// About: Minimum flips to make binary array all ones using queue
// Related file: input2.txt && output3.txt
// Author: Doha yasser
// Id: 20231089

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int minFlip(int *arr, int n, int k);

void readFromFile(string fileName)
{
    ifstream input(fileName);
    ofstream output("output3.txt");

    if (!input.is_open())
    {
        cout << "File does not open\n";
        return;
    }
    cout << "File open successfully!!\n";

    string line;
    while (getline(input, line))
    {
        int arr[100]; // max array size
        int size = 0;
        int k = 0;

        bool inArray = false;
        for (char c : line)
        {
            if (c == '[')
            {
                inArray = true;
                continue;
            }
            if (c == ']')
            {
                inArray = false;
                continue;
            }
            if (inArray && (c == '0' || c == '1'))
            {
                arr[size++] = c - '0';
            }
        }

        // k = int(line[line.length()-1]) - '0';       if 1 to 9
        string kStr = line.substr(line.find(']') + 1);
        k = stoi(kStr);

        int result = minFlip(arr, size, k);
        output << result << "\n";
    }
    input.close();
    output.close();

    cout << "done successfully!!\n";
    return;
}

class Node
{
private:
    int data;
    Node *next;

public:
    Node(int val) : data(val), next(nullptr) {};
    int getData()
    {
        return data;
    }
    void setData(int val)
    {
        data = val;
    }
    Node *getNext()
    {
        return next;
    }
    void setNext(Node *node)
    {
        next = node;
    }
};

class Queue
{
private:
    Node *front; // refer to the first item
    Node *end;   // refer to the last item not null (end -> next == null)
    int count;

public:
    Queue() : front(nullptr), end(nullptr), count(0) {}

    void enqueue(int val)
    {
        Node *newNode = new Node(val); // if object will delte at the end of function and cannot use it in dequeue
        if (end == nullptr)
        { // queue is Empty
            front = end = newNode;
        }
        else
        {
            end->setNext(newNode);
            end = newNode;
        }
        count++;
    }

    void dequeue()
    {
        if (front == nullptr)
        {
            cout << "Queue is Empty";
        }
        else
        {
            Node *temp = front;
            front = front->getNext();

            if (front == nullptr)
            { // if front after moving be null then end will be null
                end = nullptr;
            }
            delete temp;
            count--;
        }
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    int getFront()
    {
        if (front == nullptr)
        {
            cout << "Queue is empty";
            return -1; // or throw an exception
        }
        return front->getData();
    }

    int size() { return count; }

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
};

int flip(int val)
{
    return (val == 1) ? 0 : 1;
}

 int minFlip(int *arr, int n, int k)
 {

 Queue q;
 int count = 0;

 // return 4;

 for (int i = 0; i < n - k + 1; i++)
 {

     if (arr[i] == 0)
     {
         count++;
         for (int j = i; j < i + k; j++)
         {
             arr[j] = flip(arr[j]);
             if (arr[j] == 0)
             {
                 q.enqueue(j);
                 i = j;
             }
         }
     }
 }

 // check if array becomes one
 for (int i = 0; i < n; i++)
 {
     if (arr[i] == 0)
         count = -1;
 }

 return count;

 }



int main()
{

    // int arr[] = {0, 1, 0, 1};
    // int arr[] = {0, 0, 0, 1, 0, 1, 1, 0};
    // int k = 3;

    // int result = minFlip(arr, 8,k);
    // cout << "Min flipped: " << result << endl;

    readFromFile("input3.txt");
}

// correct out
//-1
//1
//2
//0
//1
//0
//-1
//1
//-1

