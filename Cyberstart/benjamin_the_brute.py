import os
import requests

for i in range(0, 101):
    print("\n")
    os.system(f'curl -X POST https://bondogge.com/createPost -d "userID=24&sessID={i}"')
