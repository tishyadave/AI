iddfs
#include <stdio.h>
#include <conio.h>

#define N 6 /* Number of nodes in the graph */

/* Global tracking variables */
int found = 0;
int nodesExpanded = 0;

/* Depth Limited Search (DLS) Engine */
void DLS(int graph[N][N], int current, int goal, int depth) {
    int i;

    /* Goal Check: If reached, print and set global flag */
    if (current == goal) {
        printf("%d ", current);
        found = 1;
        return;
    }

    /* Base Case: If depth limit is reached, stop deeper exploration */
    if (depth <= 0) {
        return;
    }

    nodesExpanded++;

    /* Explore adjacent nodes */
    for (i = 0; i < N; i++) {
        /* If edge exists and goal hasn't been discovered yet */
        if (graph[current][i] == 1 && !found) {
            DLS(graph, i, goal, depth - 1);
            
            /* Print node path sequence during stack backtracking */
            if (found) {
                printf("<- %d ", current);
                return;
            }
        }
    }
}

/* Iterative Deepening DFS Wrapper */
void IDDFS(int graph[N][N], int start, int goal, int maxDepth) {
    int iterations = 0;
    int depth;

    for (depth = 0; depth <= maxDepth; depth++) {
        found = 0;
        nodesExpanded = 0;
        iterations++;

        printf("\nDepth Limit = %d\nPath: ", depth);
        DLS(graph, start, goal, depth);

        if (found) {
            printf("\nGoal found at depth %d!", depth);
            printf("\nNodes Expanded in final level = %d", nodesExpanded);
            printf("\nTotal Iterations (Depths searched) = %d\n", iterations);
            return;
        } else {
            printf("[Goal not reached]");
        }
    }
    printf("\nGoal not found within maximum depth threshold.\n");
}

/* Main Function */
void main() {
    int start, goal, maxDepth;
    int i, j;

    /* Hardcoded 6x6 Adjacency Matrix from your class file */
    int graph[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    start = 0;    /* Root Node */
    goal = 5;     /* Target Destination */
    maxDepth = 5;

    clrscr(); /* Turbo C clear screen */

    printf("--- Iterative Deepening DFS (IDDFS) ---\n\n");
    printf("Graph Nodes: %d | Start: %d | Goal: %d\n", N, start, goal);

    IDDFS(graph, start, goal, maxDepth);

    getch(); /* Turbo C hold output window */
}