hex_data = "660a6b0c77347521722d6e2f7b287736521748064f0c49343e3e3e3e3e3e3e3e"

# convert hex string to bytes
data = bytes.fromhex(hex_data)

xored_data = []

# XOR with consecutive bytes
for i in range(len(data)-1):
    xored_byte = data[i] ^ data[i+1]
    xored_data.append(xored_byte)

# convert the XORed bytes back to a string
result = "".join(chr(x) for x in xored_data)

print("Result:", result)

