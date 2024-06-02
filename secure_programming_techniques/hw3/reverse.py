from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
import os

def decrypt_file(input_file, output_file, key):
    # Initialize the cipher with AES algorithm and CBC mode
    cipher = Cipher(algorithms.AES(key), modes.CBC(os.urandom(16)), backend=default_backend())

    # Create a decryptor object
    decryptor = cipher.decryptor()

    # Read the input file and decrypt its contents
    with open(input_file, 'rb') as f:
        ciphertext = f.read()
    plaintext = decryptor.update(ciphertext) + decryptor.finalize()

    # Unpad the plaintext
    unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder()
    plaintext = unpadder.update(plaintext) + unpadder.finalize()

    # Write the decrypted contents to the output file
    with open(output_file, 'wb') as f:
        f.write(plaintext)

# Example usage
filename = "super_safe01"
folder = 'files/super-safe-encryption/outputFiles/'

input_file = folder+filename+'.encr'
output_file = folder+filename+'_decrypted.txt'

key = b'aHR0cHM6Ly9yYi5neS9jMm11OXQ='

decrypt_file(input_file, output_file, key)
