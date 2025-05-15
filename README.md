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

## Problem 3: Minimum Segment Flips
###Overview:
This problem involves finding the minimum number of segment flips required to convert a binary array into an array of all 1s. Each flip toggles (0 → 1 or 1 → 0) a continuous segment of length k in the array. If it is impossible to convert the entire array to all 1s using such flips, the result should be -1.

###Approach:
The solution uses a custom implemented Queue data structure (based on linked nodes) to help manage flipping operations efficiently.

The flipping is done greedily from left to right: whenever a 0 is encountered at position i, flip the segment starting at i of length k.

The code manually toggles the bits in the segment (0 to 1 and 1 to 0) using a helper flip function.

After attempting all possible flips, the array is checked to confirm if all bits are 1.

If all are 1, returns the count of flips performed; otherwise, returns -1.

###Data Structures:
Queue: implemented using a linked list with Node class. It supports enqueue, dequeue, checking if empty, and getting the front element.

The queue here helps track the positions involved in flipping operations (though in this code snippet, the queue usage seems minimal and mainly for demonstration).

###Input/Output:
The program reads input from a file named inputProblem3.txt.

Each line contains a binary array in brackets, e.g., [0 1 0 1], followed by an integer k.

Outputs the minimum number of flips needed or -1 if not possible.

Results are written to output3.txt.

## Problem 4: Emergency Room Max-Heap

## Notes

- Memory Management: All code manually manages memory (no memory leaks).

- Input Handling: Each problem reads from a file.

- STL Replacement: Custom implementations for stacks, trees, heaps, etc.

## Test Cases
Sample inputs are provided in respective inputProblemX.txt files. Modify these to test different scenarios.

