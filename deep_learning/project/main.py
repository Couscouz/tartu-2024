import shutil
import random
import os

import cv2
import matplotlib.pyplot as plt
import numpy as np

from IPython.display import display, Javascript
from tensorflow.keras.preprocessing.image import ImageDataGenerator, img_to_array, load_img

from random import shuffle
from PIL import Image
from pathlib import Path

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms

import pandas as pd
import datetime
import json

#===================================================================================
#===================================================================================
#===================================================================================

classes =  ['yes','no','please','sorry','hello','wait','food','thankyou','home','help']

class CustomDataset(Dataset):
    def __init__(self, images_dir, classes, augment=True):
        """
        Args:
            images_dir (string): Path to the directory with all the images.
            classes (list): List of class names.
            augment (bool, optional): Whether to augment the images produced by the dataset.
        """
        self.images_dir = images_dir
        self.classes = classes
        self.augment = augment

        images_set = os.listdir(images_dir)
        self.images = [Image.open(os.path.join(images_dir, file_name)) for file_name in images_set]
        self.labels = [file_name.split('_')[0] for file_name in images_set]

        if augment:
            self.transform = transforms.Compose([
                transforms.RandomResizedCrop(224, scale=(0.8, 1.0), ratio=(0.75, 1.33)),
                transforms.ToTensor()
            ])
        else:
            self.transform = transforms.Compose([
                transforms.Resize((224, 224)),
                transforms.ToTensor()
            ])

    def __len__(self):
        return len(self.labels)

    def __getitem__(self, idx):
        image = self.images[idx]
        label = self.labels[idx]
        try:
            label_tensor = torch.tensor(self.classes.index(label))
        except:
            label_tensor = torch.tensor(-1)
        image = self.transform(image)

        return image, label_tensor

def get_score(final_csv):
    good = 0
    total = 0
    with open('./good.csv') as truth:
        for i,label,line_t in zip(final_csv["id"],final_csv["label"],truth):
            line = f"{i},{label}"
            if line in line_t:
                good += 1
            else:
                print(f"{line} not in {line_t}")
            total += 1
    return float(good/total)


train_dataset = CustomDataset(images_dir="./data/train",classes=classes, augment=True)
val_dataset = CustomDataset(images_dir="./data/val",classes=classes, augment=False)

train_loader = DataLoader(train_dataset, batch_size=16, shuffle=True, generator=torch.Generator().manual_seed(1))
val_loader = DataLoader(val_dataset, batch_size=8, shuffle=False)

def process(modelname,num_epochs,learning_rate):
    model = torch.hub.load('pytorch/vision:v0.10.0', modelname, pretrained=True)
    print(f"Starting training {modelname} with {num_epochs} epochs lr={learning_rate}")
    for epoch in range(num_epochs):
        model.train()  # Set the model to training mode
        running_loss = 0.0
        for images, labels in train_loader:
            optimizer.zero_grad()  # Zero the parameter gradients
            outputs = model(images)  # Forward pass
            loss = criterion(outputs, labels)  # Compute the loss
            loss.backward()  # Backward pass
            optimizer.step()  # Optimize

            running_loss += loss.item() * images.size(0)

        # Print average training loss for the epoch
        epoch_loss = running_loss / len(train_loader.dataset)
        print(f"Epoch [{epoch + 1}/{num_epochs}], Loss: {epoch_loss:.4f}")
    prediction = {}
    model.eval()
    correct = 0
    total = 0
    i=0
    batch_size = 8
    with torch.no_grad():
        for images, _labels in val_loader:
            outputs = model(images)
            _, predicted = torch.max(outputs, 1)
            for j in range(batch_size):
                index = j+1+i*8
                if index < 200:
                    prediction[index] = classes[predicted[j].item()]
            i+=1

#===================================================================================
#===================================================================================
#===================================================================================

"""
BEST COMBO
resnet34
n_epchs=
lr=0.1


lr=0.5 :
24 => 2.3 stuck
"""
modelname='resnet50'

model = torch.hub.load('pytorch/vision:v0.10.0', modelname, pretrained=True)

all_learning_rates = [0.1, 0.01, 0.05, 0.001, 0.005, 0.0001, 0.005]
all_num_epochs = [5,10,20,30]

bruteforce = False

learning_rate = 0.05

num_features = model.fc.in_features
model.fc = nn.Linear(num_features, len(classes))
model.train()
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

#-------re-train----
num_epochs = 10
iteration=0

if bruteforce:
    for num_epochs in all_num_epochs:
        for learning_rate in all_learning_rates:
            process('resnet34',num_epochs=num_epochs, learning_rate=learning_rate)

