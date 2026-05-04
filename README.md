# 🤖 Admission Assistant Robot

## 📌 Overview
The Admission Assistant Robot is an AI-powered interactive system designed to assist visitors with college admission-related queries. It integrates computer vision, embedded systems, and IoT to identify users and provide automated responses in real time.

---

## 🚀 Features
- 👁️ Real-time face detection and recognition using ESP32-CAM  
- 🧠 AI model deployment using Edge Impulse for intelligent identification  
- 🔊 Audio-based interaction using DFPlayer Mini for voice responses  
- 📡 Remote monitoring and control via Blynk IoT platform  
- 🤖 Autonomous robot control with embedded system integration  
- ⚡ Low-latency edge processing without cloud dependency  

---

## 🏗️ System Architecture



```mermaid
flowchart LR

subgraph Input_Layer
A[Visitor]
B[ESP32 CAM]
end

subgraph Edge_AI_Processing
C[Face Detection - Edge Impulse]
D[ESP32 Control Logic]
end

subgraph Actuation_Layer
E[Motor Driver and Wheels]
F[DFPlayer Audio Module]
end

subgraph IoT_Cloud_Layer
G[Blynk Cloud Server]
H[Mobile App Dashboard]
end

A --> B
B --> C
C --> D

D --> E
D --> F
D --> G

E --> I[Robot Movement]
F --> J[Voice Interaction]
G --> H
```
The system consists of multiple integrated modules:

### 1. Vision Module (ESP32-CAM)
- Captures live video feed  
- Runs AI model (Edge Impulse) for face detection/recognition  
- Sends processed data to control system  

### 2. Control Module (ESP32)
- Executes robot movement and decision logic  
- Coordinates with vision module  
- Triggers responses based on detected user  

### 3. Audio Interaction Module
- DFPlayer Mini used for pre-recorded voice responses  
- Provides admission-related guidance  

### 4. IoT Integration (Blynk)
- Enables remote monitoring and control  
- Displays system status and alerts  

---

## 🛠️ Tech Stack
- ESP32, ESP32-CAM  
- Edge Impulse (TinyML)  
- Blynk IoT Platform  
- DFPlayer Mini (Audio Module)  
- Embedded C/C++ (Arduino IDE)  
- Computer Vision  

---

## ⚙️ How It Works

1. ESP32-CAM captures visitor image  
2. Edge Impulse model processes and detects face  
3. Control module receives detection result  
4. Robot triggers appropriate response  
5. DFPlayer plays audio guidance  
6. Blynk app monitors system in real time  

---

## 🔮 Future Improvements
- 🎤 Voice recognition (speech-to-text interaction)  
- 🤖 LLM-based conversational assistant  
- ☁️ Cloud database for admission records  
- 📱 Mobile app for full control
- 🤖 ROS2 integration for autonomous navigation and modular robotic control  

---

## 🎥 Demo
<img width="540" height="720" alt="Robot-IMG" src="https://github.com/user-attachments/assets/bb3859b4-a628-4893-b01f-41a7dd428855" />
</img>

<br>

<video width="540" height="720" controls>
  <source src="[DIRECT_MP4_LINK](https://github.com/user-attachments/assets/9c2d8d01-5f73-4a56-8e6d-3fac1a973315)" type="video/mp4">
</video>

<!-- <a href="https://github.com/user-attachments/assets/9c2d8d01-5f73-4a56-8e6d-3fac1a973315"> -->
  <img width="540" height="720" alt="Robot Demo" src="https://github.com/user-attachments/assets/9c2d8d01-5f73-4a56-8e6d-3fac1a973315">
<!-- </a> -->
---

## 👨‍💻 Author
**Sambhav Jain**
