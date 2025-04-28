#include <iostream>
#include <string>
using namespace std;

// Node structure representing each part: book, chapter, section, or subsection
struct Node {
    string data;         
    Node* nextSibling;   
    Node* firstChild;    
    
    Node(string value) {
        data = value;
        nextSibling = nullptr;
        firstChild = nullptr;
    }
};

// Insert a child node under a parent
void insertChild(Node* parent, string childData) {
    Node* child = new Node(childData);
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        Node* temp = parent->firstChild;
        while (temp->nextSibling) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Display the tree recursively
void displayTree(Node* node, int level = 0) {
    if (node == nullptr) return;

    for (int i = 0; i < level; i++) {
        cout << "\t";  // Indentation based on level
    }
    cout << node->data << endl;

    displayTree(node->firstChild, level + 1);  // Recur for children
    displayTree(node->nextSibling, level);     // Recur for siblings
}

// Free the memory by deleting nodes recursively
void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->firstChild);
    deleteTree(node->nextSibling);
    delete node;
}

int main() {
    string bookTitle;
    cout << "Enter the title of the book: ";
    getline(cin, bookTitle);

    Node* book = new Node(bookTitle);

    int numChapters;
    cout << "Enter the number of chapters in the book: ";
    cin >> numChapters;
    cin.ignore();  // Clear input buffer

    for (int i = 0; i < numChapters; i++) {
        string chapterTitle;
        cout << "Enter the title of chapter " << (i + 1) << ": ";
        getline(cin, chapterTitle);

        insertChild(book, chapterTitle);

        int numSections;
        cout << "Enter the number of sections in chapter " << chapterTitle << ": ";
        cin >> numSections;
        cin.ignore();

        Node* chapterNode = book->firstChild;
        while (chapterNode) {
            if (chapterNode->data == chapterTitle) {
                for (int j = 0; j < numSections; j++) {
                    string sectionTitle;
                    cout << "Enter the title of section " << (j + 1) << " in chapter " << chapterTitle << ": ";
                    getline(cin, sectionTitle);

                    insertChild(chapterNode, sectionTitle);

                    int numSubsections;
                    cout << "Enter the number of subsections in section " << sectionTitle << ": ";
                    cin >> numSubsections;
                    cin.ignore();

                    Node* sectionNode = chapterNode->firstChild;
                    while (sectionNode) {
                        if (sectionNode->data == sectionTitle) {
                            for (int k = 0; k < numSubsections; k++) {
                                string subsectionTitle;
                                cout << "Enter the title of subsection " << (k + 1) << " in section " << sectionTitle << ": ";
                                getline(cin, subsectionTitle);

                                insertChild(sectionNode, subsectionTitle);
                            }
                            break;
                        }
                        sectionNode = sectionNode->nextSibling;
                    }
                }
                break;
            }
            chapterNode = chapterNode->nextSibling;
        }
    }

    // Display the tree structure
    cout << "\nBook Structure:\n";
    displayTree(book);

    // Free memory
    deleteTree(book);

    return 0;
}


