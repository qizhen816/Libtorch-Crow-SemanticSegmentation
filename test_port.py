# -*- coding: utf-8 -*-
"""
 @Time       : 2019/11/6 10:24
 @Author     : Zhen Qi
 @Email      : qizhen816@163.com
 @File       : test_port.py
 @Description: API Script
"""
import requests, json, base64, time


class MyEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, bytes):
            return str(obj, encoding='utf-8')
        return json.JSONEncoder.default(self, obj)

url = "http://localhost:5000/predict"

image_path = "00032.jpg"

jsons = {"image": str(base64.b64encode(open(image_path, "rb").read()))[2:-1]}

t1 = time.time()

result = requests.post(url, json=jsons).text

result = json.loads(result)["Prediction"][:]

print(result)
# result = result.encode('utf-8').decode('unicode_escape')

print("Cost time: ", time.time()-t1)

print(result)