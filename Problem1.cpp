#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    string data;
    Node* next;

    Node(const string& val) {
        data = val;
        next = nullptr;
    }
};

class Stack {
private:
    Node* root;

public:
    Stack() {
        root = nullptr;
    }

    ~Stack() {
        clear();
    }

    // Push a new value onto the stack
    void push(const string& val) {
        Node* newNode = new Node(val);
        newNode->next = root;
        root = newNode;
    }

    // Pop the top value from the stack
    void pop() {
        if (root != nullptr) {
            Node* temp = root;
            root = root->next;
            delete temp;
        }
    }

    // Return the top value without removing it
    string top() const {
        if (root != nullptr) {
            return root->data;
        }
        return "";
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return root == nullptr;
    }

    // Remove all elements from the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class BrowserHistory {
private:
    Stack back;
    Stack forward;
    string currentUrl;

public:
    BrowserHistory() {
        currentUrl = "";
    }

    // Visit a new URL
    void visit(const string& url, ofstream& out) {
        if (!currentUrl.empty()) {
            back.push(currentUrl); // save current to back
        }
        currentUrl = url;
        forward.clear(); // clear forward history
        out << "Visited: " << currentUrl << endl;
    }

    // Go back in history
    void goBack(ofstream& out) {
        if (back.isEmpty()) {
            out << "Cannot go back" << endl;
            return;
        }
        forward.push(currentUrl); // current becomes forward
        currentUrl = back.top();  // previous becomes current
        back.pop();
        out << "Went back to: " << currentUrl << endl;
    }

    // Go forward in history
    void goForward(ofstream& out) {
        if (forward.isEmpty()) {
            out << "Cannot go forward" << endl;
            return;
        }
        back.push(currentUrl); // current becomes back
        currentUrl = forward.top(); // forward becomes current
        forward.pop();
        out << "Went forward to: " << currentUrl << endl;
    }

    // Return the currently visited URL
    string getCurrentUrl() const {
        return currentUrl;
    }
};

int main() {
    ifstream inputFile("inputProblem1.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open output.txt" << endl;
        return 1;
    }

    BrowserHistory browser;
    string command, url;

    // Read command by command
    while (inputFile >> command) {
        if (command == "visit") {
            inputFile.ignore(); // ignore whitespace
            getline(inputFile, url); // read full line for URL
            browser.visit(url, outputFile);
        } else if (command == "back") {
            browser.goBack(outputFile);
        } else if (command == "forward") {
            browser.goForward(outputFile);
        } else {
            outputFile << "Unknown command: " << command << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
