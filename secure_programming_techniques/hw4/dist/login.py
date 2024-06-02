# Source Generated with Decompyle++
# File: login.pyc (Python 3.10)

#Unsupported opcode: JUMP_IF_NOT_EXC_MATCH
from datetime import datetime
import hashlib
users = [
    {
        'id': 0,
        'username': 'C29915',
        'password': '22390ad11c32faec43fc61555b53607660b3c185' },
    {
        'id': 1,
        'username': 'B23793',
        'password': 'da7705caa15608fea217326726ec6ed97a9c6c9d' },
    {
        'id': 2,
        'username': 'C311445',
        'password': '1b2932595090b46fc0eace7ffac86a362a86e5f2' },
    {
        'id': 3,
        'username': 'C311458',
        'password': '963dd210cc93a4597038ceabe0fe93b258a362b9' },
    {
        'id': 4,
        'username': 'C311444',
        'password': '122a417e6dce08a4a554333bbc6e9922b62c1f31' },
    {
        'id': 5,
        'username': 'C02076',
        'password': '4c57f0c88d9844630327623633ce269cf826ab99' },
    {
        'id': 6,
        'username': 'C311490',
        'password': '5b7046f25511b56046bee552337dcc9e581928ee' },
    {
        'id': 7,
        'username': 'C311451',
        'password': 'ef4355f04bdf02ca9876dd2f8dc07cd7d1dd0fcc' },
    {
        'id': 8,
        'username': 'B79966',
        'password': '91310be76f85f63de666ca9a85c009b4c0e9cabd' },
    {
        'id': 9,
        'username': 'B59964',
        'password': 'f576d38716b752f5457ecf2833a626d9523e975f' },
    {
        'id': 10,
        'username': 'C311465',
        'password': 'f1ef175756e0f637f1fb8ae47f65517d0601549a' },
    {
        'id': 11,
        'username': 'B21331',
        'password': '2dce283e0e268a42d62e34467db274c9c38c358f' },
    {
        'id': 12,
        'username': 'C311446',
        'password': 'ecc96904d5dca94b3751783d97209baeceea145f' },
    {
        'id': 13,
        'username': 'B95063',
        'password': '03808d90fc91d72309b6dffaddfc90dcd0e568ec' },
    {
        'id': 14,
        'username': 'B90967',
        'password': '96d0aa70fa027391bb6efd9700aa808c0d35ab73' },
    {
        'id': 15,
        'username': 'C311467',
        'password': '2b9af7205de6b8d1d9d1e060c51fcccb376b3163' },
    {
        'id': 16,
        'username': 'C311455',
        'password': 'a70c3bcf1d8794fa79801a8ec882925f3746b028' },
    {
        'id': 17,
        'username': 'C311466',
        'password': '20c0b7bdab70ca2cc9c844a0d74a3af0bbf41c3e' },
    {
        'id': 18,
        'username': 'C311464',
        'password': '062b06ba8e755765c6b049809b7430fd54fe5b21' },
    {
        'id': 19,
        'username': 'C40195',
        'password': '2022c1fddd7df3a85fc01618a0a9dbd1e35d8e97' },
    {
        'id': 20,
        'username': 'C40193',
        'password': '713a62692f70dcbe1c3b11a240deb504af626229' },
    {
        'id': 21,
        'username': 'B53271',
        'password': '8b6cea61d247482e9e7f1e7efb1db432a69bbcb2' },
    {
        'id': 22,
        'username': 'C311449',
        'password': 'eb732649f9e2327bb6f534be4b9ba085b3250ac9' },
    {
        'id': 23,
        'username': 'B45021',
        'password': '59f054fa5a2164fb3ae235dd40b71eea61fc005f' },
    {
        'id': 24,
        'username': 'C40194',
        'password': '94b1786d32ac0dcc593810568d9ee8b5ac1c49ef' },
    {
        'id': 25,
        'username': 'B87773',
        'password': '079c0782d55dbfbc9dd86a2b43d22d71ada8ddd6' }]

def login(username, password, sum):
#Warning: Stack history is not empty!
#Warning: block stack is not empty!
    hash = hashlib.sha1(password.encode('utf8')).hexdigest()
    
    try:
        checksum = eval(sum)
        if checksum != 10:
            log_event('Wrong checksum entered!')
            print('Wrong checksum!')
    finally:
        #return None
        if None(None((lambda x = None: x['username'] == username), users)) == []:
            log_event('User ' + username + ' does not exist!')
            print('User does not exist!')
        return None
        if None(None((lambda x = None: x['password'] == hash), users)) == []:
            log_event('Wrong password!')
            print('Wrong password!')
        return None
        log_event('Checksum correct! User is logged in!')
        print('Well done! Your flag is your password!')
        return None
        log_event('Can not eval() the following: ' + sum)
        print('Unexpected error!')
        return None



def log_event(text):
    now = datetime.now()
    file = open('log.txt', 'a')
    entry = str(now) + ': ' + text + '\n'
    file.write(entry)
    file.close()


def input_val(username, password, sum):
    if username.strip() == '' or password.strip() == '':
        print('Username or password can not be empty!')
        return None
    if None.strip() == '':
        print('Checksum can not be empty!')
        return None
    None(username, password, sum)

# WARNING: Decompyle incomplete