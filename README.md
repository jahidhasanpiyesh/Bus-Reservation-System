# 🚌 Online Bus Reservation System in C

A simple and efficient **Bus Reservation System** built using the **C programming language**. This project provides a console-based ticket booking experience where users can view buses, check seat availability, book tickets, and manage reservations.

---

## ⭐ Features

* View available buses
* Check seat availability
* Book tickets
* Cancel ticket
* Store passenger information
* Easy file handling for saving data
* Simple and clean console UI

---

## 🛠 Technologies Used

* **Language:** C
* **Compiler:** GCC / MinGW
* **IDE (optional):** VS Code / CodeBlocks / Dev-C++

---

## 🚀 How to Run

1. Install any C compiler (GCC recommended).
2. Clone the repository:

   ```bash
   git clone https://github.com/jahidhasanpiyesh/-Bus-Reservation-System.git
   ```
3. Open the project folder.
4. Compile the program:

   ```bash
   gcc main.c -o bus
   ```
5. Run the program:

   ```bash
   ./bus
   ```

---

## 📁 Project Structure (Example)

```
Bus-Reservation-System/
├─ main.c
├─ bus.h
├─ data.txt (for storing booking info)
└─ README.md
```

---

## 🎯 Learning Outcomes

This project helps students practice:

* File handling in C
* Arrays & structures
* Functions and modular coding
* Input validation
* Basic system design

---

## 🐞 Common Errors Faced During Development

Here are the **realistic and commonly expected errors** that occur while building a Bus Reservation System in C:

### 1️⃣ File Not Found (data.txt missing)

The program stores booking information inside `data.txt`. If the file is missing, the program cannot load or save data.

* **Fix:** Create an empty `data.txt` file in the project folder.

### 2️⃣ Wrong Input Crash (Letters instead of numbers)

When the program expects a number but the user enters text, it may crash.

* **Fix:** Validate numeric input and clear the buffer.

### 3️⃣ Seat Number Out of Range

If the user enters an invalid seat number (too high or low), the program may behave incorrectly.

* **Fix:** Add range checks to ensure the seat number is valid.

### 4️⃣ Compilation Errors (Missing function prototypes)

Errors appear when functions are used without being declared, or header file is not included properly.

* **Fix:** Ensure all function prototypes are included in `bus.h`.

### 5️⃣ Data Overwriting (Wrong file mode)

Using `"w"` instead of `"a"` overwrites previous booking data.

* **Fix:** Use `"a"` mode when adding new records.

---
## 🤝 Contribution

Feel free to fork the repository and submit pull requests to improve features or fix bugs.

---

## 🛡️ License

This project is licensed under the **GNU General Public License v3.0**. 

### ⚖️ Permissions under GPLv3:
* **Commercial Use:** You can use this software for commercial purposes.
* **Modification:** You can modify the code, but you must keep the source code open.
* **Distribution:** You can distribute the original or modified code.
* **Credit:** You must give credit to the original author (Md Jahid Hasan).

See the [LICENSE](LICENSE) file for more details.

---

## 👤 Author

- **Developer:** Md Jahid Hasan  
- **Email:** jahidhasanpiyesh@gmail.com  
- **LinkedIn:** [Md Jahid Hasan](https://www.linkedin.com/in/md-jahid-hasan-9418b9298)  
- **Portfolio:** [My Portfolio](https://jahidhasanpiyesh.github.io/)
