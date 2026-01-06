# ✈️ Flight Booking System
A C++ command-line application for managing flight reservations. This project was developed as a university assignment to demonstrate object-oriented programming, file handling, and architectural patterns in C++.

## 🎓 Project Overview
This system allows users to manage flights, airports, and reservations through a CLI (Command Line Interface). It supports two types of users: Admins (who manage the data) and Customers (who book flights).

## ✨ Features
* **User Authentication:** Secure login and registration with password hashing.

### Role-Based Access:

* **Admin:** Create/Edit/Delete flights and airports, manage users.

* **Customer:** Search for flights, book tickets, view personal reservations, manage profile.

* **Data Persistence:** Custom file-based database system using both text (for users) and binary files (for flights/airports) to save data between sessions.

* **Input Validation:** Checks for valid dates, IATA codes, and numeric inputs.

## 🛠️ Tech Stack
**Language:** C++20

**Build System:** CMake (Minimum version 3.31)

**Interface:** Console/Terminal (CLI)
