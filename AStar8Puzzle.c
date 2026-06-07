#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 3

typedef struct Node {
    int mat[N][N];
    int x, y;
    int cost, level;
    struct Node* parent;
} Node;

typedef struct {
    Node* arr[10000];
    int size;
} PriorityQueue;

int goal[N][N];
int nodesExpanded = 0;

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node;
    int temp;

    node = (Node*)malloc(sizeof(Node));

    memcpy(node->mat, mat, sizeof(node->mat));

    temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;
    node->cost = 0;

    return node;
}

int calculateCost(int mat[N][N]) {
    int count = 0;
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (mat[i][j] && mat[i][j] != goal[i][j])
                count++;
        }
    }

    return count;
}

int isSafe(int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < N)
        return 1;
    return 0;
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

void printPath(Node* root) {
    if (root == NULL)
        return;

    printPath(root->parent);
    printMatrix(root->mat);
}

int isGoal(int mat[N][N]) {
    if (memcmp(mat, goal, sizeof(goal)) == 0)
        return 1;
    return 0;
}

void push(PriorityQueue* pq, Node* node) {
    pq->arr[pq->size] = node;
    pq->size++;
}

Node* pop(PriorityQueue* pq) {
    int minIndex = 0;
    int i, f1, f2;
    Node* temp;

    for (i = 1; i < pq->size; i++) {
        f1 = pq->arr[i]->cost + pq->arr[i]->level;
        f2 = pq->arr[minIndex]->cost + pq->arr[minIndex]->level;

        if (f1 < f2)
            minIndex = i;
    }

    temp = pq->arr[minIndex];
    pq->size--;
    pq->arr[minIndex] = pq->arr[pq->size];

    return temp;
}

void main() {
    int initial[N][N];
    int x = 0, y = 0;
    int i, j;
    int newX, newY;
    PriorityQueue pq;
    Node* root;
    Node* min;
    Node* child;
    clock_t start, end;

    clrscr();

    printf("Enter initial state:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);

            if (initial[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    printf("Enter goal state:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &goal[i][j]);
        }
    }

    pq.size = 0;

    root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(root->mat);
    push(&pq, root);

    start = clock();

    while (pq.size > 0) {
        min = pop(&pq);
        nodesExpanded++;

        if (isGoal(min->mat)) {
            end = clock();

            printf("Solution Path:\n");
            printPath(min);

            printf("Path Cost: %d\n", min->level);
            printf("Nodes Expanded: %d\n", nodesExpanded);
            printf("Time: %.4f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

            getch();
            return;
        }

        for (i = 0; i < 4; i++) {
            newX = min->x + row[i];
            newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat);
                push(&pq, child);
            }
        }
    }

    printf("No solution found!\n");

    getch();
}