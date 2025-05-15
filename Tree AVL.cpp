/* File: Problem2.cpp
 Authors:
 Sara Yasser   : 20230168
 Bassant Ahmed : 20230094
 Section: S16
 GitHub Link: https://github.com/Doha-yasser/DS-implementation
 ---------------------------------------
 NOTE:
 You need to add the file "contect_input" to the cmake file to run the test cases.
 Also the output will be in a file called "contact_output".
---------------------------------------
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Contact {
    int id;
    string name;
    string phone;
    string email;
    Contact* left;
    Contact* right;
    int height;
};

int height(Contact* n) {
    return n ? n->height : 0;
}

int getBalance(Contact* n) {
    return n ? height(n->left) - height(n->right) : 0;
}
Contact* rightRotate(Contact* y) {
    Contact* x = y->left;
    Contact* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Contact* leftRotate(Contact* x) {
    Contact* y = x->right;
    Contact* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Contact* newContact(int id, string name, string phone, string email) {
    Contact* contact = new Contact();
    contact->id = id;
    contact->name = name;
    contact->phone = phone;
    contact->email = email;
    contact->left = contact->right = nullptr;
    contact->height = 1;
    return contact;
}
Contact* checkBalance(Contact* Contact, int id){

    Contact->height = 1 + max(height(Contact->left), height(Contact->right));

    int balance = getBalance(Contact);

    // Left Left
    if (balance > 1 && id < Contact->left->id)
        return rightRotate(Contact);

    // Right Right
    if (balance < -1 && id > Contact->right->id)
        return leftRotate(Contact);

    // Left Right
    if (balance > 1 && id > Contact->left->id) {
        Contact->left = leftRotate(Contact->left);
        return rightRotate(Contact);
    }
    // Right Left
    if (balance < -1 && id < Contact->right->id) {
        Contact->right = rightRotate(Contact->right);
        return leftRotate(Contact);
    }

    return Contact;
}
Contact* insert(Contact* Contact, int id, string name , string phone , string email) {
    if (!Contact)
        return newContact(id, name, phone, email);

    if (id < Contact->id)
        Contact->left = insert(Contact->left, id, name, phone, email);
    else if (id > Contact->id)
        Contact->right = insert(Contact->right, id, name, phone, email);
    else{
        cout << "Error: The contact with ID " << id << " already exists!\n";
        return Contact;
    }
    return checkBalance(Contact, id);
}
Contact* search(Contact* root, int id) {
    if (!root) {
        cout << "\nError: Contact not found!\n";
        return nullptr;
    }
    if(root->id == id){
        cout << "\nContact found\n";
        return root;
    }else if(root->id < id){
        return search(root->left, id);
    }else if(root->id > id){
        return search(root->right, id);
    }else{
        cout << "\nError: Contact not found!\n";
        return nullptr;
    }
}
Contact* minValueNode(Contact* node) {
    Contact* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Contact* deleteContact(Contact* root, int id) {
    if (!root) {
        cout << "Error: Contact not found!\n";
        return nullptr;
    }

    if (id < root->id)
        root->left = deleteContact(root->left, id);
    else if (id > root->id)
        root->right = deleteContact(root->right, id);
    else {
        // Node found
        if (!root->left || !root->right) {
            Contact* temp = root->left ? root->left : root->right;

            // No child case
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                // One child case
                *root = *temp;
            }
            delete temp;
        } else {
            // Two children case
            Contact* temp = minValueNode(root->right);
            root->id = temp->id;
            root->name = temp->name;
            root->phone = temp->phone;
            root->email = temp->email;
            root->right = deleteContact(root->right, temp->id);
        }
        cout << "\nContact deleted successfully.\n";
    }

    if (!root) return root;

    return checkBalance(root, id);
}
void listContacts(Contact* root) {
    if (!root) return;
    listContacts(root->left);
    cout << "ID: " << root->id << ", Name: " << root->name
         << ", Phone: " << root->phone << ", Email: " << root->email << "\n";
    listContacts(root->right);
}

void printTree(Contact* root, int space = 0, int indent = 6) {
    if (!root) return;

    space += indent;
    printTree(root->right, space);
    cout << setw(space) << root->id << "\n";
    printTree(root->left, space);
}

int main() {
    ifstream testInput("contact_input.txt");
    if (!testInput) {
        cerr << "Error: Input file 'contact_input.txt' not found.\n";
        return 1;
    }
    testInput.close();
    freopen("contact_input.txt", "r", stdin);   // Redirect cin
    freopen("contact_output.txt", "w", stdout); // Redirect cout

    Contact* root = nullptr;
    int choice;

    do {
        cout << "\nAddress Book Application\n"
             << "------------------------\n"
             << "1. Add New Contact\n"
             << "2. Search for Contact\n"
             << "3. Delete Contact\n"
             << "4. List All Contacts (Sorted by ID)\n"
             << "5. Display Current Tree Structure\n"
             << "6. Exit\n"
             << "Enter operation: ";
        cin >> choice;
        cout << choice << "\n";

        switch (choice) {
            case 1: {
                int id;
                string name, phone, email;
                cout << "Enter unique ID (integer): ";
                cin >> id;
                cout << id << "\n";
                cin.ignore();

                cout << "Enter name: ";
                getline(cin, name);
                cout << name << "\n";

                cout << "Enter phone: ";
                getline(cin, phone);
                cout << phone << "\n";

                cout << "Enter email: ";
                getline(cin, email);
                cout << email << "\n";

                root = insert(root, id, name, phone, email);
                break;
            }
            case 2: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                cout << id << "\n";
                Contact* found = search(root, id);
                if (found) {
                    
                    cout << "ID: " << found->id << "\n";
                    cout << "Name: " << found->name << "\n";
                    cout << "Phone: " << found->phone << "\n";
                    cout << "Email: " << found->email << "\n";
                }
                break;
            }
            case 3: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                cout << id << "\n";
                root = deleteContact(root, id);
                break;
            }
            case 4: {
                cout << "\nContacts in Address Book (sorted by ID):\n";
                if (!root)
                    cout << "Address Book is empty.\n";
                else
                    listContacts(root);
                break;
            }
            case 5: {
                cout << "\nCurrent AVL Tree:\n";
                printTree(root);
                break;
            }
            case 6:
                cout << "Exiting Address Book. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}