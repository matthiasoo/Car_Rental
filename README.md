# 🚗 Car Rental – A Command-Line Vehicle Rental Application (C++)

A command-line application written in C++ for managing a vehicle rental system. The project allows users to handle customers, vehicles, and rental operations with full support for business logic and archiving.

---

## 🛠️ Features

### 👥 Customer Management
- Add new customers
- Archive (deactivate) customers
- Customer login system
- Support for different account types (e.g. Bronze, Golden, Diamond)
- Automatic discount calculation based on account type

### 🚗 Vehicle Management
- Support for multiple vehicle types: **bicycle, moped, car**
- Add and archive vehicles
- View available vehicles and detailed information

### 📅 Rental Management
- Rent/reserve vehicles
- End rental
- Archive completed rentals
- Calculate rental duration and cost (with discount support)

---

## 🧱 Architecture

- Using **managers** for customers, vehicles, and rentals
- Data stored in **in-memory repositories** (no persistent storage)
- Clients and vehicles are pre-initialized in code
- Implemented as a **CMake project**
- Works fully in **command-line interface (CLI)** mode

---

## ⚙️ Before You Begin

To build and run this CMake project on Windows:

1. Download the **MinGW Distro archive** from [nuwen.net](https://nuwen.net/mingw.html).
2. Install **CMake** from [cmake.org](https://cmake.org/).
3. Extract the MinGW archive to the `C:\` folder.
4. Add `C:\MinGW\bin` to your system `PATH`.

---

## ▶️ Building the Project and Running Tests

1. Navigate to the project directory:
    ```
    cd <Project Directory>
    ```

2. Create a build directory:
    ```
    mkdir build
    cd build
    ```

3. Generate build files using MinGW Makefiles:
    ```
    cmake -G "MinGW Makefiles" ..
    ```

4. Build the project:
    ```
    make
    ```

5. Run the tests:
    ```
    make check
    ```

The main executable will be located at:
    ```
    \build\View\CarRental.exe
    ```

---

## 📦 Planned Features

- Persistent data storage (file/database)
- Application logging (Logger)
- Internationalization
- Data protection and validation
- Graphical User Interface (GUI)

---

## ⚠️ Note

This application **does not persist data** — all changes made during runtime are lost after exit.