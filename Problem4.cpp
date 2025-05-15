/* File: Problem4.cpp
 Authors: Rahma Bahgat
 ID: 20231056
 Section: S16
 GitHub Link: https://github.com/Doha-yasser/DS-implementation
 ---------------------------------------
 NOTE:
 You need to add the file "inputProblem4" to the cmake file to run the test cases.
 Also the output will be in a file called "outputProblem4".
---------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Constants to define limits
const int MAX_PATIENTS = 1000;
const int MAX_TEST_CASES = 10;
const int MAX_PATIENTS_PER_TEST = 100;

// Structure to store patient data
struct Patient {
    string name;
    int severity{};         // Higher severity = higher priority
    int arrival_time{};
};

// Custom MaxHeap class (priority queue)
class MaxHeap {
private:
    Patient heap[MAX_PATIENTS];   // Static array to store heap
    int size;                     // Current number of elements in the heap

    // Determines which patient has higher priority
    bool hasHigherPriority(const Patient& a, const Patient& b) {
        if (a.severity > b.severity) return true;
        if (a.severity == b.severity) return a.arrival_time < b.arrival_time;
        return false;
    }

    // Swaps two Patient objects
    void swapPatients(Patient& a, Patient& b) {
        Patient temp = a;
        a = b;
        b = temp;
    }

    // Maintains max-heap property from bottom to top
    void heapifyUp(int index) {
        if (index == 0) return;  // Root node
        int parent = (index - 1) / 2;
        if (hasHigherPriority(heap[index], heap[parent])) {
            swapPatients(heap[index], heap[parent]);
            heapifyUp(parent);  // Recur up the tree
        }
    }

    // Maintains max-heap property from top to bottom
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && hasHigherPriority(heap[left], heap[largest])) {
            largest = left;
        }
        if (right < size && hasHigherPriority(heap[right], heap[largest])) {
            largest = right;
        }

        if (largest != index) {
            swapPatients(heap[index], heap[largest]);
            heapifyDown(largest);  // Recur down the tree
        }
    }

public:
    // Constructor to initialize heap size
    MaxHeap() : size(0) {}

    // Inserts a patient into the heap
    void insert(const Patient& patient) {
        if (size >= MAX_PATIENTS) {
            cerr << "Heap full, cannot insert more patients!" << endl;
            return;
        }
        heap[size] = patient;
        heapifyUp(size);
        size++;
    }

    // Extracts the patient with the highest priority
    Patient extractMax() {
        if (size == 0) {
            throw runtime_error("Heap is empty");
        }

        Patient maxPatient = heap[0];           // Root is the max
        heap[0] = heap[size - 1];               // Replace root with last element
        size--;                                 // Reduce size
        if (size > 0) {
            heapifyDown(0);                     // Restore heap property
        }
        return maxPatient;
    }

    // Prints current heap contents (names only)
    void printHeap(ostream& out) const {
        out << "Heap: [";
        for (int i = 0; i < size; ++i) {
            out << heap[i].name;
            if (i != size - 1) out << ", ";
        }
        out << "]" << endl;
    }

    // Checks if heap is empty
    bool isEmpty() const {
        return size == 0;
    }
};

// Reads test cases from a file into a 2D array of patients
void readTestCasesFromFile(const string& filename, Patient testCases[MAX_TEST_CASES][MAX_PATIENTS_PER_TEST],
                           int testCaseSizes[MAX_TEST_CASES], int& numTestCases) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        numTestCases = 0;
        return;
    }

    numTestCases = 0;
    int currentPatient = 0;
    string line;

    // Read line by line
    while (getline(file, line)) {
        if (line.empty()) {
            // Blank line indicates end of a test case
            if (currentPatient > 0) {
                testCaseSizes[numTestCases] = currentPatient;
                numTestCases++;
                currentPatient = 0;
            }
            continue;
        }

        if (numTestCases >= MAX_TEST_CASES || currentPatient >= MAX_PATIENTS_PER_TEST) {
            cerr << "Warning: Exceeded maximum test cases or patients per test case" << endl;
            continue;
        }

        // Parse patient data from line (assumes structured text input)
        Patient p;
        size_t nameStart = line.find("\"name\": \"") + 9;
        p.name = line.substr(nameStart, line.find("\"", nameStart) - nameStart);

        size_t severityStart = line.find("\"severity\": ") + 11;
        p.severity = stoi(line.substr(severityStart, line.find(",", severityStart) - severityStart));

        size_t timeStart = line.find("\"arrival_time\": ") + 16;
        p.arrival_time = stoi(line.substr(timeStart, line.find("}", timeStart) - timeStart));

        testCases[numTestCases][currentPatient] = p;
        currentPatient++;
    }

    // Final test case (in case file doesn't end with blank line)
    if (currentPatient > 0) {
        testCaseSizes[numTestCases] = currentPatient;
        numTestCases++;
    }

    file.close();
}

// Processes a single test case: inserts patients and simulates treatment order
void processTestCase(Patient patients[], int count, int testCaseNumber, ofstream& outFile) {
    MaxHeap priorityQueue;

    outFile << "\n=== Test Case #" << testCaseNumber << " ===" << endl;
    outFile << "Inserting patients:" << endl;

    // Insert all patients into priority queue
    for (int i = 0; i < count; ++i) {
        outFile << "Inserting: " << patients[i].name << endl;
        priorityQueue.insert(patients[i]);
        priorityQueue.printHeap(outFile);
    }

    // Extract and print treatment order
    outFile << "\nTreatment Order:" << endl;
    while (!priorityQueue.isEmpty()) {
        outFile << "Treating: " << priorityQueue.extractMax().name << endl;
    }
}

// Main function: reads from file, processes test cases, writes output
int main() {
    string inputFilename = "inputProblem4.txt";
    string outputFilename = "outputProblem4.txt";

    // Data structures to hold multiple test cases
    Patient testCases[MAX_TEST_CASES][MAX_PATIENTS_PER_TEST];
    int testCaseSizes[MAX_TEST_CASES];
    int numTestCases = 0;

    // Load patients from input file
    readTestCasesFromFile(inputFilename, testCases, testCaseSizes, numTestCases);
    ofstream outFile(outputFilename);

    if (!outFile.is_open()) {
        cerr << "Error creating output file!" << endl;
        return 1;
    }

    // Handle case with no test cases
    if (numTestCases == 0) {
        outFile << "No test cases found in input file." << endl;
    } else {
        // Process each test case one by one
        for (int i = 0; i < numTestCases; ++i) {
            processTestCase(testCases[i], testCaseSizes[i], i + 1, outFile);
        }
    }

    outFile.close();
    cout << "Output saved to " << outputFilename << endl;
    return 0;
}
