#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;

    Student(int id, string n, float g) {
        studentID = id;
        name = n;
        GPA = g;
        left = nullptr;
        right = nullptr;
    }
};

//SubTask3: 3.	Implement BST operations
class StudentBST {
private:
    Student* root;

    Student* insert(Student* node, int id, string name, float gpa) {
        if (node == nullptr)
            return new Student(id, name, gpa);

        if (id < node->studentID)
            node->left = insert(node->left, id, name, gpa);
        else if (id > node->studentID)
            node->right = insert(node->right, id, name, gpa);

        return node;
    }

    Student* search(Student* node, int id) {
        if (node == nullptr || node->studentID == id)
            return node;

        if (id < node->studentID)
            return search(node->left, id);

        return search(node->right, id);
    }

    Student* findMin(Student* node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    Student* deleteStudent(Student* node, int id) {
        if (node == nullptr)
            return nullptr;

        if (id < node->studentID) {
            node->left = deleteStudent(node->left, id);
        }
        else if (id > node->studentID) {
            node->right = deleteStudent(node->right, id);
        }
        else {
            if (node->left == nullptr) {
                Student* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Student* temp = node->left;
                delete node;
                return temp;
            }

            Student* temp = findMin(node->right);

            node->studentID = temp->studentID;
            node->name = temp->name;
            node->GPA = temp->GPA;

            node->right = deleteStudent(
                node->right, temp->studentID
            );
        }

        return node;
    }

    //SubTask4: Inorder Function
    void inorder(Student* node) {
        if (node == nullptr)
            return;

        inorder(node->left);

        cout << "ID: " << node->studentID
             << ", Name: " << node->name
             << ", GPA: " << node->GPA << endl;

        inorder(node->right);
    }

    //SubTask5: ANALYTICAL qUESTION 
    int countStudents(Student* node) {
        if (node == nullptr)
            return 0;

        return 1 + countStudents(node->left)
                 + countStudents(node->right);
    }

    Student* highestGPA(Student* node, Student* best) {
        if (node == nullptr)
            return best;

        if (best == nullptr || node->GPA > best->GPA)
            best = node;

        best = highestGPA(node->left, best);
        best = highestGPA(node->right, best);

        return best;
    }

    Student* lowestGPA(Student* node, Student* best) {
        if (node == nullptr)
            return best;

        if (best == nullptr || node->GPA < best->GPA)
            best = node;

        best = lowestGPA(node->left, best);
        best = lowestGPA(node->right, best);

        return best;
    }

    void displayAboveGPA(Student* node, float threshold) {
        if (node == nullptr)
            return;

        displayAboveGPA(node->left, threshold);

        if (node->GPA > threshold) {
            cout << "ID: " << node->studentID
                 << ", Name: " << node->name
                 << ", GPA: " << node->GPA << endl;
        }

        displayAboveGPA(node->right, threshold);
    }

    void destroy(Student* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    StudentBST() {
        root = nullptr;
    }

    ~StudentBST() {
        destroy(root);
    }

    void Insert(int id, string name, float gpa) {
        if (search(root, id) != nullptr) {
            cout << "Student ID already exists.\n";
            return;
        }

        root = insert(root, id, name, gpa);
        cout << "Student inserted successfully.\n";
    }

    void Search(int id) {
        Student* result = search(root, id);

        if (result == nullptr) {
            cout << "Student not found.\n";
            return;
        }

        cout << "ID: " << result->studentID
             << ", Name: " << result->name
             << ", GPA: " << result->GPA << endl;
    }

    void Delete(int id) {
        if (search(root, id) == nullptr) {
            cout << "Student not found.\n";
            return;
        }

        root = deleteStudent(root, id);
        cout << "Student deleted successfully.\n";
    }

    void DisplayInorder() {
        inorder(root);
    }

    void DisplayCount() {
        cout << "Total students: "
             << countStudents(root) << endl;
    }

    void DisplayHighestGPA() {
        Student* result = highestGPA(root, nullptr);

        if (result == nullptr) {
            cout << "No student records available.\n";
            return;
        }

        cout << "Highest GPA: " << result->name
             << " (ID: " << result->studentID
             << ", GPA: " << result->GPA << ")\n";
    }

    void DisplayLowestGPA() {
        Student* result = lowestGPA(root, nullptr);

        if (result == nullptr) {
            cout << "No student records available.\n";
            return;
        }

        cout << "Lowest GPA: " << result->name
             << " (ID: " << result->studentID
             << ", GPA: " << result->GPA << ")\n";
    }

    void DisplayAboveGPA(float threshold) {
        cout << "Students with GPA above " << threshold
             << ":\n";

        displayAboveGPA(root, threshold);
    }
};

int main() {
    StudentBST bst;

    bst.Insert(103, "Ali", 3.5);
    bst.Insert(101, "Sara", 3.9);
    bst.Insert(105, "Ahmed", 2.8);
    bst.Insert(102, "Ayesha", 3.2);
    bst.Insert(104, "Usman", 3.7);

    cout << "\nStudents sorted by ID:\n";
    bst.DisplayInorder();

    cout << "\nSearch for ID 102:\n";
    bst.Search(102);

    cout << "\nTotal students:\n";
    bst.DisplayCount();

    cout << "\nHighest GPA:\n";
    bst.DisplayHighestGPA();

    cout << "\nLowest GPA:\n";
    bst.DisplayLowestGPA();

    cout << "\nGPA threshold 3.0:\n";
    bst.DisplayAboveGPA(3.0);

    cout << "\nDelete student ID 103:\n";
    bst.Delete(103);

    cout << "\nStudents after deletion:\n";
    bst.DisplayInorder();

    return 0;
}
