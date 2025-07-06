# 🧠 Data Structure problems

> 📜 **Disclaimer:** This project was developed collaboratively for educational purposes. My personal contribution is limited to **Problem 4: Patient Triage System using Max Heap**.

---

## 📦 Overview

This repository contains implementations of four data structure problems in C++, all written **without using the Standard Template Library (STL)**. Each problem is in a separate `.cpp` file and demonstrates core concepts in custom data structure implementation.

---

## 📝 Problem List

### 🧭 **Problem 1: Browser History with Stacks**
- Implements browser navigation using two custom stack structures.
- Tracks URL visits, back, and forward commands.
- Input: `inputProblem1.txt`  
- Compilation:
  ```bash
  g++ Problem1.cpp -o Problem1
  ./Problem1
📇 Problem 2: AVL Tree Address Book
Contact management system using a self-balancing AVL Tree.

Supports add, delete, search, and list operations.

Input: inputProblem2.txt

Output: outputProblem2.txt

🔁 Problem 3: Minimum Segment Flips
Flips segments of a binary array to turn all bits to 1.

Greedy + queue-based approach (custom queue).

Input: inputProblem3.txt

Output: output3.txt

🏥 Problem 4: Patient Triage System using Max Heap ✅ (My Contribution)
This solution simulates a hospital triage system using a custom Max Heap. Patients are prioritized based on severity, and in case of a tie, by arrival time. The most critical patient is always treated first.

🔧 Features:
Fully array-based Max Heap (no STL)

Custom Patient struct storing:

name (string)

severity (int)

arrival_time (int)

Heap operations:

insert() with heapify-up

extractMax() with heapify-down

Handles multiple test cases via structured input

📂 File Structure:
Problem4.cpp — Complete solution code

inputProblem4.txt — JSON-like patient entries for multiple test cases

outputProblem4.txt — Logs of insertions and treatment order

▶️ How to Run:
bash
Copy
Edit
g++ Problem4.cpp -o Problem4
./Problem4
📚 Technologies Used
Language: C++

Data Structures Implemented:

Stack (Array-based)

AVL Tree

Queue (Linked list)

Max Heap (Array-based)

Concepts Covered:

Manual memory management

Tree balancing algorithms

Heap operations

Greedy algorithms

File parsing

👩‍💻 Contribution
I contributed Problem 4: Patient Triage System using Max Heap, which includes:

Custom MaxHeap class

Patient struct

Input parsing from structured file

Full logic for insertion, extraction, and priority ordering

Output formatting and logs

📜 License
This project was developed for academic purposes. All solutions and components belong to their respective contributors. Redistribution without credit is not permitted.
