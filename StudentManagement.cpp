#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


// -------------- Prototype --------------------
void addStudentDataToFile();
void createStudentDataFile();
void readStudentData();
void updateStudentData();
void deleteStudentData();
// ---------------------------------------------


int main() {
    int choice;
    do {
        cout << "=================================\n";
        cout << "1. Create Student Data File" << endl;
        cout << "2. Search Student Data by ID" << endl;
        cout << "3. Update Student Data by ID" << endl;
        cout << "4. Delete Student Data by ID" << endl;
        cout << "5. Add Student Data" << endl;
        cout << "6. Exit" << endl;
        cout << "=================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                createStudentDataFile();
                break;
            case 2:
                readStudentData();
                break;
            case 3:
                updateStudentData();
                break;
            case 4:
                deleteStudentData();
                break;
            case 5:
                addStudentDataToFile();
                break;
            case 0:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 0, 1, 2, 3, 4,5" << endl;
        }
    } while (choice != 0);
    return 0;
}


void addStudentDataToFile(){
    fstream addData;
    addData.open("student_data.csv", ios::app);
    int n_student;
    cout << "Input number of student: ";
    cin >> n_student;

    int ID;
    string name, gender, email, phone_number;

    cout << "Input ID name gender email phone_number: ";

    for(int i=0; i<n_student; i++){
        cin >> ID 
            >> name 
            >> gender 
            >> email 
            >> phone_number;

        addData   << ID << ','
                    << name << ','
                    << gender << ','
                    << email << ','
                    << phone_number
                    << endl;

    }
    addData.close();
}


void createStudentDataFile(){
    ofstream WriteData("student_data.csv");
    int n_student;
    cout << "Input number of student: ";
    cin >> n_student;

    int ID;
    string name, gender, email, phone_number;

    cout << "Input ID name gender email phone_number: ";

    for(int i=0; i<n_student; i++){
        cin >> ID 
            >> name 
            >> gender 
            >> email 
            >> phone_number;

        WriteData   << ID << ','
                    << name << ','
                    << gender << ','
                    << email << ','
                    << phone_number
                    << endl;

    }
    WriteData.close();
}


void readStudentData() {
    ifstream studentFile;
    studentFile.open("student_data.csv");

    int rollnum, roll2, count = 0;
    cout << "Enter the ID number of the student to display details: ";
    cin >> rollnum;

    vector<string> row;
    string line, word;

    while (getline(studentFile, line)) {
        row.clear();

        stringstream s(line);
        
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        
        // -----------------In case of compiler higher than C-11 --------------
        roll2 = stoi(row[0]);
        // -----------------In case of compiler lower than C-11 ---------------
        // stringstream convert;
        // convert << row[0];
        // convert >> roll1;

        if (roll2 == rollnum) {
            count = 1;
            cout << "Student Details:" << endl;
            cout << "ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Email: " << row[3] << endl;
            cout << "Phone: " << row[4] << endl;
            break;
        }
    }

    if (count == 0)
        cout << "Record not found\n";

    studentFile.close();
}


void updateStudentData() {
    fstream fin;
    fin.open("student_data.csv");

    ofstream fout ("student_data_new.csv"); 

    int rollnum, roll1, count = 0, i;
    char data;
    string new_data;
    int index;
    string line, word;
    vector<string> row;

    cout << "Enter the ID of the record to be updated: ";
    cin >> rollnum;

    cout << "Enter the data to be updated(N/G/E/P): ";
    cin >> data;

    if (data == 'n' || data == 'N')
        index = 1;
    else if (data == 'g' || data == 'G')
        index = 2;
    else if (data == 'e' || data == 'E')
        index = 3;
    else if (data == 'p' || data == 'P')
        index = 4;
    else {
        cout << "Wrong choice.\n";
        return;
    }

    cout << "Enter new data information: ";
    cin >> new_data;

    while (getline(fin, line)) { 

        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) { 
            row.push_back(word);
        }

        // -----------------In case of compiler higher than C-11 --------------
        roll1 = stoi(row[0]);
        // -----------------In case of compiler lower than C-11 ---------------
        // stringstream convert;
        // convert << row[0];
        // convert >> roll1;

        int row_size = row.size();

        if (roll1 == rollnum) {
            count = 1;
            row[index] = new_data;
        }

        for (i = 0; i < row_size - 1; i++) {
            fout << row[i] << ",";
        }

        fout << row[row_size - 1] << "\n";
    }

    if (count == 0)
        cout << "Record not found\n";

    fin.close();
    fout.close();

    remove("student_data.csv");
    rename("student_data_new.csv", "student_data.csv");
}


void deleteStudentData() 
{ 
    fstream fin;
    fin.open("student_data.csv");

    ofstream fout("student_data_new.csv");

    int rollnum, roll1, count = 0;
    string line;
    vector<string> row;

    cout << "Enter the ID of the student to be deleted: ";
    cin >> rollnum;

    while (getline(fin, line)) { 
        row.clear();
        stringstream s(line);

        string word;
        while (getline(s, word, ',')) { 
            row.push_back(word);
        } 

        // -----------------In case of compiler higher than C-11 --------------
        roll1 = stoi(row[0]);
        // -----------------In case of compiler lower than C-11 ---------------
        // stringstream convert;
        // convert << row[0];
        // convert >> roll1;

        if (roll1 != rollnum) { 
            for (size_t i = 0; i < row.size() - 1; i++) { 
                fout << row[i] << ", ";
            } 
            fout << row.back() << "\n";
        } 
        else { 
            count = 1;
        } 
    } 

    if (count == 1) {
        cout << "Record deleted\n";
    } 
    else {
        cout << "Record not found\n";
    }

    fin.close();
    fout.close();

    remove("student_data.csv");
    rename("student_data_new.csv", "student_data.csv");
} 
