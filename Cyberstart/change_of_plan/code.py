# pip install pycryptodome
from Crypto.Cipher import AES
import base64

BLOCK_SIZE = 32

PADDING = b'{'

# Encrypted text to decrypt
encrypted = "xpd4OA7GZYDfn4lTMJW/EEqgp26BlgjxsTonc1Elcgo="

def decode_aes(c, e):
    return c.decrypt(base64.b64decode(e)).rstrip(PADDING)

secret = "password"

with open("words.txt", "r") as file:
    for line in file:

        secret = line[:-1]
        if secret[-1:] == "\n":
            print("Error, new line character at the end of the string. This will not match!")
        elif len(secret.encode('utf-8')) >= 32:
            print("Error, string too long. Must be less than 32 bytes.")
        else:
            # create a cipher object using the secret
            cipher = AES.new(secret.encode('utf-8') + (BLOCK_SIZE - len(secret.encode('utf-8')) % BLOCK_SIZE) * PADDING, AES.MODE_ECB)

            # decode the encoded string
            decoded = decode_aes(cipher, encrypted)

            if decoded != '':
                try:
                    decoded.decode('utf-8')
                    print(f'Decoded: {decoded}\n')
                    break
                except Exception as e:
                    pass
