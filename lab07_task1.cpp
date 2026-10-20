#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Task 1.	Generate a Binary Tree from the Given String
Node* buildTree(const string& s, int& i) {
    if (i >= (int)s.length() || s[i] == ',' || s[i] == ')')
        return nullptr;

    Node* root = new Node(s[i]);
    i++;

    if (i < (int)s.length() && s[i] == '(') {
        i++;

        root->left = buildTree(s, i);

        if (i < (int)s.length() && s[i] == ',')
            i++;

        root->right = buildTree(s, i);

        if (i < (int)s.length() && s[i] == ')')
            i++;
    }

    return root;
}

// Task 2.	Generate Preorder Form (Recursive)
void preorder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->data;
    preorder(root->left);
    preorder(root->right);
}

// Task 3.	Generate Inorder Form (Using Linear ADT)
void inorderIterative(Node* root) {
    stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();

        cout << current->data;
        current = current->right;
    }
}

// Task 4: Generate Postorder Form (Iterative)
void postorderIterative(Node* root) {
    if (root == nullptr)
        return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();

        s2.push(current);

        if (current->left != nullptr)
            s1.push(current->left);

        if (current->right != nullptr)
            s1.push(current->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
}

// Task 5: Validate the string without building a tree
bool parseNodeString(const string& s, int& i) {
    if (i >= (int)s.length() ||
        s[i] == '(' || s[i] == ')' || s[i] == ',')
        return false;

    i++;

    if (i < (int)s.length() && s[i] == '(') {
        i++;

        if (i < (int)s.length() && s[i] != ',') {
            if (!parseNodeString(s, i))
                return false;
        }

        if (i >= (int)s.length() || s[i] != ',')
            return false;

        i++;

        if (i < (int)s.length() && s[i] != ')') {
            if (!parseNodeString(s, i))
                return false;
        }

        if (i >= (int)s.length() || s[i] != ')')
            return false;

        i++;
    }

    return true;
}

bool validateTreeString(const string& s) {
    if (s.empty())
        return false;

    int i = 0;

    return parseNodeString(s, i) && i == (int)s.length();
}

// Task 6: Calculate the height of the tree
int height(Node* root) {
    if (root == nullptr)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;
}

// Task 6: Calculate the Depth of the Tree
void displayDepth(Node* root, int depth) {
    if (root == nullptr)
        return;

    cout << root->data << ": " << depth << endl;

    displayDepth(root->left, depth + 1);
    displayDepth(root->right, depth + 1);
}

// Task 7: Generate a BST from a Sequence of Integers
class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

BSTNode* insertBST(BSTNode* root, int value) {
    if (root == nullptr)
        return new BSTNode(value);

    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);

    return root;
}

void inorderBST(BSTNode* root) {
    if (root == nullptr)
        return;

    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}

void deleteTree(Node* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void deleteBST(BSTNode* root) {
    if (root == nullptr)
        return;

    deleteBST(root->left);
    deleteBST(root->right);
    delete root;
}

int main() {
    string treeString = "a(b(d,e),c(,f(g,)))";
    cout << "The treeString is: " << treeString << endl;

    int index = 0;
    Node* root = buildTree(treeString, index);

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorderIterative(root);
    cout << endl;

    cout << "Postorder: ";
    postorderIterative(root);
    cout << endl;

    cout << "Valid tree string: ";
    cout << (validateTreeString(treeString) ? "Yes" : "No") << endl;

    cout << "Tree height: " << height(root) << endl;

    cout << "Node depths:" << endl;
    displayDepth(root, 0);

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int size = sizeof(values) / sizeof(values[0]);

    BSTNode* bstRoot = nullptr;

    for (int i = 0; i < size; i++)
        bstRoot = insertBST(bstRoot, values[i]);

    cout << "BST inorder: ";
    inorderBST(bstRoot);
    cout << endl;

    deleteTree(root);
    deleteBST(bstRoot);

    return 0;
}
