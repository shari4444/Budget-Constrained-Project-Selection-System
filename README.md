# Budget-Constrained Project Selection System

> **Analysis and Design of Algorithms (AOA) Mini-Project**  
> An algorithmic decision-support tool using the **0/1 Knapsack Problem** via **Dynamic Programming** to select the optimal combination of projects under a fixed budget ceiling.

---

## 👥 Project Team

| Member Name | Roll Number |
| :--- | :--- |
| **Sharvari Chaudhari** | `25102B0082` |
| **Karthik Akinapelly** | `25102B0074` |
| **Satyajeet Prasad** | `25102B0067` |

---

## 📌 Problem Statement

Organizations and academic institutions frequently face a catalog of proposed projects with varying investment costs and expected benefits, constrained by a strict total budget. Because projects must be either completely funded or completely rejected (no partial completion allowed), this is formulated as a **0/1 Knapsack Problem**:

- **$\text{Select} = 1$:** The project is fully funded, incurring its cost and delivering its full benefit.
- **$\text{Reject} = 0$:** The project is not funded, incurring zero cost and delivering zero benefit.

Greedy strategies fail because items cannot be divided fractionally. **Dynamic Programming** guarantees finding the subset of projects that yields the maximum possible benefit without exceeding the available budget.

---

## ⚙️ Algorithmic Formulation

### Recurrence Relation

For project $i$ with cost $\text{cost}[i]$ and benefit $\text{benefit}[i]$, and current capacity $w$:

$$\text{DP}[i][w] = \begin{cases} 
\max\Big(\text{DP}[i-1][w],\; \text{benefit}[i] + \text{DP}[i-1][w - \text{cost}[i]]\Big) & \text{if } \text{cost}[i] \le w \\
\text{DP}[i-1][w] & \text{otherwise}
\end{cases}$$

### Backtracking
After constructing the DP table up to $\text{DP}[n][W]$, we trace backward from state $(n, W)$ to recover the exact set of selected projects:
- If $\text{DP}[i][w] \neq \text{DP}[i-1][w]$, project $i$ was selected; we subtract $\text{cost}[i]$ from remaining capacity $w$.
- If $\text{DP}[i][w] == \text{DP}[i-1][w]$, project $i$ was rejected.

### Complexities
- **Time Complexity:** $\mathcal{O}(n \times W)$ (pseudo-polynomial)
- **Space Complexity:** $\mathcal{O}(n \times W)$
- Where $n$ is the number of candidate projects and $W$ is the total budget.

---

## 📂 Project Structure

```text
.
├── index.html     # Interactive web interface (runs pure client-side 0/1 Knapsack)
├── style.css      # Warm earth/cream aesthetic styling
├── main.c         # Pure C implementation for terminal execution and viva
└── README.md      # Project documentation
```

---

## 🚀 How to Run

### 1. Web Application (Interactive UI)
The web interface runs completely in the browser without any backend, database, or external dependencies.

- Simply open `index.html` in any modern web browser, or serve it locally:
  ```bash
  python3 -m http.server 5500
  ```
- Visit: [http://localhost:5500](https://budget-constrainer.netlify.app/)

**Web Features:**
- **Dynamic Rows:** Adjust the number of projects and click "Generate Rows".
- **Preset Data:** Click "Load Sample Data" to pre-fill test values.
- **Instant Solution:** Calculates Maximum Achievable Benefit, Budget Used, Remaining Budget, Selected Projects, and Rejected Projects.
- **Input Validation:** Prevents negative numbers, non-numeric values, empty fields, and duplicate IDs.

---

### 2. C Program (Terminal / Viva Demo)
The core algorithm is also implemented in pure C (`main.c`) using standard I/O libraries.

#### Compilation:
```bash
gcc main.c -o knapsack
```

#### Execution:
```bash
./knapsack
```

#### Sample Interactive Run:
```text
======================================================================
   BUDGET-CONSTRAINED PROJECT SELECTION SYSTEM
   0/1 Knapsack Algorithm using Dynamic Programming
   AOA Mini-Project | Module 4
======================================================================

Enter the number of projects (1 to 100): 4

--- Enter Details for Each Project ---

Project 1:
  Project ID (integer): 1
  Project Title: Website Redesign
  Cost (INR > 0): 10
  Expected Benefit (score/value > 0): 60

Project 2:
  Project ID (integer): 2
  Project Title: Mobile App
  Cost (INR > 0): 20
  Expected Benefit (score/value > 0): 100

Project 3:
  Project ID (integer): 3
  Project Title: AI Dashboard
  Cost (INR > 0): 30
  Expected Benefit (score/value > 0): 120

Project 4:
  Project ID (integer): 4
  Project Title: Security System
  Cost (INR > 0): 15
  Expected Benefit (score/value > 0): 70

Enter the Total Available Budget (INR, 1 to 10000): 50

======================================================================
                    PROJECT SELECTION RESULTS
======================================================================

[ SELECTED PROJECTS ] (3 selected)
----------------------------------------------------------------------
ID     | Title                     | Cost (INR)   | Benefit        
----------------------------------------------------------------------
1      | Website Redesign          | 10           | 60             
2      | Mobile App                | 20           | 100            
4      | Security System           | 15           | 70             
----------------------------------------------------------------------

[ REJECTED / UNSELECTED PROJECTS ] (1 rejected)
----------------------------------------------------------------------
ID     | Title                     | Cost (INR)   | Benefit        
----------------------------------------------------------------------
3      | AI Dashboard              | 30           | 120            
----------------------------------------------------------------------

[ OPTIMAL SELECTION SUMMARY ]
----------------------------------------
Total Available Budget : INR 50
Total Budget Used      : INR 45
Remaining Budget       : INR 5
Total Maximum Benefit  : 230
Selected Projects      : 3 / 4
----------------------------------------
```

---

## 🧪 Sample Verification Test Cases

| Dataset | Budget ($W$) | Candidate Projects (Cost, Benefit) | Optimal Selected | Maximum Benefit | Budget Used |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Sample 1** | ₹50 | P1 (10, 60), P2 (20, 100), P3 (30, 120), P4 (15, 70) | **P1, P2, P4** | **230** | ₹45 |
| **Sample 2** | ₹30 | P1 (10, 50), P2 (15, 65), P3 (20, 90), P4 (25, 120) | **P1, P3** | **140** | ₹30 |
| **Sample 3** | ₹25 | A (12, 40), B (14, 50), C (25, 100) | **C** | **100** | ₹25 |

---

## 📜 Academic Integrity
This project was developed for academic submission under the **Analysis and Design of Algorithms (AOA)** curriculum. No heavy external frameworks or backend engines are required, keeping the code clean, reproducible, and easy to explain during a viva examination.
