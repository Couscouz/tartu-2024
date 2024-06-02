import itertools
import base64

# Generate all combinations of Base64 characters
base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
combinations = itertools.product(base64_chars, repeat=20)

# Write combinations to file
with open("base64_combinations.txt", "w") as file:
    i=0
    for combo in combinations:
    	i=i+1
    	print(f"{i}")
    	base64_string = ''.join(combo)
    	file.write(base64_string + "\n")
