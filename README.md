# Database of Students

## Description
This program is a database management system for students. It allows users to manage student records, including adding new students, viewing students by various categories (such as honor roll, academic probation, and year), and deleting student records. The data can be loaded from a CSV file or managed through user input.

## Features
- Add new students to the database.
- View student records based on various criteria:
  - First 10 students in the database
  - Honor roll students (GPA >= 3.5)
  - Students on academic probation (GPA < 2.0)
  - Freshman, sophomore, junior, and senior students
  - Individual student information by ID
- Delete student records by ID.
- Load student data from a CSV file.

## Requirements
- C Compiler (e.g., GCC)
- Compatible with Windows OS
- Clion or any other C IDE

## Usage Instructions
1. Compile the program using a C compiler.
2. Run the executable.
3. Follow the on-screen instructions:
   - Choose 'E' to start with an empty database or 'F' to load a database from a file.
   - Add, view, or delete student records as needed.
   - Use 'X' to exit the program.

## Sample Input File Format
If loading from a file, ensure the CSV format follows this structure:
`StudentName, StudentID, GPA, CreditHours`
