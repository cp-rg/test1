import requests

ESP32_IP = "http://192.168.86.44/setString"   # Change to your ESP32 IP
text_to_send = "dddd"

try:
    response = requests.post(ESP32_IP, data=text_to_send)
    print("ESP32 replied:", response.text)
except Exception as e:
    print("Error sending request:", e)