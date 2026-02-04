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
#include <dirent.h>
#include <algorithm>

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
void list_weeks_in_term(const string& term_name, vector<string>& weeks);
string choose_or_create_week(const string& term_name);
bool create_new_sheet(const string& path);
void list_terms(vector<string>& terms);
string choose_or_create_term();
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

    // Let user choose or create a term, then choose/create a week inside it
    string term = choose_or_create_term();
    create_term(term);
    file = choose_or_create_week(term);

    // Ensure the chosen file exists; if not, create and initialize it
    ifstream CheckFile(file);
    if (CheckFile)
    {
        cout << "I've opened your " << file << " attendance sheet." << endl;
    }
    else
    {
        // Try to create and initialize the new sheet (will prompt for columns)
        if (create_new_sheet(file))
        {
            cout << "Attendance sheet '" << file << "' created successfully." << endl;
        }
        else
        {
            cerr << "Failed to create your file" << endl;
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

// List .txt files under data/<term_name>
void list_weeks_in_term(const string& term_name, vector<string>& weeks)
{
    weeks.clear();
    string dirPath = "data/" + term_name;
    DIR* dir = opendir(dirPath.c_str());
    if (!dir) return;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        string name = entry->d_name;
        if (name.size() > 4 && name.substr(name.size()-4) == ".txt")
        {
            weeks.push_back(name);
        }
    }
    closedir(dir);
    sort(weeks.begin(), weeks.end());
}

// List subdirectories under data/
void list_terms(vector<string>& terms)
{
    terms.clear();
    string base = "data";
    DIR* dir = opendir(base.c_str());
    if (!dir) return;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        string name = entry->d_name;
        if (name == "." || name == "..") continue;
        string full = base + "/" + name;
        struct stat st;
        if (stat(full.c_str(), &st) == 0 && S_ISDIR(st.st_mode))
        {
            terms.push_back(name);
        }
    }
    closedir(dir);
    sort(terms.begin(), terms.end());
}

// Prompt user to choose existing term or create new one
string choose_or_create_term()
{
    vector<string> terms;
    list_terms(terms);

    cout << "Available terms:\n";
    if (terms.empty()) cout << "  (none)\n";
    else
    {
        for (size_t i = 0; i < terms.size(); ++i)
            cout << "  " << (i+1) << ") " << terms[i] << "\n";
    }

    cout << "\nOptions:\n";
    cout << "  1) Select existing term\n";
    cout << "  2) Create new term (default: Trimester2530)\n";
    cout << "Choose option (1/2): ";
    int opt = 0;
    while (!(cin >> opt) || (opt != 1 && opt != 2))
    {
        cout << "Invalid. Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opt == 1)
    {
        if (terms.empty())
        {
            cout << "No existing terms. Switching to create new term.\n";
            opt = 2;
        }
        else
        {
            cout << "Enter term number to open: ";
            int sel = 0;
            while (!(cin >> sel) || sel < 1 || sel > (int)terms.size())
            {
                cout << "Invalid selection. Enter number between 1 and " << terms.size() << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return terms[sel-1];
        }
    }

    // Create new term
    cout << "Enter new term name (default 'Trimester2530'): ";
    string name;
    getline(cin, name);
    if (name.empty()) name = "Trimester2530";
    return name;
}

// Prompt user to choose existing week or create new one
string choose_or_create_week(const string& term_name)
{
    vector<string> weeks;
    list_weeks_in_term(term_name, weeks);

    cout << "Available weeks in " << term_name << ":\n";
    if (weeks.empty())
    {
        cout << "  (none)\n";
    }
    else
    {
        for (size_t i = 0; i < weeks.size(); ++i)
            cout << "  " << (i+1) << ") " << weeks[i] << "\n";
    }

    cout << "\nOptions:\n";
    cout << "  1) Select existing week\n";
    cout << "  2) Create new week (default: week1_attendance)\n";
    cout << "Choose option (1/2): ";
    int opt = 0;
    while (!(cin >> opt) || (opt != 1 && opt != 2))
    {
        cout << "Invalid. Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opt == 1)
    {
        if (weeks.empty())
        {
            cout << "No existing weeks. Switching to create new week.\n";
            opt = 2;
        }
        else
        {
            cout << "Enter week number to open: ";
            int sel = 0;
            while (!(cin >> sel) || sel < 1 || sel > (int)weeks.size())
            {
                cout << "Invalid selection. Enter number between 1 and " << weeks.size() << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string chosen = weeks[sel-1];
            return string("data/") + term_name + "/" + chosen;
        }
    }

    // Create new week
    cout << "Enter new week name (no extension, default 'week1_attendance'): ";
    string name;
    getline(cin, name);
    if (name.empty()) name = "week1_attendance";
    // sanitize: remove .txt if present
    if (name.size() > 4 && name.substr(name.size()-4) == ".txt")
        name = name.substr(0, name.size()-4);

    string fullpath = string("data/") + term_name + "/" + name + ".txt";
    return fullpath;
}

// Create a new sheet at the given path and prompt for columns
bool create_new_sheet(const string& path)
{
    // ensure directory exists
    // prompt for columns and write header
    cout << "Creating new attendance sheet: " << path << "\n";
    colName.clear();
    cout << "Define number of columns (min 2, max 10): ";
    int cols = 0;
    while (!(cin >> cols) || cols < 2 || cols > 10)
    {
        cout << "Please enter a number between 2 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    FileCol = cols;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int x = 0; x < FileCol; ++x)
    {
        string col;
        bool valid = false;
        while (!valid)
        {
            cout << "Enter column " << (x+1) << " name (e.g. Name (TEXT) or Age (INT)): ";
            getline(cin, col);
            // trim
            size_t start = col.find_first_not_of(" \t\r\n");
            size_t end = col.find_last_not_of(" \t\r\n");
            if (start == string::npos) col = "";
            else col = col.substr(start, end - start + 1);

            if (validate_column_format(col))
            {
                valid = true;
                colName.push_back(col);
            }
            else
            {
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
                    cout << "Assuming TEXT type, using: " << assumed << "\n";
                    valid = true;
                    colName.push_back(assumed);
                }
                else if (!col.empty() && digits_only)
                {
                    string assumed = col + " (INT)";
                    cout << "Assuming INT type, using: " << assumed << "\n";
                    valid = true;
                    colName.push_back(assumed);
                }
                else
                {
                    cout << "Error: Column must end with type specification (TEXT) or (INT).\n";
                }
            }
        }
    }

    ofstream out(path);
    if (!out) return false;
    for (int x = 0; x < FileCol; ++x)
    {
        out << colName[x];
        if (x < FileCol-1) out << ',';
    }
    out << '\n';
    out.close();

    // also create .csv
    string csvPath = path;
    if (csvPath.size() > 4 && csvPath.substr(csvPath.size()-4) == ".txt")
        csvPath = csvPath.substr(0, csvPath.size()-4) + ".csv";
    ofstream outCsv(csvPath);
    if (outCsv)
    {
        for (int x = 0; x < FileCol; ++x)
        {
            outCsv << colName[x];
            if (x < FileCol-1) outCsv << ',';
        }
        outCsv << '\n';
        outCsv.close();
    }

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
