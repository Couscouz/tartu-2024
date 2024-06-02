import subprocess

# Define the fixed inputs
password = "no_care"
check = "5+5"

# Function to read usernames from file and test each one
def test_usernames_from_file(filename):
    try:
        # Open the file and read usernames
        with open(filename, 'r') as file:
            usernames = file.readlines()

        # Iterate through each username
        i=1
        for username in usernames:
            username = username.strip()  # Remove any extra whitespace/newline characters

            # Create the process
            process = subprocess.Popen(
                ['./login'],            # Command to execute the script
                stdin=subprocess.PIPE,  # Standard input to the process
                stdout=subprocess.PIPE, # Standard output from the process
                stderr=subprocess.PIPE  # Standard error from the process
            )

            # Provide the inputs to the process
            inputs = f"{username}\n{password}\n{check}\n".encode()

            # Communicate the inputs and capture the output and error (if any)
            output, error = process.communicate(inputs)

            # Print the outputs (decode bytes to string)
            # print(f"Username: {username}")
            # print("Output:", output.decode())
            # print("Error:", error.decode())

            # Optionally, add a condition to break the loop if a successful login is found
            if "does not" not in output.decode().lower():
                print(f"Successful login with username: {username}")

    except FileNotFoundError:
        print(f"The file {filename} was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Specify the filename
filename = "/usr/share/wordlists/usernames.txt"

# Run the function
test_usernames_from_file(filename)
