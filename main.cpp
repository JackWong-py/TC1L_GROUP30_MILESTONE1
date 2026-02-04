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
#include <cctype>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

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
    COUNT_ROW,
    EXIT
};

CHOICE show_menu();
void insert_new_row(string file_name);
void view_attendance_sheet();
void NewFile();
void initialize_metadata(string file);
bool validate_column_format(const string& col);
// New helper functions for term and file handling
void create_term(const string& term_name);
bool open_file_in_term(const string& term_name, const string& csv_name);

// Function to validate column format - must end with (TEXT) or (INT)
bool validate_column_format(const string& col)
{
    // Check if column ends with (TEXT) or (INT)
    size_t len = col.length();
    return (len >= 6 && col.substr(len - 6) == "(TEXT)") ||
           (len >= 5 && col.substr(len - 5) == "(INT)");
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

    // Auto-create requested term and open requested file (fallback to prompt if missing)
    create_term("Trimester2530");
    if (!open_file_in_term("Trimester2530", "week1_attendance"))
    {
        // If the file wasn't found in the term folder, fall back to original prompt
        cout << "Enter attendance sheet name: " << endl;
        cin >> file;
        file = file + ".txt";
    }

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

                   // Trim trailing/leading spaces
                   size_t start = col.find_first_not_of(" \t\r\n");
                   size_t end = col.find_last_not_of(" \t\r\n");
                   if (start == string::npos)
                       col = "";
                   else
                       col = col.substr(start, end - start + 1);

                   // Validate column format (strict)
                   if (validate_column_format(col))
                   {
                       valid = true;
                       colName.push_back(col);
                   }
                   else
                   {
                       // If user entered a plain name (letters/spaces), assume TEXT
                       bool letters_only = true;
                       bool digits_only = true;
                       for (char c : col)
                       {
                           if (!isalpha(c) && !isspace(c)) letters_only = false;
                           if (!isdigit(c)) digits_only = false;
                       }

                       if (!col.empty() && letters_only)
                       {
                           string assumed = col + " (TEXT)";
                           cout << "Assuming TEXT type, using: " << assumed << endl;
                           valid = true;
                           colName.push_back(assumed);
                       }
                       else if (!col.empty() && digits_only)
                       {
                           string assumed = col + " (INT)";
                           cout << "Assuming INT type, using: " << assumed << endl;
                           valid = true;
                           colName.push_back(assumed);
                       }
                       else
                       {
                           cout << "Error: Column must end with type specification (TEXT) or (INT)." << endl;
                           cout << "Example: Name (TEXT) or Age (INT)" << endl;
                       }
                   }
               }
            }
            for (int x = 0; x < FileCol; x++)
            {
            if (x == FileCol - 1)
                {inFile << colName[x] << '\n';}
            else
                {inFile << colName[x] << ',';
            }
            }

            inFile.close();

            // Also create a .csv version with same header
            string csvFile = file;
            if (csvFile.size() > 4 && csvFile.substr(csvFile.size()-4) == ".txt")
                csvFile = csvFile.substr(0, csvFile.size()-4) + ".csv";
            ofstream outCsv(csvFile);
            if (outCsv)
            {
                for (int x = 0; x < FileCol; x++)
                {
                    if (x == FileCol - 1)
                        outCsv << colName[x] << '\n';
                    else
                        outCsv << colName[x] << ',';
                }
                outCsv.close();
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
         size_t len = colName[x].length();
         if (len >= 6 && colName[x].substr(len - 6) == "(TEXT)")
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

// Create a term folder under data/TERM_NAME (e.g. data/Trimester2530)
void create_term(const string& term_name)
{
    string base = "data";
    struct stat st = {0};
    if (stat(base.c_str(), &st) == -1)
    {
        mkdir(base.c_str(), 0755);
    }
    string path = base + "/" + term_name;
    if (stat(path.c_str(), &st) == -1)
    {
        if (mkdir(path.c_str(), 0755) == 0)
            cout << "Create term -> " << term_name << " created" << endl;
        else
            cerr << "Failed to create term folder: " << path << endl;
    }
    else
    {
        cout << "Term already exists: " << term_name << endl;
    }
}

// Open a CSV (txt) file located under data/TERM_NAME/CSV_NAME.txt
// Sets the global `file` variable to the found path on success.
bool open_file_in_term(const string& term_name, const string& csv_name)
{
    string path = "data/" + term_name + "/" + csv_name + ".txt";
    ifstream f(path);
    if (!f.is_open())
    {
        cerr << "Error: file not found: " << path << endl;
        return false;
    }
    f.close();
    file = path;
    cout << "Open file -> " << csv_name << "" << endl;
    return true;
}

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
string get_text()
      {
          string input;

          while(true)
          {
              bool valid = true;
              getline(cin >> ws, input);

              for (char c : input)
              {
                if (!isalpha(c) && !isspace(c))
                {
                    valid = false;
                    break;
                }
              }

              if (valid && !input.empty())
              {
                  return input; //only alphbet + space
              }
              else
              {
                  cout << "Invalid input! Only alphabets and space allowed. Try again.\n";
              }
          }
      }

void insert_new_row(string file_name)
{
    // Build the row string first, then append to both .txt and .csv
    string row;
    for (int x = 0; x < FileCol; x++)
    {
        if (colType[x] == "string")
        {
             string value;
             cout << "Enter " << colName[x] << " : ";
             value = get_text();
             row += value;
        }
        else
        {
            int value;
            cout << "Enter " << colName[x] << " : ";
            if (!(cin >> value))
            {
                cout << "Invalid input for (INT). Please enter number only." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                x--; // repeat this column
                continue;
            }
            row += to_string(value);
        }

        if (x < FileCol - 1)
            row += ',';
    }

    row += '\n';

    // Append to .txt
    ofstream outTxt(file_name, ios::app);
    if (!outTxt)
    {
         cerr << "Error opening file for append: " << file_name << endl;
         return;
    }
    outTxt << row;
    outTxt.close();

    // Append to .csv counterpart
    string csvName = file_name;
    if (csvName.size() > 4 && csvName.substr(csvName.size()-4) == ".txt")
         csvName = csvName.substr(0, csvName.size()-4) + ".csv";
    else
         csvName = csvName + ".csv";

    ofstream outCsv(csvName, ios::app);
    if (outCsv)
    {
         outCsv << row;
         outCsv.close();
    }

    cout << "New row added successfully. " << endl;
}

//count row
int count_rows_except_header(const string& filename)
{
    // Make sure the file exists and is in the correct folder. Otherwise, the function will return 0.
    ifstream inFile(filename);
    if (!inFile.is_open())
        return 0;

    string line;
    int count = 0;
    bool isFirstLine = true; //skip the header row

    while (getline(inFile, line))
    {
        if (line.empty()) continue;

        if (isFirstLine)
        {
            isFirstLine = false; //skip header
            continue;
        }

        count++;
    }

    inFile.close();
    return count;
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
        cout << "3) Count Records\n";  //(Exclude Header)
        cout << "4) Exit\n";
        cout << "Enter your choice[IN NUMBER(1/2/3/4)]: ";

        cin >> input;

        //Handling non-numeric inputs
        if (!cin)  //Detect invalid input
        {
            cout << "Invalid input! Please enter a number(1/2/3/4) only.\n";
            cin.clear();  //Reset input stream
            cin.ignore(numeric_limits<streamsize>::max(),'\n');  //Remove garbage input
            continue;  //Retry the menu
        }

        switch(input)
        {
            case 1:
                choice = INSERT_ROW;
                break;
            case 2:
                choice = VIEW_SHEET;
                break;
            case 3:
            {
                choice = COUNT_ROW;
                int total = count_rows_except_header(file);
                cout << "\nTotal Records: " << total << endl;
                break;
            }
            case 4:
                choice = EXIT;
                break;
            default:
                cout << "\nInvalid! Enter 1/2/3/4 only.";
        }

    } while (input <1 || input > 4);

    return choice;
}
