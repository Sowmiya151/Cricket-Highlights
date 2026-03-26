# 🏏 Automated Cricket Highlight Generation System

## 📌 Project Overview
This project presents an automated system for generating cricket match highlights using sensor-based data and a rule-based AI engine. It eliminates manual effort and enables real-time highlight detection.

---

## 🚨 Problem Statement
Manual highlight creation:
- Requires significant time and human effort  
- May miss important moments  
- Cannot provide real-time highlights  
- Needs continuous video analysis  

---

## 💡 Proposed Solution
The system uses:
- 📡 Sensor-based data collection  
- ⚙️ Rule + AI-based highlight detection  
- 🎯 Event scoring mechanism  
- 🎥 Automatic highlight generation  

---

## 🏗️ System Architecture (5-Layer Model)

### 1️⃣ Embedded Hardware Layer
- Captures ball speed, bat impact, boundaries, etc.

### 2️⃣ Data Acquisition Layer
- Converts sensor signals into structured data (CSV)

### 3️⃣ Networking Layer
- Synchronizes real-time match events

### 4️⃣ Rule Engine & AI Layer
- Detects key events (wickets, sixes, boundaries)

### 5️⃣ Display Layer
- Generates highlight timeline and clips

---

## 🧠 Key Features
- ✅ Real-time highlight detection  
- ✅ Mid-match highlight updates  
- ✅ Top highlight moments selection  
- ✅ Excitement scoring system  
- ✅ Over-wise highlight timeline  

---

## ⚙️ Technologies Used
- C / C++  
- CSV Data Processing  
- Rule-Based Logic  
- Basic AI Scoring Techniques  

---

## 📊 Highlight Detection Approaches

### 🔹 Overall Match Highlights
- Analyzes full match
- Selects best moments using scoring

### 🔹 Mid-Match Highlights
- Selects best event per over
- Real-time processing

### 🔹 Highlight Moments
- Picks top events based on ranking

---

## 📁 Project Structure
```
cricket-highlights-system/
│
├── data/
│ └── cricketdata.csv
│
├── src/
│ ├── overall_highlights.cpp
│ ├── mid_match.cpp
│ ├── selective_events.cpp
│ └── display.cpp
│
├── docs/
│ └── project_report.pdf
│
└── README.md
```
