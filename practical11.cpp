#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class student {
public:
    int rollno;
    char name[50];
    char add[50];
    char div[5];

    void setData() {
        cout << "Enter Roll no: ";
        cin >> rollno;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Address of student: ";
        cin >> add;
        cout << "Division of student: ";
        cin >> div;
    }

    void showData() {
        cout << "\nRoll no. of student: " << rollno;
        cout << "\nName of the student: " << name;
        cout << "\nAddress of student: " << add;
        cout << "\nDivision of student: " << div << endl;
    }

    int retrollno() {
        return rollno;
    }
};

void write_record() {
    ofstream outfile("StudentDatabase", ios::binary | ios::app);
    student obj;
    obj.setData();
    outfile.write(reinterpret_cast<char*>(&obj), sizeof(obj));
    outfile.close();
}

void display_record() {
    ifstream infile("StudentDatabase", ios::binary);
    student obj;
    while (infile.read(reinterpret_cast<char*>(&obj), sizeof(obj))) {
        obj.showData();
    }
    infile.close();
}

void search_record(int n) {
    bool flag = false;
    ifstream infile("StudentDatabase", ios::binary);
    student obj;
    while (infile.read(reinterpret_cast<char*>(&obj), sizeof(obj))) {
        if (obj.retrollno() == n) {
            flag = true;
            obj.showData();
            break;
        }
    }
    infile.close();
    if (!flag) {
        cout << "Record for roll no. " << n << " is not found in the file." << endl;
    }
}

void delete_record(int n) {
    student obj;
    ifstream infile("StudentDatabase", ios::binary);
    ofstream outfile("StudentNewData", ios::binary);
    while (infile.read(reinterpret_cast<char*>(&obj), sizeof(obj))) {
        if (obj.retrollno() != n) {
            outfile.write(reinterpret_cast<char*>(&obj), sizeof(obj));
        }
    }
    infile.close();
    outfile.close();
    remove("StudentDatabase");
    rename("StudentNewData", "StudentDatabase");
}

int main() {
    int ch;
    while (true) {
        cout << "\n****** File Operations ******"
             << "\n1. Add Record"
             << "\n2. Display Records"
             << "\n3. Search a Particular Record"
             << "\n4. Delete a Particular Record"
             << "\n5. Exit"
             << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                int n;
                cout << "Enter total number of records you want to store in the file: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    write_record();
                }
                break;
            }
            case 2:
                cout << "\nList of records:";
                display_record();
                break;
            case 3: {
                int s;
                cout << "Enter student roll no. to search: ";
                cin >> s;
                search_record(s);
                break;
            }
            case 4: {
                int t;
                cout << "Enter student roll no. to delete: ";
                cin >> t;
                delete_record(t);
                cout << "Record Deleted Successfully!!" << endl;
                break;
            }
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
