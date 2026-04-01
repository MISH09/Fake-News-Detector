# Fake News Detector (Rule-Based)

A rule-based fake news detection system built using C++ (OOP) with an additional web interface using HTML, CSS, and JavaScript. The system evaluates news articles using logical rules instead of machine learning.

---

## Features
- Rule-based fake news detection
- Object-Oriented Programming concepts (Inheritance, Polymorphism, Encapsulation)
- Keyword-based clickbait detection
- Source credibility analysis
- Title–content mismatch detection
- File handling in C++ (news.txt)
- Search functionality for saved articles
- Web interface with analyze, view, and search pages

---

## How It Works

The system assigns a base score and adjusts it using predefined rules:

- Keyword Rule → -20  
- Source Rule → +30 / -30  
- Title Match Rule → +10 / -20  

### Classification
- Score ≥ 80 → Reliable  
- Score 50–79 → Suspicious  
- Score < 50 → Fake News  

---

## Technologies Used
- C++ (core logic and file handling)
- HTML, CSS, JavaScript (web interface)
- Local Storage (frontend persistence)

---

## Project Structure
fake-news-detector/
│
├── fake_news_detector.cpp
├── news.txt
│
├── index.html
├── view.html
├── search.html
├── style.css
├── script.js
│
└── README.md


---

## How to Run
### C++ Version
g++ fake_news_detector.cpp -o detector
./detector

(Windows: detector)

### Web Version
Open `index.html` in a browser.

---

## Data Storage
- C++: Stored in `news.txt`
- Web: Stored using browser local storage

---

## Example

Input: (Windows: detector)

### Web Version
Open `index.html` in a browser.

---

## Data Storage
- C++: Stored in `news.txt`
- Web: Stored using browser local storage

---

## Example

Input:
Title: Breaking News Government Secret
Content: This shocking event reveals secret plans
Source: randomnews.xyz

Output:
Score: 10
Result: FAKE NEWS

---

## Future Enhancements
- Add more advanced detection rules
- Integrate machine learning models
- Replace text file with database storage
- Develop a full-stack deployment

---

## Author
Manasi Joshi
