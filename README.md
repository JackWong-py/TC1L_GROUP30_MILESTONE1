# Student Attendance Tracker

A C++ command-line application for managing student attendance records using CSV-formatted text files.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Compilation](#compilation)
- [Usage Guide](#usage-guide)
- [Menu Options](#menu-options)
- [Example Usage](#example-usage)
- [File Structure](#file-structure)
- [Team Members](#team-members)
- [Known Issues](#known-issues)
- [Troubleshooting](#troubleshooting)

## Overview

The Student Attendance Tracker is a console-based application developed as part of the CCP6114 Programming Fundamentals course (Trimester 2530). It allows users to create and manage attendance sheets with customizable columns, add student records, and view attendance data in CSV format.

## Features

- **Create New Attendance Sheet**: Initialize a new attendance sheet with custom columns
- **Flexible Column Definition**: Support for up to 10 columns with TEXT or INT data types
- **Insert New Records**: Add student attendance records with data validation
- **View Attendance Sheet**: Display all records in CSV format
- **Persistent Storage**: Data is saved in plain text files (.txt) for easy access
- **Data Type Validation**: Ensures INTEGER fields only accept numeric values

## Prerequisites

Before using this software, ensure you have:

- **C++ Compiler**: 
  - GCC (g++) version 4.8 or higher
  - Clang 3.3 or higher
  - MSVC (Visual Studio) 2013 or higher
- **Operating System**: Windows, Linux, or macOS
- **Minimum C++ Standard**: C++11 or higher

## Installation

1. **Clone or Download the Repository**:
   ```bash
   git clone https://github.com/JackWong-py/TC1L_GROUP30_MILESTONE1.git
   cd TC1L_GROUP30_MILESTONE1
   ```

2. **Verify Files**:
   Ensure `main.cpp` is present in the directory.

## Compilation

### On Linux/macOS:
```bash
g++ -std=c++11 main.cpp -o attendance_tracker
```

### On Windows (using MinGW):
```bash
g++ -std=c++11 main.cpp -o attendance_tracker.exe
```

### On Windows (using Visual Studio):
1. Open Developer Command Prompt
2. Run:
   ```bash
   cl /EHsc main.cpp /Fe:attendance_tracker.exe
   ```

## Usage Guide

### Starting the Program

**On Linux/macOS**:
```bash
./attendance_tracker
```

**On Windows**:
```bash
attendance_tracker.exe
```

### First-Time Setup

1. **Enter Attendance Sheet Name**:
   - When prompted, enter a name for your attendance sheet (e.g., `ClassA`, `CS101`)
   - The program will automatically append `.txt` extension
   - Example: Enter `ClassA` → creates `ClassA.txt`

2. **Creating a New Sheet**:
   If the file doesn't exist, you'll be prompted to:
   
   a. **Define Number of Columns** (2-10):
      - Enter a number between 2 and 10
      - Example: `3` for three columns
   
   b. **Define Each Column**:
      - Each column must include a name and type specification
      - Format: `ColumnName (TYPE)`
      - Types: `(TEXT)` for strings or `(INT)` for integers
      - Examples:
        - `Name (TEXT)`
        - `StudentID (INT)`
        - `Status (INT)`
        - `Email (TEXT)`

3. **Opening an Existing Sheet**:
   - If the file already exists, the program will load it automatically
   - You'll proceed directly to the main menu

### Main Menu Navigation

After setup, you'll see the main menu with three options:

```
=====MENU=====
1) Insert New Row
2) View Sheet (CSV Mode)
3) Exit
Enter your choice[IN NUMBER(1/2/3)]:
```

## Menu Options

### 1. Insert New Row

Adds a new student record to the attendance sheet.

**Steps**:
1. Select option `1` from the main menu
2. Enter data for each column in sequence
3. For TEXT columns: Enter any text (names, emails, etc.)
4. For INT columns: Enter numbers only (Student ID, status, age, etc.)
5. The system validates input types and prompts for re-entry if invalid

**Example**:
```
Enter Name (TEXT) : John Tan
Enter StudentID (INT) : 1001
Enter Status (INT) : 1
New row added successfully.
```

**Status Convention**:
- `1` = Present
- `0` = Absent

### 2. View Sheet (CSV Mode)

Displays all records in the attendance sheet.

**Steps**:
1. Select option `2` from the main menu
2. The program displays all records in comma-separated format
3. If no records exist, it shows "(No records found)"

**Example Output**:
```
------------------------------------------
    View Attendance Sheet (CSV Mode)
------------------------------------------
StudentID, Name, Status
Name (TEXT),StudentID (INT),Status (INT)
John Tan,1001,1
Ian Chen,1002,0
```

### 3. Exit

Exits the program and returns to the command line.

**Steps**:
1. Select option `3` from the main menu
2. Program displays "Program quited." and terminates

## Example Usage

### Complete Workflow Example

```
========================================
STUDENT ATTENDANCE TRACKER - MILESTONE 1
========================================
Enter attendance sheet name: 
ClassA
Attendance sheet "ClassA.txt" created successfully.
Define number of columns (max 10): 3
Enter column 1 name (Name (TEXT/INT)): 
Name (TEXT)
Enter column 2 name (Name (TEXT/INT)): 
StudentID (INT)
Enter column 3 name (Name (TEXT/INT)): 
Status (INT)

=====MENU=====
1) Insert New Row
2) View Sheet (CSV Mode)
3) Exit
Enter your choice[IN NUMBER(1/2/3)]: 1

Enter Name (TEXT) : John Tan
Enter StudentID (INT) : 1001
Enter Status (INT) : 1
New row added successfully.

=====MENU=====
1) Insert New Row
2) View Sheet (CSV Mode)
3) Exit
Enter your choice[IN NUMBER(1/2/3)]: 1

Enter Name (TEXT) : Mary Lee
Enter StudentID (INT) : 1002
Enter Status (INT) : 0
New row added successfully.

=====MENU=====
1) Insert New Row
2) View Sheet (CSV Mode)
3) Exit
Enter your choice[IN NUMBER(1/2/3)]: 2

------------------------------------------
    View Attendance Sheet (CSV Mode)
------------------------------------------
StudentID, Name, Status
Name (TEXT),StudentID (INT),Status (INT)
John Tan,1001,1
Mary Lee,1002,0

=====MENU=====
1) Insert New Row
2) View Sheet (CSV Mode)
3) Exit
Enter your choice[IN NUMBER(1/2/3)]: 3
Program quited.
```

## File Structure

```
TC1L_GROUP30_MILESTONE1/
│
├── main.cpp              # Main C++ source code
├── README.md             # This documentation file
├── .gitignore            # Git ignore rules
└── *.txt                 # Attendance sheet files (created at runtime)
```

## Team Members

**Course**: CCP6114 Programming Fundamentals  
**Class**: TC1L / TT1L  
**Trimester**: 2530

| Member | ID | Name | Email | Phone | Task |
|--------|-------|------|-------|-------|------|
| Member 1 | 252UC2543V | Wong Haw Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436 | Insert New Row |
| Member 2 | 252UC2528G | Tan Yi Da | TAN.YI.DA@student.mmu.edu.my | +60166273669 | File Management |
| Member 3 | 252UC2543V | Wong Haw Jack | WONG.HAW.JACK@student.mmu.edu.my | +60123626436 | Show Menu |
| Member 4 | 252UC250R2 | Zeid Mahmoud | ZEID.MAHMOUD.SALEH1@student.mmu.edu.my | +601137304844 | View Sheet |

## Known Issues

1. **Column Definition Limit**: Maximum 10 columns can be defined per attendance sheet
2. **Minimum Columns**: At least 2 columns are required (e.g., Name and Status)
3. **Column Format Validation**: Column names must include type specification `(TEXT)` or `(INT)`
4. **Fixed Header Display**: The view sheet function displays a fixed header "StudentID, Name, Status" regardless of actual columns
5. **No Edit/Delete Functions**: Currently, records cannot be edited or deleted after insertion

## Troubleshooting

### Problem: Compilation Errors

**Solution**: Ensure you have a C++11 compatible compiler and use the `-std=c++11` flag:
```bash
g++ -std=c++11 main.cpp -o attendance_tracker
```

### Problem: "Invalid input for (INT)" Error

**Solution**: When entering data for INT columns, use numbers only (no letters or special characters).

### Problem: "Column must end with type specification" Error

**Solution**: When defining columns, always include either `(TEXT)` or `(INT)` at the end.
- Correct: `Name (TEXT)`, `Age (INT)`
- Incorrect: `Name`, `Age`

### Problem: Cannot Open Existing File

**Solution**: 
1. Ensure the .txt file is in the same directory as the program
2. Check file permissions (read/write access)
3. Verify the filename is correct (case-sensitive on Linux/macOS)

### Problem: File Not Saving Data

**Solution**: 
1. Check you have write permissions in the current directory
2. Ensure sufficient disk space is available
3. Don't interrupt the program while writing data

### Problem: Invalid Choice in Menu

**Solution**: Enter only numbers 1, 2, or 3 when prompted for menu selection.

---

## Additional Notes

- All attendance data is stored in plain text format (.txt files)
- Files use comma-separated values (CSV) for easy import into spreadsheet applications
- The first row of each file contains column definitions
- Data is automatically saved when you insert a new row
- You can have multiple attendance sheets by using different filenames

## Support

For issues or questions, contact any team member listed above.

---

*Last Updated: December 2024*  
*Version: Milestone 1*
