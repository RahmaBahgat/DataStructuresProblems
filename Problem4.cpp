#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Stores patient data
struct Patient {
    string name;        // Patient name
    int severity;       // Condition severity (higher = worse)
    int arrival_time;   // Arrival order (lower = earlier)
};

// Priority queue implementation
class MaxHeap {
private:
    vector<Patient> heap;  // Stores patients in heap order

    // Compare two patients' priority
    bool hasHigherPriority(const Patient& a, const Patient& b) {
        if (a.severity > b.severity) return true;
        if (a.severity == b.severity) return a.arrival_time < b.arrival_time;
        return false;
    }

    // Fix heap after insertion (bubble up)
    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (hasHigherPriority(heap[index], heap[parent])) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    // Fix heap after extraction (bubble down)
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.size() && hasHigherPriority(heap[left], heap[largest])) {
            largest = left;
        }
        if (right < heap.size() && hasHigherPriority(heap[right], heap[largest])) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Add new patient
    void insert(const Patient& patient) {
        heap.push_back(patient);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return top priority patient
    Patient extractMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        Patient maxPatient = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return maxPatient;
    }

    // Print current heap contents
    void printHeap(ostream& out) const {
        out << "Heap: [";
        for (size_t i = 0; i < heap.size(); ++i) {
            out << heap[i].name;
            if (i != heap.size() - 1) out << ", ";
        }
        out << "]" << endl;
    }

    // Check if heap is empty
    bool isEmpty() const {
        return heap.empty();
    }
};

// Read test cases from file
vector<vector<Patient>> readTestCasesFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<Patient>> testCases;
    vector<Patient> currentTestCase;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return testCases;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            if (!currentTestCase.empty()) {
                testCases.push_back(currentTestCase);
                currentTestCase.clear();
            }
            continue;
        }

        Patient p;
        size_t nameStart = line.find("\"name\": \"") + 9;
        p.name = line.substr(nameStart, line.find("\"", nameStart) - nameStart);

        size_t severityStart = line.find("\"severity\": ") + 11;
        p.severity = stoi(line.substr(severityStart, line.find(",", severityStart) - severityStart));

        size_t timeStart = line.find("\"arrival_time\": ") + 16;
        p.arrival_time = stoi(line.substr(timeStart, line.find("}", timeStart) - timeStart));

        currentTestCase.push_back(p);
    }

    if (!currentTestCase.empty()) {
        testCases.push_back(currentTestCase);
    }

    file.close();
    return testCases;
}

// Process one test case
void processTestCase(const vector<Patient>& patients, int testCaseNumber, ofstream& outFile) {
    MaxHeap priorityQueue;

    outFile << "\n=== Test Case #" << testCaseNumber << " ===" << endl;
    outFile << "Inserting patients:" << endl;

    for (const auto& patient : patients) {
        outFile << "Inserting: " << patient.name << endl;
        priorityQueue.insert(patient);
        priorityQueue.printHeap(outFile);
    }

    outFile << "\nTreatment Order:" << endl;
    while (!priorityQueue.isEmpty()) {
        outFile << "Treating: " << priorityQueue.extractMax().name << endl;
    }
}

int main() {
    string inputFilename = "patients.txt";
    string outputFilename = "output.txt";

    vector<vector<Patient>> testCases = readTestCasesFromFile(inputFilename);
    ofstream outFile(outputFilename);

    if (!outFile.is_open()) {
        cerr << "Error creating output file!" << endl;
        return 1;
    }

    if (testCases.empty()) {
        outFile << "The input file is empty." << endl;
    }

    for (size_t i = 0; i < testCases.size(); ++i) {
        processTestCase(testCases[i], i + 1, outFile);
    }

    outFile.close();
    cout << "Output saved to " << outputFilename << endl;
    return 0;
}
