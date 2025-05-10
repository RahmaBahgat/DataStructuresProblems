# DS-implementation

## Overview
This repository contains solutions to four programming problems, each implemented in C++ without using the STL library. Each problem is in a separate .cpp file and demonstrates custom data structure implementations.

## Problem 1: Browser History with Stacks
### Approach:

- Uses two stacks (backStack and forwardStack) to manage navigation history.

- visit(url): Pushes to backStack, clears forwardStack.

= goBack(): Moves current URL from backStack to forwardStack.

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

## Problem 4: Emergency Room Max-Heap

## Notes

- Memory Management: All code manually manages memory (no memory leaks).

- Input Handling: Each problem reads from a file.

- STL Replacement: Custom implementations for stacks, trees, heaps, etc.

## Test Cases
Sample inputs are provided in respective inputProblemX.txt files. Modify these to test different scenarios.

