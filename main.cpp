/**********************************************

Program: student_attendance_tracker.cpp
Course: CCP6114_Programming_Fundamentals
Lecture Class: TC1L
Tutorial Class: TT1L
Trimester: 2530
Member_1: 252UC2543V | Wong_Haw_Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436
Member_2: 252UC2543V | Wong_Haw_Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436
Member_3: 252UC2543V | Wong_Haw_Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436
Member_4: 252UC2543V | Wong_Haw_Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436

**********************************************

Task Distribution
Member_1:
Member_2:
Member_3:
Member_4:

**********************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Global variable to store the attendance sheet filename
string file;

enum CHOICE
{
    INSERT_ROW,
    VIEW_SHEET,
    EXIT
};

CHOICE show_menu();
void insert_new_row();
void view_attendance_sheet();

int main()
{
    cout << "========================================" << endl;
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "========================================" << endl;

    //Enter attendance sheet name
    cout << "Enter attendance sheet name: " << endl;
    cin >> file;

    //If attendance sheet name not exist, create a new file.
    //Else, create a new file.

    //If the file is new, define number of column of the CSV file (max 10)

    //After the file is successfully open/created,
    //Menu is prompted as below:
    //
    //1) Insert New Row
    //  > Enter Student ID: (Must contain number only)
    //  > Enter Name: (Must contain alphabet and space only)
    //  > Enter Status (Present(1), Absent(0)): (Input 1 or 0 only)
    //
    //2) View Sheet (CSV Mode)
    //   ------------------------------------------
    //       View Attendance Sheet (CSV Mode)
    //   ------------------------------------------
    //     StudentID, Name, Status
    //     1001, John Tan, 1
    //     1002, Ian Chen, 0

    //3) Exit
    //  > Close file

    CHOICE user_choice;

    while(user_choice != EXIT)
    {
        user_choice = show_menu(); //We get the user choice by showing the menu.

        switch(user_choice)
        {
            case INSERT_ROW:
            insert_new_row();
            break;

            case VIEW_SHEET:
            view_attendance_sheet();
            break;

            default:
            cout << "Please enter the menu only! " << endl;
            break;

        }
    }

    return 0;
}

// Function to view the attendance sheet in CSV format
void view_attendance_sheet()
{
    // Open the attendance file for reading
    ifstream inFile(file);

    // Display the header
    cout << "------------------------------------------" << endl;
    cout << "    View Attendance Sheet (CSV Mode)" << endl;
    cout << "------------------------------------------" << endl;

    // Check if file opened successfully
    if (!inFile.is_open())
    {
        cout << "Error: Could not open file '" << file << "'" << endl;
        return;
    }

    // Display column headers
    cout << "StudentID, Name, Status" << endl;

    // Read and display each line from the file
    string line;
    bool hasData = false;

    while (getline(inFile, line))
    {
        // Skip empty lines
        if (line.empty())
        {
            continue;
        }
        cout << line << endl;
        hasData = true;
    }

    // If no data was found, display a message
    if (!hasData)
    {
        cout << "(No records found)" << endl;
    }

    // Close the file
    inFile.close();
}
