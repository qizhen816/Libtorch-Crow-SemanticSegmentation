# -*- coding: utf-8 -*-
"""
 @Time       : 2019/11/6 10:24
 @Author     : Zhen Qi
 @Email      : qizhen816@163.com
 @File       : test_port.py
 @Description: API Script
"""
import requests, json, base64, time
import numpy as np
import cv2

url = "http://localhost:5000/predict"

image_path = "12043.jpg"

jsons = {"image": str(base64.b64encode(open(image_path, "rb").read()))[2:-1]}

t1 = time.time()

result = requests.post(url, json=jsons).text

result = json.loads(result)["Prediction"][:]

#
# result = result.encode('utf-8').decode('unicode_escape')

print("Cost time: ", time.time()-t1)
# result = result.replace(' ', '0')
# result = result.replace('~', '128')
# result = np.fromstring(result)
# print(str(result[:].encode('ascii', 'ignore'))[2:-1].split('\\x'))
# result.reshape((512, 512))
result = base64.b64decode(result)
result = np.asarray(bytearray(result), np.uint8)[:7225]
print(len(result))
print(result)
result.reshape((85, -1))
# x = cv2.imread(image_path)
img_decode = cv2.imdecode(result, cv2.IMREAD_GRAYSCALE)
cv2.resize(img_decode, cv2.imread(image_path).shape[:2])
cv2.imshow("pic", img_decode)
cv2.waitKey()
print(result)
# print(result)