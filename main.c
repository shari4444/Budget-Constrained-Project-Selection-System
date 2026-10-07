/*
 ============================================================================
 Project Title : Budget-Constrained Project Selection System
 Algorithm     : 0/1 Knapsack using Dynamic Programming
 Subject       : Analysis and Design of Algorithms (AOA) Mini-Project
 Module        : Module 4 - Dynamic Programming
 Team Members  : Sharvari Chaudhari (25102B0082)
                 Karthik Akinapelly (25102B0074)
                 Satyajeet Prasad   (25102B0067)
 ============================================================================
*/

#include <stdio.h>
#include <string.h>

#define MAX_PROJECTS 100
#define MAX_BUDGET 10000

// Structure to store project information
typedef struct {
    int id;
    char title[100];
    int cost;
    int benefit;
    int selected; // 1 if selected in optimal solution, 0 otherwise
} Project;

// Global DP table: DP[i][w] stores maximum benefit achievable
// using a subset of the first i projects with budget constraint w
int DP[MAX_PROJECTS + 1][MAX_BUDGET + 1];

// Utility function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to print a divider line for neat terminal presentation
void printLine(char ch, int length) {
    for (int i = 0; i < length; i++) {
        putchar(ch);
    }
    putchar('\n');
}

int main() {
    int n;          // Number of projects
    int budget;     // Total budget available
    Project projects[MAX_PROJECTS + 1];

    printLine('=', 70);
    printf("   BUDGET-CONSTRAINED PROJECT SELECTION SYSTEM\n");
    printf("   0/1 Knapsack Algorithm using Dynamic Programming\n");
    printf("   AOA Mini-Project | Module 4\n");
    printLine('=', 70);

    // --- STEP 1: INPUT NUMBER OF PROJECTS ---
    while (1) {
        printf("\nEnter the number of projects (1 to %d): ", MAX_PROJECTS);
        if (scanf("%d", &n) != 1) {
            printf("[Error] Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        if (n <= 0 || n > MAX_PROJECTS) {
            printf("[Error] Number of projects must be between 1 and %d.\n", MAX_PROJECTS);
            continue;
        }
        break;
    }

    // --- STEP 2: INPUT PROJECT DETAILS ---
    printf("\n--- Enter Details for Each Project ---\n");
    for (int i = 1; i <= n; i++) {
        projects[i].selected = 0; // initialize selection status
        
        printf("\nProject %d:\n", i);
        
        // Project ID
        while (1) {
            printf("  Project ID (integer): ");
            if (scanf("%d", &projects[i].id) != 1) {
                printf("  [Error] Invalid ID. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        while (getchar() != '\n'); // flush newline

        // Project Title
        printf("  Project Title: ");
        if (fgets(projects[i].title, sizeof(projects[i].title), stdin) != NULL) {
            size_t len = strlen(projects[i].title);
            if (len > 0 && projects[i].title[len - 1] == '\n') {
                projects[i].title[len - 1] = '\0';
            }
        }
        if (strlen(projects[i].title) == 0) {
            snprintf(projects[i].title, sizeof(projects[i].title), "Project_%d", projects[i].id);
        }

        // Project Cost
        while (1) {
            printf("  Cost (INR > 0): ");
            if (scanf("%d", &projects[i].cost) != 1) {
                printf("  [Error] Invalid cost. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            if (projects[i].cost <= 0) {
                printf("  [Error] Cost must be greater than 0.\n");
                continue;
            }
            break;
        }

        // Expected Benefit
        while (1) {
            printf("  Expected Benefit (score/value > 0): ");
            if (scanf("%d", &projects[i].benefit) != 1) {
                printf("  [Error] Invalid benefit. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            if (projects[i].benefit <= 0) {
                printf("  [Error] Benefit must be greater than 0.\n");
                continue;
            }
            break;
        }
    }

    // --- STEP 3: INPUT TOTAL BUDGET ---
    while (1) {
        printf("\nEnter the Total Available Budget (INR, 1 to %d): ", MAX_BUDGET);
        if (scanf("%d", &budget) != 1) {
            printf("[Error] Invalid budget. Please enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }
        if (budget <= 0 || budget > MAX_BUDGET) {
            printf("[Error] Budget must be between 1 and %d.\n", MAX_BUDGET);
            continue;
        }
        break;
    }

    // --- STEP 4: DYNAMIC PROGRAMMING TABLE CONSTRUCTION ---
    // Recurrence Relation:
    // If cost[i] <= w:
    //   DP[i][w] = max(DP[i-1][w], benefit[i] + DP[i-1][w - cost[i]])
    // Otherwise:
    //   DP[i][w] = DP[i-1][w]
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            if (i == 0 || w == 0) {
                DP[i][w] = 0; // Base case: 0 projects or 0 budget yields 0 benefit
            } else if (projects[i].cost <= w) {
                DP[i][w] = max(
                    DP[i - 1][w],                                      // Exclude project i
                    projects[i].benefit + DP[i - 1][w - projects[i].cost] // Include project i
                );
            } else {
                DP[i][w] = DP[i - 1][w]; // Project i exceeds current capacity w
            }
        }
    }

    // Maximum achievable benefit is stored at DP[n][budget]
    int maxBenefit = DP[n][budget];

    // --- STEP 5: BACKTRACKING TO FIND SELECTED PROJECTS ---
    int w = budget;
    int budgetUsed = 0;
    int selectedCount = 0;

    for (int i = n; i > 0; i--) {
        // If the value came from including project i:
        // DP[i][w] != DP[i-1][w] means project i was selected
        if (DP[i][w] != DP[i - 1][w]) {
            projects[i].selected = 1;
            budgetUsed += projects[i].cost;
            selectedCount++;
            w -= projects[i].cost; // Reduce remaining capacity
        } else {
            projects[i].selected = 0; // Project was not selected
        }
    }

    int remainingBudget = budget - budgetUsed;

    // --- STEP 6: DISPLAY DYNAMIC PROGRAMMING TABLE ---
    printf("\n");
    printLine('-', 70);
    printf("DYNAMIC PROGRAMMING TABLE (DP[i][w])\n");
    printf("Each row represents projects considered; columns represent budget.\n");
    printLine('-', 70);

    // If budget is very large, limit printed columns so terminal doesn't overflow
    int step = 1;
    if (budget > 25) {
        step = (budget + 24) / 25; // sample columns neatly
        printf("(Showing budget columns with step size of %d due to large budget)\n", step);
    }

    printf("%-8s |", "Proj\\Cap");
    for (int col = 0; col <= budget; col += step) {
        printf("%5d", col);
    }
    printf("\n");
    printLine('-', 11 + ((budget / step) + 1) * 5);

    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("%-8s |", "Base(0)");
        } else {
            printf("P%-7d |", projects[i].id);
        }
        for (int col = 0; col <= budget; col += step) {
            printf("%5d", DP[i][col]);
        }
        printf("\n");
    }
    printLine('-', 70);

    // --- STEP 7: DISPLAY SELECTION RESULTS ---
    printf("\n");
    printLine('=', 70);
    printf("                    PROJECT SELECTION RESULTS\n");
    printLine('=', 70);

    // Selected Projects Table
    printf("\n[ SELECTED PROJECTS ] (%d selected)\n", selectedCount);
    printLine('-', 70);
    printf("%-6s | %-25s | %-12s | %-15s\n", "ID", "Title", "Cost (INR)", "Benefit");
    printLine('-', 70);
    if (selectedCount == 0) {
        printf("No projects could be selected within the given budget.\n");
    } else {
        for (int i = 1; i <= n; i++) {
            if (projects[i].selected) {
                printf("%-6d | %-25s | %-12d | %-15d\n",
                       projects[i].id, projects[i].title, projects[i].cost, projects[i].benefit);
            }
        }
    }
    printLine('-', 70);

    // Rejected Projects Table
    printf("\n[ REJECTED / UNSELECTED PROJECTS ] (%d rejected)\n", n - selectedCount);
    printLine('-', 70);
    printf("%-6s | %-25s | %-12s | %-15s\n", "ID", "Title", "Cost (INR)", "Benefit");
    printLine('-', 70);
    if (n - selectedCount == 0) {
        printf("All projects were successfully selected!\n");
    } else {
        for (int i = 1; i <= n; i++) {
            if (!projects[i].selected) {
                printf("%-6d | %-25s | %-12d | %-15d\n",
                       projects[i].id, projects[i].title, projects[i].cost, projects[i].benefit);
            }
        }
    }
    printLine('-', 70);

    // Summary Card
    printf("\n[ OPTIMAL SELECTION SUMMARY ]\n");
    printLine('-', 40);
    printf("Total Available Budget : INR %d\n", budget);
    printf("Total Budget Used      : INR %d\n", budgetUsed);
    printf("Remaining Budget       : INR %d\n", remainingBudget);
    printf("Total Maximum Benefit  : %d\n", maxBenefit);
    printf("Selected Projects      : %d / %d\n", selectedCount, n);
    printLine('-', 40);

    printLine('=', 70);
    printf("Algorithm execution complete. Optimal combination achieved.\n");
    printLine('=', 70);

    return 0;
}
