# Student Attendance Tracker - Milestone 1 & 2

## Overview
This is a C++ based **Student Attendance Tracker** designed for academic record management. The software allows users to organize attendance data by academic terms and weeks, providing a structured way to insert, view, update, and delete student records using a file-based storage system.

---

## Project Information
* **Course:** CCP6114_Programming_Fundamentals
* **Trimester:** 2530
* **Class:** TC1L (Lecture) / TT1L (Tutorial)
* **Developers:**
    * Wong Haw Jack (252UC2543V)
    * Tan Yi Da (252UC2528G)
    * Chen Chee Chuen (252UC2546J)
    * Zeid Mahmoud (252UC250R2)

---

## Features
The program provides a menu-driven interface with the following functionalities:

1. **Term & Week Management:** Organizes files within a `data/` directory. Users can select existing terms or create new ones.
2. **Dynamic Sheet Creation:** When creating a new week, the user defines the number of columns (2-10). The system automatically handles `StudentID (INT)` and `Status (INT)` columns.
3. **Insert Row:** Add new student records. The system validates input types based on metadata (TEXT or INT).
4. **View Sheet:** Displays the full content of the current attendance text file.
5. **Count Records:** Displays the total number of students, excluding the header row.
6. **Update Status:** Search for a student by ID and modify their attendance status.
7. **Delete Row:** Remove a specific student record from the file using their ID.

---

## File Structure
The software creates a hierarchical data structure:
```text
project_root/
│
├── student_attendance_tracker.cpp   # Source code
├── data/                            # Root data folder
│   └── [Term_Name]/                 # Directory for a specific term
│       └── [Week_Name].txt          # Attendance sheet (CSV format)
