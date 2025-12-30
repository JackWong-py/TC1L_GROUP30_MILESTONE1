/**********************************************

Program: student_attendance_tracker.cpp
Course: CCP6114_Programming_Fundamentals
Lecture Class: TC1L
Tutorial Class: TT1L
Trimester: 2530
Member_1: 252UC2543V | Wong_Haw_Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436
Member_2: 252UC2528G |   Tan_Yi_Da   | TAN.YI.DA@student.mmu.edu.my     | +60166273669
Member_3: 252UC2543V | Wong_Haw_Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436
Member_4: 252UC250R2 | Zeid Mahmoud  | ZEID.MAHMOUD.SALEH1@student.mmu.edu.my |+601137304844

**********************************************

Task Distribution
Member_1: Insert New Row
Member_2: File Management
Member_3: Show Menu
Member_4: View Sheet

**********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

// Global variable to store the attendance sheet filename
string file;
vector <string> colName;//I can't put more than 1 cin inside this string so I changed it to colName[10]. Jack: Change to vector, for more easy to initialize.
string colType[10];
vector <string> stringData[10];
vector <int> intData[10];
int FileCol=0;

enum CHOICE
{
    INSERT_ROW,
    VIEW_SHEET,
    EXIT
};

CHOICE show_menu();
void insert_new_row(string file_name);
void view_attendance_sheet();
void NewFile();
void initialize_metadata(string file);
bool validate_column_format(const string& col);

// Function to validate column format - must contain (TEXT) or (INT)
bool validate_column_format(const string& col)
{
    // Check if column contains (TEXT) or (INT)
    if (col.find("(TEXT)") != string::npos || col.find("(INT)") != string::npos)
    {
        return true;
    }
    return false;
}

int main()
{


    cout << "========================================" << endl;
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "========================================" << endl;

    //*********************************************************************
    //Sean's part
    //Bug report:
    //1) Number of column can be define more than 10.
    // > Expected outcome: "Please enter number between 2 to 10"
    // > Minimum 2 column to record attendance: Name, Status.
    //
    //2) After column defined successfully, it did not write the first row to the file.
    // > eg input: Name(TEXT),StudentID(INT),Status(INT)
    // > directly write to the first row of the file: Name(TEXT),StudentID(INT),Status(INT)
    // > Column with Name(TEXT),StudentID(INT),Status(INT) created successfully.

    //Enter attendance sheet name
    cout << "Enter attendance sheet name: " << endl;
    cin >> file;
    file=file+".txt";

    ifstream CheckFile(file);
    ofstream inFile; //To open attendance sheet file but if its opened and the system will not open again

    if (CheckFile)
	 {
        cout<<"I've opened your "<<file<<" attendance sheet."<<endl;
	 }
    else //If attendance sheet name not exist, create a new file.
    {
        inFile.open(file);
        if (!inFile)
            cout<<"Failed to create your file"<<endl;
        else
        {
            cout<<"Attendance sheet \""<<file<<"\"created sucessfully."<<endl; //Else, create a new file.
            cout<<"Define number of columns (max 10): ";//If the file is new, define number of column of the CSV file (max 10)
            cin>>FileCol;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //While I asking for the column I faced the problem which it will cout ask user to 2 columns in a row which miss up the first column question so I used this line to solve this problem

            for (int x=0;x<FileCol;x++) // After the file is successfully open/created, ask user column's name one column by one column
            {
               string col;
               bool valid = false;
               while (!valid)
               {
                   cout<<"Enter column "<<x+1<<" name (Name (TEXT/INT)): "<<endl;
                   getline(cin,col);
                   
                   // Validate column format
                   if (validate_column_format(col))
                   {
                       valid = true;
                       colName.push_back(col);
                   }
                   else
                   {
                       cout << "Error: Column must include type specification (TEXT) or (INT)." << endl;
                       cout << "Example: Name (TEXT) or Age (INT)" << endl;
                   }
               }
            }

        }
    }

    initialize_metadata(file);

//      cout << "Columns detected: " << std::endl; //This part of code is for confirm that correct column has been detected.
//      for (const auto& h : colType)
//      {
//        cout << "[" << h << "]" << std::endl;
//      }
//      cout << FileCol << endl;

    CHOICE user_choice;
    while(user_choice != EXIT)
    {
        user_choice = show_menu(); //We get the user choice by showing the menu.

        switch(user_choice)
        {
            case INSERT_ROW:
            insert_new_row(file);
            break;

            case VIEW_SHEET:
            view_attendance_sheet();
            break;
        }
    }
    cout << "Program quited.";
    return 0;
}

//Function to initialize the first row (metadata) of the file
void initialize_metadata(string file)
{
      ifstream input_file(file);
      string header_line;

      colName.clear();
      FileCol = 0;

      if(input_file)
      {
         if(getline(input_file, header_line))
         {
            stringstream ss(header_line);
            string column;

            while(getline(ss, column, ','))
            {
               colName.push_back(column);
               FileCol++;
            }

         }
      }
      else
      {
         cerr << "Unable to open file! " << endl;
      }
      for (int x=0;x<FileCol;x++)
      {
         if (colName[x].find("TEXT") != string::npos)
            colType[x]="string";
         else
            colType[x]="int";
      }
}

// Function to view the attendance sheet in CSV format
//Zeid's part
//Overall everything ok
//
//1) Program display headers multiple times,
// > "StudentID, Name, Status" no need to be display.

void view_attendance_sheet()
{
    // Open the attendance file for reading
    ifstream inFile(file);

    // Display the header
    cout << endl << "------------------------------------------" << endl;
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
//Jack's Part
void insert_new_row(string file_name)
{
   ofstream file(file_name, ios::app); // Open file in append mode

   if (!file.is_open()) //If open file fail it will directly return.
   {
      std::cerr << "Error opening file!" << std::endl;
      return;
   }

   for (int x=0; x<FileCol; x++) //Loop through
   {
      //We check through the column type, if it is string type, the type of data write into file will be string type
      if (colType[x]== "string")
      {
         string value;
         cout << "Enter " << colName[x] << " : ";
         getline(cin >> ws, value);
         file << value;
      }
      else
      {
         int value;
         cout << "Enter " << colName[x] << " : ";
         if(!(cin >> value))
         {
            cout << "Invalid input for (INT). Please enter number only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            x--; //I reduce the column loop by 1 to repeat current loop.
            continue; //Ignore the below code, rerun the loops again.
         }
         file << value;
      }
      if (x < FileCol - 1)
      {
         file << ','; //Add a ',' if not the end of column
      }
      else
      {
         file << '\n'; //If it is a last column, end a new line
      }
   }
   cout << "New row added successfully. " << endl;
   file.close();
}

//Ian's part
//Everything ok, need prompted more friendly if user input less than 1 and more than 3.
CHOICE show_menu()
{
   //*******************************************************************

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
    //  > Quit program

    int input = 0;
    CHOICE choice;
    do {

        cout << "\n=====MENU=====\n";
        cout << "1) Insert New Row\n";
        cout << "2) View Sheet (CSV Mode)\n";
        cout << "3) Exit\n";
        cout << "Enter your choice[IN NUMEBR(1/2/3)]: ";
        cin >> input;
        switch(input)
        {
            case 1:
                choice = INSERT_ROW;
                break;
            case 2:
                choice = VIEW_SHEET;
                break;
            case 3:
                choice = EXIT;
                break;
            default: "Invalid! Enter 1/2/3 only. ";
        }

    } while (input <1 || input > 3);

    return choice;
}
