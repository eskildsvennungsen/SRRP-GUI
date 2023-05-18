import json
import os
import time

def parseJSON(input):
    with open(os.path.join(os.path.dirname(__file__), "baginfo.json")) as f:
        data = json.load(f)
        height = data['Settings']['height']
        f.close()
        return height

while True:
    time.sleep(1)
    print(parseJSON(1))