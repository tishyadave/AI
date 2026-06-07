csp
#include <stdio.h>
#include <conio.h>

#define MAX 10

int graph[MAX][MAX];
int color[MAX];
int n;
int m; 

int isSafe(int v, int c) {
    int i;
    for (i = 0; i < n; i++) {
        if (graph[v][i] == 1 && color[i] == c) {
            return 0; 
        }
    }
    return 1; 
}

int solve(int v) {
    int c;

    if (v == n) {
        return 1; 
    }

    for (c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c; /* Assign color c */

            /* Recursively assign colors to the rest of the nodes */
            if (solve(v + 1)) {
                return 1;
            }

            color[v] = 0;        }
    }

    return 0; 
}

/* Main Function */
void main() {
    int i, j;
    clrscr(); 
    printf("--- Graph Coloring Problem (CSP) ---\n\n");

    printf("Enter number of nodes (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge, 1 for edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter number of colors available: ");
    scanf("%d", &m);

    for (i = 0; i < n; i++) {
        color[i] = 0;
    }

    if (solve(0)) {
        printf("\nSolution exists! Node Assignments:\n");
        for (i = 0; i < n; i++) {
            printf("Node %d -> Color %d\n", i, color[i]);
        }
    } else {
        printf("\nNo solution exists with %d colors.\n", m);
    }

    getch();
}