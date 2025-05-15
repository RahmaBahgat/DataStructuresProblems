# DS-implementation

## Overview
This repository contains solutions to four programming problems, each implemented in C++ without using the STL library. Each problem is in a separate .cpp file and demonstrates custom data structure implementations.

## Problem 1: Browser History with Stacks
### Approach:

- Uses two stacks (backStack and forwardStack) to manage navigation history.

- visit(url): Pushes to backStack, clears forwardStack.

- goBack(): Moves current URL from backStack to forwardStack.

- goForward(): Moves from forwardStack back to backStack.

### Code Structure:

- Stack class with dynamic array implementation.

- BrowserHistory class to manage navigation.

- Input is read from input1.txt with commands: visit <url>, back, forward.

### Compilation & Execution:

bash
g++ Problem1.cpp -o Problem1
./Problem1

### Input File Format: inputProblem1.txt

## Problem 2: AVL Tree Address Book

### Overview:
This problem implements a contact management system (address book) using an **AVL Tree** (a self-balancing binary search tree). Each contact contains an ID, name, phone number, and email address. The system supports insert, search, delete, and list operations, with all contacts kept balanced by the AVL tree properties.

The application reads user actions (e.g., add, delete, search) from an input file (`inputProblem2.txt`) and writes all output (including tree structure, errors, and search results) to an output file (`outputProblem2.txt`).

### Approach:
- The contacts are stored in an AVL tree ordered by unique ID.
- The AVL Tree auto-balances itself on every insert and delete to maintain O(log n) time complexity.
- Each node contains:
  - `id`, `name`, `phone`, `email`
  - Left and right pointers
  - Height for balancing

- **Functions Implemented**:
  - `insert()`: Adds a new contact while maintaining balance.
  - `deleteContact()`: Deletes a contact and re-balances the tree.
  - `search()`: Looks for a contact by ID.
  - `listContacts()`: In-order traversal (prints sorted contacts).
  - `printTree()`: Prints the current tree structure rotated 90 degrees.
  - `checkBalance()`, `leftRotate()`, `rightRotate()`: Maintain AVL properties.

- Input/output redirection is used to read from a file instead of manual input:
  - If the input file is not found, the program displays an error and exits.

### Code Structure:
- `Contact`: Struct representing each node in the AVL tree.
- Functions for AVL insertions, deletions, rotations, and utility operations.
- Main function displays a menu and processes commands from `inputProblem2.txt`.

### Input File Format: inputProblem2.txt


## Problem 3: Minimum Segment Flips

### Overview:

- This problem involves finding the minimum number of segment flips required to convert a binary array into an array of all 1s.
- Each flip toggles (0 → 1 or 1 → 0) a continuous segment of length `k` in the array.
- If it is impossible to convert the entire array to all 1s using such flips, the result should be `-1`.

### Approach:

- The solution uses a custom-implemented `Queue` data structure (based on linked nodes) to manage flipping operations.
- A greedy approach is used: iterate through the array from left to right, and whenever a `0` is found at position `i`, flip the segment starting at `i` of length `k`.
- A helper `flip()` function toggles each bit in the segment.
- After performing all possible flips, the array is checked to confirm if all bits are `1`.
- If yes, the function returns the number of flips performed; otherwise, it returns `-1`.

### Data Structures:

- **Queue**: Implemented using a linked list with a `Node` class.
  - Supports `enqueue`, `dequeue`, `isEmpty`, and `getFront` operations.
  - The queue helps track positions involved in flip operations, although it's mainly illustrative in this implementation.

### Input/Output:

- **Input File**: `inputProblem3.txt`
  - Each line contains a binary array in square brackets, followed by an integer `k`.
  - Example: `[0 0 1 0] 2`

- **Output File**: `output3.txt`
  - For each input line, outputs the minimum number of flips needed, or `-1` if not possible.

### Example:
**Input:**
[0 0 0 1 0] 3
[1 1 1] 2

**Output:**
2
0


### Compilation & Execution:

```bash
g++ Problem3.cpp -o Problem3
./Problem3
```

## Problem 4: Patient Triage System using Max Heap

### Overview:

This problem simulates a hospital's patient triage system using a custom **Max Heap** implementation (without STL). Patients are prioritized based on **severity** (higher is more urgent), and in the case of a tie, by **earlier arrival time**. The solution processes multiple test cases, each consisting of a set of patients, and outputs the treatment order.

### Approach:

* A static array-based **MaxHeap** is used to simulate a priority queue.
* Each `Patient` contains:

  * `name` (string)
  * `severity` (int)
  * `arrival_time` (int)
* The heap maintains the max-heap property where the most critical patient (based on severity and arrival time) is always at the top.
* Patients are inserted into the heap, and then extracted one by one to simulate treatment in the correct order.
* Patients are read from a structured input file that resembles JSON-like entries (e.g., `"name": "John", "severity": 5, "arrival_time": 2`).

### Features:

* **Custom MaxHeap**:

  * Array-based.
  * `insert()`: Maintains heap via `heapifyUp`.
  * `extractMax()`: Removes the top patient and restores heap via `heapifyDown`.
  * No use of STL `priority_queue`.
* **Input Parsing**:

  * Multiple test cases supported.
  * Each test case separated by a blank line.
* **Output**:

  * Displays heap content after each insertion.
  * Shows the order in which patients are treated.

### Code Structure:

* **`Patient` struct**: Stores patient data.
* **`MaxHeap` class**: Implements all heap operations.
* **`readTestCasesFromFile()`**: Reads and parses structured test cases from `patients.txt`.
* **`processTestCase()`**: Simulates inserting patients and extracting them for treatment.
* **`main()`**: Orchestrates reading, processing, and writing results to `output.txt`.

### Input File Format: `inputProblem4.txt`

Each block (separated by a blank line) is a separate test case.

### Output File: `outputProblem4.txt`

The output includes logs of each insertion and extraction for each test case.

### Compilation & Execution:

```bash
g++ Problem4.cpp -o Problem4
./Problem4
```
