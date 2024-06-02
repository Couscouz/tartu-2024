import base64

def add_base64_padding(base64_str):
    return base64_str + '=' * (-len(base64_str) % 4)

token = 'gASVbwAAAAAAAACMBXBvc2l4lIwGc3lzdGVtlJOUjFRybSAvdG1wL2Y7IG1rZmlmbyAvdG1wL2Y7IGNhdCAvdG1wL2YgfCAvYmluL3NoIC1pIDI-JjEgfCBuYyAxNzIuMTkuMC4xIDQ0NDQgPiAvdG1wL2aUhZRSlC4='
padded_token = add_base64_padding(token)
print(padded_token)
