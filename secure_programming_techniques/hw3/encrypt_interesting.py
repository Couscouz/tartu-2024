#!/usr/bin/python
# -*- coding: utf-8 -*-
import hashlib
import os
import sys
import random
import threading
import tkinter as tk
from pathlib import Path
from tkinter import *
from tkinter import filedialog, messagebox

from Cryptodome.Cipher import AES


class EncryptionTool:
    def __init__(
        self,
        user_file,
        user_key,
        user_salt,
    ):

        # get the path to input file

        self.user_file = user_file

        self.input_file_size = os.path.getsize(self.user_file)
        self.chunk_size = 1024
        self.total_chunks = self.input_file_size // self.chunk_size + 1

        # convert the key and salt to bytes

        self.user_key = bytes(user_key, "utf-8")
        self.user_salt = bytes(user_key[::-1], "utf-8")

        # get the file extension

        self.file_extension = self.user_file.split(".")[-1]

        # hash type for hashing key and salt

        self.hash_type = "SHA256"

        # encrypted file name

        self.encrypt_output_file = (
            ".".join(self.user_file.split(".")[:-1])
            + ".encr"
        )

        # dictionary to store hashed key and salt

        self.hashed_key_salt = dict()

        # hash key and salt into 16 bit hashes

        self.hash_key_salt()

    def read_in_chunks(self, file_object, chunk_size=1024):
        """Lazy function (generator) to read a file piece by piece.
        Default chunk size: 1k.
        """

        while True:
            data = file_object.read(chunk_size)
            if not data:
                break
            yield data

    def encrypt(self):

        # create a cipher object

        cipher_object = AES.new(
            self.hashed_key_salt["key"], AES.MODE_CFB, self.hashed_key_salt["salt"]
        )

        self.abort()  # if the output file already exists, remove it first

        input_file = open(self.user_file, "rb")
        output_file = open(self.encrypt_output_file, "ab")
        done_chunks = 0

        for piece in self.read_in_chunks(input_file, self.chunk_size):
            encrypted_content = cipher_object.encrypt(piece)
            output_file.write(encrypted_content)
            done_chunks += 1
            yield done_chunks / self.total_chunks * 100

        input_file.close()
        output_file.close()

        # clean up the cipher object

        del cipher_object

    def soft_encrypt(self):

        self.abort()

        input_file = open(self.user_file, "rb")
        output_file = open(self.encrypt_output_file, "ab")
        done_chunks = 0

        for piece in self.read_in_chunks(input_file, self.chunk_size):
            encrypted_content = self.soft_encrypt_help(piece)
            output_file.write(encrypted_content)
            done_chunks += 1
            yield done_chunks / self.total_chunks * 100

        input_file.close()
        output_file.close()


    def soft_encrypt_help(self,data):
        encrypted_data = b''
        key = self.user_key.decode('utf-8')
        key = key * (len(key) // 4 + 1)
        key = key.encode()
        key_length = len(key)
        for i, byte in enumerate(data):
            encrypted_data += bytes([byte ^ key[i % key_length]])
        return encrypted_data

    def abort(self):
        if os.path.isfile(self.encrypt_output_file):
            os.remove(self.encrypt_output_file)


    def hash_key_salt(self):

        # create new hasher object
        hasher = hashlib.new(self.hash_type)
        generatorNumber = key = self.secret_sauce(self.user_key.decode('utf-8'))
        random.seed(generatorNumber)
        key = ''
        for i in range(24):
            random_thing2acter = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789')
            key += random_thing2acter
        first = bytes(key, "utf-8") 
        second = bytes(key[::-1], "utf-8") 
        hasher.update(first)

        # turn the output key hash into 32 bytes (256 bits)

        self.hashed_key_salt["key"] = bytes(hasher.hexdigest()[:32], "utf-8")

        # clean up hash object

        del hasher

        #  create a new hash object

        hasher = hashlib.new(self.hash_type)
        hasher.update(second)

        # turn the output salt hash into 16 bytes (128 bits)

        self.hashed_key_salt["salt"] = bytes(hasher.hexdigest()[:16], "utf-8")

        # clean up hash object

        del hasher
    
    def secretKey(self):
        # key for the secret encryption, base64 encoded, only for development - remove after!
        key = 'aHR0cHM6Ly9yYi5neS93cjB2azI='
        salt = 'aHR0cHM6Ly9yYi5neS93cjB2azI='[::-1]

        return key,salt
    
    def supersecretKey(self):
        # key for the super secret encryption, base64 encoded, only for development - remove after!
        key = 'aHR0cHM6Ly95b3V0dS5iZS9QYi1IRE5VU3FyRT9mZWF0dXJlPXNoYXJlZA=='
        salt = 'aHR0cHM6Ly95b3V0dS5iZS9QYi1IRE5VU3FyRT9mZWF0dXJlPXNoYXJlZA=='[::-1]

        return key,salt

    def secret_sauce(self,string):

        generator=''
        for thing in string:
            if thing.isdigit():
                generator+=thing
        if generator != '':
            total = int(generator)
        else:
            total = 0

        for thing2 in string:
            if thing2.isdigit(): 
                total += int(thing2)  
            elif thing2.isprintable():  
                total += ord(thing2)
        return total
    


class MainWindow:

        self.soft_encrypt_btn = tk.Button(
            root,
            text="Secret Encrypt",
            command=self.se_check_callback,
            bg="#27ae60",
            fg="#ffffff",
            bd=2,
            relief=tk.FLAT,
        )

        self.encrypt_btn = tk.Button(
            root,
            text="Super Secret Encrypt",
            command=self.e_check_callback,
            bg="#27ae60",
            fg="#ffffff",
            bd=2,
            relief=tk.FLAT,
        )

        self.reset_btn = tk.Button(
            root,
            text="Clear",
            command=self.reset_callback,
            bg="#717d7e",
            fg="#ffffff",
            bd=2,
            relief=tk.FLAT,
        )

        self.stop_btn = tk.Button(
            root,
            text="STOP",
            command=self.cancel_callback,
            bg="#aaaaaa",
            fg="#ffffff",
            bd=2,
            state="disabled",
            relief=tk.FLAT,
        )

        self.stop_btn.grid(
            padx=15,
            pady=8,
            ipadx=24,
            ipady=6,
            row=8,
            column=0,
            columnspan=2,
            sticky=tk.W + tk.E + tk.N + tk.S,
        )

        tk.Grid.columnconfigure(root, 0, weight=1)
        tk.Grid.columnconfigure(root, 1, weight=1)
        tk.Grid.columnconfigure(root, 2, weight=1)
        tk.Grid.columnconfigure(root, 3, weight=1)

    def e_check_callback(self):

        newPath = Path(self._file_url.get())
        if newPath.is_file():
            pass
        else:
            messagebox.showinfo("EncrypC", "Please Enter a valid File URL!")
            return

        if len(self._secret_key.get()) == 0:
            messagebox.showinfo("EncrypC", "Please Enter a valid Secret Key!")
            return
        elif self._secret_key.get() != self._secret_key_check.get():
            messagebox.showinfo("EncrypC", "Passwords do not match!")
            return

        self.encrypt_callback()

    def se_check_callback(self):

        newPath = Path(self._file_url.get())
        if newPath.is_file():
            pass
        else:
            messagebox.showinfo("EncrypC", "Please Enter a valid File URL!")
            return

        if len(self._secret_key.get()) == 0:
            messagebox.showinfo("EncrypC", "Please Enter a Secret Key!")
            return
        elif self._secret_key.get() != self._secret_key_check.get():
            messagebox.showinfo("EncrypC", "Passwords do not match!")
            return

        self.soft_enc_callback()


    def encrypt_execute(self):
        self.freeze_controls()

        try:
            self._cipher = EncryptionTool(
                self._file_url.get(), self._secret_key.get(), self._salt.get()
            )
            for percentage in self._cipher.encrypt():
                if self.should_cancel:
                    break
                percentage = "{0:.2f}%".format(percentage)
                self._status.set(percentage)
                self.status_label.update()

            if self.should_cancel:
                self._cipher.abort()
                self._status.set("Cancellation Successful!")
                messagebox.showinfo("EncrypC", "Cancellation Successful!")
                self._cipher = None
                self.should_cancel = False
                self.unfreeze_controls()
                return

            self._cipher = None
            self.should_cancel = False
            self._status.set("File Encryption Successful!")
            messagebox.showinfo("EncrypC", "File Encryption Successful!")
        except Exception as e:

            self._status.set(e)

        self.unfreeze_controls()


    def soft_enc_execute(self):
        self.freeze_controls()

        try:
            self._cipher = EncryptionTool(
                self._file_url.get(), self._secret_key.get(), self._salt.get()
            )
            for percentage in self._cipher.soft_encrypt():
                if self.should_cancel:
                    break
                percentage = "{0:.2f}%".format(percentage)
                self._status.set(percentage)
                self.status_label.update()

            if self.should_cancel:
                self._cipher.abort()
                self._status.set("Cancellation Successful!")
                messagebox.showinfo("EncrypC", "Cancellation Successful!")
                self._cipher = None
                self.should_cancel = False
                self.unfreeze_controls()
                return

            self._cipher = None
            self.should_cancel = False
            self._status.set("File Encryption Successful!")
            messagebox.showinfo("EncrypC", "File Encryption Successful!")
        except Exception as e:

            self._status.set(e)

        self.unfreeze_controls()


if __name__ == "__main__":
    ROOT = tk.Tk()
    MAIN_WINDOW = MainWindow(ROOT)
    bundle_dir = getattr(sys, "_MEIPASS", os.path.abspath(os.path.dirname(__file__)))
    ROOT.resizable(height=False, width=False)
    ROOT.mainloop()
