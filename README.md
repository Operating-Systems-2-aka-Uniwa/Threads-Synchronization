<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

---

<p align="center">
  <strong>Operating Systems II</strong>
</p>

<h1 align="center">
  POSIX Threads - "What A Wonderful World!" Program
</h1>

<p align="center">
  <strong>Vasileios Evangelos Athanasiou</strong><br>
  Student ID: 19390005
</p>

<p align="center">
  <a href="https://github.com/Ath21" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/vasilis-athanasiou-7036b53a4/" target="_blank">LinkedIn</a>
</p>

<hr/>

<p align="center">
  <strong>Supervision</strong>
</p>

<p align="center">
  Supervisor: Vasileios Mamalis, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/vassilios-mamalis/" target="_blank">UNIWA Profile</a>
</p>

<p align="center">
  Co-supervisor: Nikolaos Psarras, Applications Lecturer
</p>

<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/nikolaos-psarras/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/psarras-nikolas-20234183/" target="_blank">LinkedIn</a>
</p>

</hr>

<p align="center">
  Athens, June 2022
</p>

---

# POSIX Threads – "What A Wonderful World!" Program

This repository contains an assignment for **Operating Systems II**, focusing on thread synchronization using POSIX threads to repeatedly print the phrase:


What A Wonderful World!


---

## Table of Contents

| Section | Folder/File | Description |
|------:|-------------|-------------|
| 1 | `assign/` | Assignment material |
| 1.1 | `assign/ASK-2B-OS-II-LAB-2021-22.png` | Assignment description in English |
| 1.2 | `assign/ΑΣΚ-2Β-ΛΣ-ΙΙ-ΕΡΓ-2021-22.png` | Assignment description in Greek |
| 2 | `src/` | Source code implementations |
| 2.1 | `src/semaphores.c` | Semaphore-based synchronization |
| 2.2 | `src/condition_vars.c` | Condition variable synchronization |
| 3 | `README.md` | Repository documentation |

---

## Project Overview

The project demonstrates synchronization techniques using **POSIX threads** to ensure correct printing order among multiple threads.

Three threads cooperate:

- Thread 1 prints `"What A "`
- Thread 2 prints `"Wonderful "`
- Thread 3 prints `"World!"`

The program continuously prints the phrase in correct sequence.

Two synchronization approaches are implemented:
- Semaphore-based synchronization
- Condition variable synchronization

---

## Objectives

- Implement multi-threaded execution using POSIX threads.
- Synchronize thread execution order correctly.
- Prevent race conditions using mutex protection.
- Demonstrate synchronization techniques in practice.

---

## Key Features

- **Thread Cooperation**  
  Multiple threads cooperate to print a single output sequence.

- **Synchronization Control**  
  Ensures proper execution order.

- **Mutex Protection**  
  Prevents race conditions in shared resources.

- **Continuous Execution**  
  Program runs until manually terminated.

---

## Program Structure

1. Initialize synchronization mechanisms.
2. Create three worker threads.
3. Each thread prints its assigned word.
4. Synchronization ensures proper printing order.
5. Execution repeats indefinitely.

---

## Requirements

- **Operating System:** Linux or Unix-like OS
- **Compiler:** GCC
- **Libraries:** POSIX Threads (`pthread`) and POSIX Semaphores

---

## Installation & Usage

### 1. Clone Repository
```bash
git clone https://github.com/Operating-Systems-2-aka-Uniwa/Threads-Synchronization.git
cd Threads-Synchronization
```

### 2. Compile Programs
```bash
gcc -o semaphores semaphores.c -lpthread -lrt
gcc -o condition_vars condition_vars.c -pthread
```

### 3. Run Programs
```bash
./semaphores
./condition_vars
```