#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int id;
    string name;
    float marks;

public:
    // Function to input student data
    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    // Function to display student data
    void display() const {
        cout << "ID: " << id << "\nName: " << name << "\nMarks: " << marks << endl;
    }

    // Getter for ID
    int getID() const {
        return id;
    }

    // Getter for Marks
    float getMarks() const {
        return marks;
    }
};

// Function to add a student record to the file
void addStudent() {
    Student student;
    ofstream outFile("students.dat", ios::binary | ios::app);
    student.input();
    outFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
    outFile.close();
    cout << "Student record added successfully.\n";
}

// Function to display all student records from the file
void displayAllStudents() {
    Student student;
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "Error in opening file.\n";
        return;
    }
    cout << "\n\nDisplaying All Students:\n";
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        student.display();
        cout << "-----------------------\n";
    }
    inFile.close();
}

// Function to search for a student by ID
void searchStudent(int id) {
    Student student;
    ifstream inFile("students.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.getID() == id) {
            student.display();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "Student not found.\n";
}

// Function to delete a student record by ID
void deleteStudent(int id) {
    Student student;
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.getID() == id) {
            found = true;
        } else {
            outFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student record deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

// Function to display students with marks greater than or equal to the specified value
void displayStudentsWithMarks(float minMarks) {
    Student student;
    ifstream inFile("students.dat", ios::binary);
    bool found = false;
    if (!inFile) {
        cout << "Error in opening file.\n";
        return;
    }

    cout << "\n\nDisplaying Students with Marks >= " << minMarks << ":\n";
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.getMarks() >= minMarks) {
            student.display();
            cout << "-----------------------\n";
            found = true;
        }
    }
    inFile.close();

    if (!found) {
        cout << "No student found with marks >= " << minMarks << ".\n";
    }
}

// Main menu function
int main() {
    int choice, id;
    float marks;

    do {
        cout << "\n\n*** Student Management System ***\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Delete Student by ID\n";
        cout << "5. Display Students with Marks >= X\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAllStudents();
            break;
        case 3:
            cout << "Enter ID to search: ";
            cin >> id;
            searchStudent(id);
            break;
        case 4:
            cout << "Enter ID to delete: ";
            cin >> id;
            deleteStudent(id);
            break;
        case 5:
            cout << "Enter the minimum marks: ";
            cin >> marks;
            displayStudentsWithMarks(marks);
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
