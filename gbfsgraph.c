#include <stdio.h>
#include <conio.h>

#define MAX 20

int findBest(int open[], int h[], int n) {
    int i;
    int min = 9999;
    int index = -1;

    for (i = 0; i < n; i++) {
        if (open[i] == 1 && h[i] < min) {
            min = h[i];
            index = i;
        }
    }

    return index;
}

void printPath(int parent[], int goal) {
    if (parent[goal] == -1) {
        printf("%d ", goal);
        return;
    }

    printPath(parent, parent[goal]);
    printf("%d ", goal);
}

void GBFS(int graph[MAX][MAX], int h[], int n, int start, int goal) {
    int open[MAX], closed[MAX], parent[MAX];
    int i, current, neighbor;
    int nodesExpanded = 0;

    for (i = 0; i < n; i++) {
        open[i] = 0;
        closed[i] = 0;
        parent[i] = -1;
    }

    open[start] = 1;

    while (1) {
        current = findBest(open, h, n);

        if (current == -1) {
            printf("No Path Found!\n");
            return;
        }

        open[current] = 0;
        closed[current] = 1;
        nodesExpanded++;

        if (current == goal) {
            printf("\nGBFS Result\n");
            printf("Path: ");
            printPath(parent, goal);
            printf("\nNodes Expanded: %d", nodesExpanded);
            return;
        }

        for (neighbor = 0; neighbor < n; neighbor++) {

            if (graph[current][neighbor] != 0 &&
                closed[neighbor] == 0 &&
                open[neighbor] == 0) {

                parent[neighbor] = current;
                open[neighbor] = 1;
            }
        }
    }
}

void main() {
    int graph[MAX][MAX];
    int h[MAX];
    int n, start, goal;
    int i, j;

    clrscr();

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter heuristic values:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter goal node: ");
    scanf("%d", &goal);

    GBFS(graph, h, n, start, goal);

    getch();
}