print(f"Starting with {modelname}, lr={learning_rate}, {num_epochs} epochs")
for epoch in range(num_epochs):
    model.train()  # Set the model to training mode
    running_loss = 0.0
    correct = 0
    total = 0
    for images, labels in train_loader:
        optimizer.zero_grad()  # Zero the parameter gradients
        outputs = model(images)  # Forward pass
        loss = criterion(outputs, labels)  # Compute the loss
        loss.backward()  # Backward pass
        optimizer.step()  # Optimize

        running_loss += loss.item() * images.size(0)

        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

    # Print average training loss for the epoch
    epoch_loss = running_loss / len(train_loader.dataset)

    accuracy = 100 * correct / total
    print(f"Epoch [{epoch + 1}/{num_epochs}], Loss: {epoch_loss:.4f}, Accuracy: {accuracy:.2f}%")
#--------------------------

prediction = {}
model.eval()
correct = 0
total = 0
i=0
batch_size = 8
with torch.no_grad():
    for images, _labels in val_loader:
        outputs = model(images)
        _, predicted = torch.max(outputs, 1)
        for j in range(batch_size):
            index = j+1+i*8
            if index < 200:
                prediction[index] = classes[predicted[j].item()]
        i+=1
        
#----saving to final csv-----

submission = {"id": list(prediction.keys()), "label": list(prediction.values())}


score = get_score(submission)
name = f"{modelname}_{num_epochs}e_{learning_rate}lr_score{score}"

print(f"{name} ==> {score}")

submission_df = pd.DataFrame(submission)

now = datetime.datetime.now()
date = f"{now.day}-May_{3+now.hour}h{now.minute}"
output_path = f"./output/submission_{name}_{date}.csv"

submission_df.to_csv(output_path, index=False)


# model_names = ['resnet18','resnet34','resnet50','resnet101','resnet152']
# all_num_epochs = [1,2,3,5,10]
# how_much_each = 3

# sumup = {}

# for modelname in model_names:
#     for num_epochs in all_num_epochs:
#         for iteration in range(how_much_each):
#             try:
#                 model = torch.hub.load('pytorch/vision:v0.10.0', modelname, pretrained=True)

#                 num_features = model.fc.in_features
#                 model.fc = nn.Linear(num_features, len(classes)) # K stands for the number of classes
#                 model.train()
#                 criterion = nn.CrossEntropyLoss()
#                 optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

#                 print(f"Re training {modelname} with {num_epochs} epochs")
#                 #-------re-train----
#                 for epoch in range(num_epochs):
#                     model.train()  # Set the model to training mode
#                     running_loss = 0.0
#                     for images, labels in train_loader:
#                         optimizer.zero_grad()  # Zero the parameter gradients
#                         outputs = model(images)  # Forward pass
#                         loss = criterion(outputs, labels)  # Compute the loss
#                         loss.backward()  # Backward pass
#                         optimizer.step()  # Optimize

#                         running_loss += loss.item() * images.size(0)

#                     # Print average training loss for the epoch
#                     epoch_loss = running_loss / len(train_loader.dataset)
#                     print(f"Epoch [{epoch + 1}/{num_epochs}], Loss: {epoch_loss:.4f}")
#                 #--------------------------

#                 prediction = {}
#                 model.eval()
#                 correct = 0
#                 total = 0
#                 i=0
#                 batch_size = 8
#                 with torch.no_grad():
#                     for images, _labels in val_loader:
#                         outputs = model(images)
#                         _, predicted = torch.max(outputs, 1)
#                         for j in range(batch_size):
#                             index = j+1+i*8
#                             if index < 200:
#                                 prediction[index] = classes[predicted[j].item()]
#                         i+=1
                        
#                 #----saving to final csv-----

#                 submission = {"id": list(prediction.keys()), "label": list(prediction.values())}
                

#                 score = get_score(submission)
#                 name = f"{modelname}_{num_epochs}e_i{iteration}"

#                 print(f"{name} ==> {score}")
#                 sumup[name] = str(score)
#                 if score > max_score:
#                     max_score = score

#                 submission_df = pd.DataFrame(submission)
#                 now = datetime.datetime.now()
#                 date = f"{now.day}-May_{3+now.hour}h{now.minute}"
#                 output_path = f"./output/submission_{modelname}_{num_epochs}e_i{iteration}_{date}.csv"

#                 submission_df.to_csv(output_path, index=False)

#                 print("============")
#             except:
#                 print(f"error with {modelname}_{num_epochs}e_i{iteration}")

# recap = {"id": list(sumup.keys()), "score": list(sumup.values())}
# recap_df = pd.DataFrame(recap)

# now = datetime.datetime.now()
# date = f"{now.day}-May_{3+now.hour}h{now.minute}"
# recap_df.to_csv(f"./output/sumup_{date}.csv", index=False)
