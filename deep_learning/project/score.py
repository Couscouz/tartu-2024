import json
import csv
import os
import sys
import pandas as pd

def get_score(final_csv):
    good = 0
    total = 0
    with open('./good.csv') as truth:
        for line,line_t in zip(final_csv,truth):
            #line = f"{i},{label}"
            if line in line_t:
                good += 1
            else:
                print(f"{line} not in {line_t}")
            total += 1
    return float(good/total)

filename = sys.argv[1]

df = pd.read_csv(filename)
print(df)
score = get_score(df)
print(f"{filename} ==> {score}")