# **Smart Route Optimisation System (APS)**

A C++ console-based system that allows users to:

- Compute the **shortest distance between two cities** using the **Floyd–Warshall algorithm**
- Compute a **Hamiltonian Path (Path-TSP)** between two cities that visits all other cities exactly once (Brute-force permutation method)
- *(Placeholder)* City traversal (BFS/DFS) — coming soon
- Manage city names, distances, and run multiple queries in a menu-driven interface

---

## 📌 **Features**

### ✅ **1. Shortest Path Between Two Cities**
Uses the **Floyd–Warshall Algorithm** to compute all-pair shortest paths.  
You can optionally print the full route using reconstructed `nextHop`.

---

### ✅ **2. Hamiltonian Path / Path-TSP**
Finds the **shortest route** that:
- Starts at **source**
- Ends at **destination**
- Visits **every other city exactly once**

**Algorithm:** Brute-force permutation  
**Time complexity:** `O((N-2)! * N)`  
**Recommended:** Works only for small graphs (**N < 11–12**)

---

### ❌ **3. Traversal (BFS/DFS)**  
Not implemented yet — reserved for team members.

---

## 🛠️ **How to Compile**

Use any C++ compiler. Example using **g++**:

```sh
g++ Main.cpp -o Main
```
### ▶️ How to Run
```sh
./Main
```

## 📌 **Code Architecture Overview**

### 🔧 **Algorithms Used**

---

### **1. Floyd–Warshall Algorithm**
A dynamic programming algorithm used to compute the **shortest paths between all pairs of cities**.

**Purpose in this project:**
- Computes **all-pair shortest distances**
- Builds the **`nextHop` matrix**, which is later used to reconstruct paths efficiently
- Ensures that even if a city pair has no direct edge, indirect shortest routes are identified

---

### **2. Brute-force Permutation (Hamiltonian Path / Path-TSP)**
Used to find the **shortest route from a given source to a given destination** while visiting **all other cities exactly once**.

**How it works:**
- Generates **all permutations** of intermediate cities  
- For each permutation:
  - Computes full route distance (Source → permutation → Destination)
  - Validates whether all legs in the path exist
- Tracks:
  - **Global minimum path distance**
  - **Best intermediate sequence** in `g_best_intermediate_path`

**Notes:**
- Time complexity: **O((N-2)! × N)**  
- Practical only for small datasets (`N < 11`)

---

## Contributors

<table>
    <tr>
        <td align="center">
        <a href="http://github.com/Sudhanshu-Ambastha">
            <img src="https://avatars.githubusercontent.com/u/135802131?v=4" width="100px;" alt=""/>
            <br />
            <sub><b>Sudhanshu Ambastha </b></sub>
        </a>
        <br />
    </td>
    <td align="center">
        <a href="https://github.com/Vishwas567917">
            <img src="https://avatars.githubusercontent.com/u/139749696?s=100&v=4" width="100px;" alt=""/>
            <br />
            <sub><b>Parth Shrivastava</b></sub>
        </a>
        <br />
    </td>
    <td align="center">
        <a href="https://github.com/Shrivatsa-Sharan-Garg">
            <img src="https://avatars.githubusercontent.com/u/179140208?v=4" width="100px;" alt=""/>
            <br />
            <sub><b>Shrivatsa Sharan Garg</b></sub>
        </a>
        <br/>
    </td>
    </tr>
</table>