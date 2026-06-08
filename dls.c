#include <stdio.h>
#include <conio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int parent[MAX];

int DLS(int current, int goal, int limit, int n) {
    int i;

    visited[current] = 1;

    if (current == goal)
        return 1;

    if (limit <= 0)
        return 0;

    for (i = 0; i < n; i++) {
        if (graph[current][i] != 0 && visited[i] == 0) {
            parent[i] = current;

            if (DLS(i, goal, limit - 1, n))
                return 1;
        }
    }

    return 0;
}

void printPath(int start, int goal) {
    if (goal == start) {
        printf("%d ", start);
        return;
    }

    printPath(start, parent[goal]);
    printf("%d ", goal);
}

void main() {
    int n, start, goal, limit;
    int i, j;
    int found;

    clrscr();

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter goal node: ");
    scanf("%d", &goal);

    printf("Enter depth limit: ");
    scanf("%d", &limit);

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    found = DLS(start, goal, limit, n);

    if (found) {
        printf("\nGoal found within depth limit\n");
        printf("Path: ");
        printPath(start, goal);
    } else {
        printf("\nGoal not found within depth limit");
    }

    getch();
}