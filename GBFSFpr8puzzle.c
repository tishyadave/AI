#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define N 3

struct Node {
    int mat[N][N];
    int x, y;
    int h;
    struct Node* parent;
};

int goal[N][N] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

struct Node* OPEN[1000];
int openSize = 0;

int calculateHeuristic(int mat[N][N]) {
    int h = 0;
    int i, j, val, targetX, targetY;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (mat[i][j] != 0) {
                val = mat[i][j];
                targetX = (val - 1) / N;
                targetY = (val - 1) % N;
                h = h + abs(i - targetX) + abs(j - targetY);
            }
        }
    }

    return h;
}

struct Node* newNode(int mat[N][N], int x, int y, int newX, int newY, struct Node* parent) {
    struct Node* node;
    int i, j, temp;

    node = (struct Node*)malloc(sizeof(struct Node));
    node->parent = parent;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            node->mat[i][j] = mat[i][j];
        }
    }

    temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->h = calculateHeuristic(node->mat);

    return node;
}

int isSafe(int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < N)
        return 1;
    return 0;
}

int compare(int a[N][N], int b[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (a[i][j] != b[i][j])
                return 0;
        }
    }

    return 1;
}

void printMatrix(int mat[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void printPath(struct Node* node) {
    if (node == NULL)
        return;

    printPath(node->parent);
    printMatrix(node->mat);
}

void push(struct Node* node) {
    OPEN[openSize] = node;
    openSize++;
}

struct Node* pop() {
    int minIndex = 0;
    int i;
    struct Node* node;

    for (i = 1; i < openSize; i++) {
        if (OPEN[i]->h < OPEN[minIndex]->h)
            minIndex = i;
    }

    node = OPEN[minIndex];
    openSize--;
    OPEN[minIndex] = OPEN[openSize];

    return node;
}

void main() {
    int initial[N][N];
    int x = 0, y = 0;
    int i, j;
    int newX, newY;
    struct Node* root;
    struct Node* current;
    struct Node* child;

    clrscr();

    printf("Enter initial 8-puzzle state 0 for blank:\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);

            if (initial[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    root = (struct Node*)malloc(sizeof(struct Node));
    root->parent = NULL;
    root->x = x;
    root->y = y;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            root->mat[i][j] = initial[i][j];
        }
    }

    root->h = calculateHeuristic(root->mat);

    push(root);

    while (openSize > 0) {
        current = pop();

        if (compare(current->mat, goal)) {
            printf("\nGoal State Reached:\n\n");
            printPath(current);
            getch();
            return;
        }

        for (i = 0; i < 4; i++) {
            newX = current->x + row[i];
            newY = current->y + col[i];

            if (isSafe(newX, newY)) {
                child = newNode(current->mat, current->x, current->y, newX, newY, current);
                push(child);
            }
        }
    }

    printf("No solution found\n");

    getch();
}