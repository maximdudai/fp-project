# TeSP PSI Management Application

This project, developed for the "Fundamentals of Programming" course, is a prototype application for managing the academic situation of students in the TeSP program in Information Systems Programming (PSI) at the School of Technology and Management (ESTG).

## Overview

### Data Entities:

#### 1. Student:
Each student is identified by a unique identifier, student number, name, course code, and email.

Example: `[75; 2239999; Maria Valente; 4515; 2239999@my.ipleiria.pt]`

#### 2. Course Unit (Unidade Curricular):
Each course unit is identified by a unique identifier, course unit code, name, academic year, semester, and ECTS credits.

Example: `[4; 4515104; Fundamentals of Programming; 1st year; 1st semester; 7]`

#### 3. Evaluation:
Each evaluation is identified by a unique identifier, student identifier, course unit identifier, academic year, evaluation period (Final Semester Evaluation, Retake, Special), evaluation date, and final grade.

Example: `[81; 75; 4; 2023-24; Final Semester Evaluation; 15/01/2024; 16]`

### Application Requirements:

- The application should store data for up to 150 students, 18 course units, and 5000 evaluations.
- Implemented in the C programming language.

## Functionality

The application provides the following functionalities:

- **Student Data Management:**
  - Register and consult student information.

- **Course Unit Management:**
  - Register and consult data related to course units.

- **Evaluation Data Management:**
  - Register and consult data related to evaluations.

- **Statistics:**
  - Total approved ECTS for a student.
  - Current arithmetic mean of grades in approved course units for a student.
  - Percentage of approved ECTS in each academic semester for a student.

- **Data Persistence:**
  - Save and load application data from binary files.

## Implementation

The application is developed in the C programming language. Refer to the [Installation](#installation) section for setup instructions.

## How to Use

To use the application, follow these steps:

```bash
# Example installation steps
git clone https://github.com/maximdudai/fp-project.git

cd fp-project

gcc main.c -o main.exe
./main.exe  
