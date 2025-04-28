#include <iostream>
using namespace std;

// Structure of each node in BST
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

// Insert a value into BST
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Inorder Traversal (Left, Root, Right)
void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

// Find the number of nodes in the longest path (i.e., height of the tree)
int longestPathLength(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = longestPathLength(root->left);
    int rightHeight = longestPathLength(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Find minimum value in BST
int findMin(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return -1;
    }
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

// Swap left and right pointers of all nodes (mirror the tree)
void mirrorTree(Node* root) {
    if (root == nullptr) return;
    
    // Swap left and right
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Search for a value in BST
bool search(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    else if (key < root->data) return search(root->left, key);
    else return search(root->right, key);
}

// Free the tree memory
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int n;
    
    cout << "Enter number of nodes to insert initially: ";
    cin >> n;
    
    cout << "Enter values: ";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        root = insert(root, value);
    }
    
    cout << "\nInorder Traversal of BST: ";
    inorderTraversal(root);
    cout << endl;
    
    // Insert a new node
    int newValue;
    cout << "\nEnter a value to insert into BST: ";
    cin >> newValue;
    root = insert(root, newValue);
    
    cout << "Inorder Traversal after insertion: ";
    inorderTraversal(root);
    cout << endl;
    
    // Find longest path
    cout << "\nNumber of nodes in longest path (Height): " << longestPathLength(root) << endl;
    
    // Find minimum value
    cout << "Minimum value in BST: " << findMin(root) << endl;
    
    // Mirror the tree
    mirrorTree(root);
    cout << "\nInorder Traversal after mirroring: ";
    inorderTraversal(root);
    cout << endl;
    
    // Search for a value
    int searchValue;
    cout << "\nEnter a value to search: ";
    cin >> searchValue;
    if (search(root, searchValue)) {
        cout << searchValue << " is found in the BST.\n";
    } else {
        cout << searchValue << " is NOT found in the BST.\n";
    }
    
    // Clean up
    deleteTree(root);
    
    return 0;
}
