#include <stdio.h> 
#include <stdlib.h> 
  
#define INF 1000 
  
struct Node { 
    int id; 
    int val;            
    int leaf;           
    int num_kids; 
    struct Node* kids[10];  
}; 
  
int total_nodes = 0; 
  
struct Node* build_tree(int level) { 
    struct Node* n = (struct Node*)malloc(sizeof(struct Node)); 
    n->id = total_nodes++; 
  
    printf("\n[Setting up Node %d at Depth %d]\n", n->id, level); 
    printf("Is this a leaf node? (1=Yes / 0=No): "); 
    int is_leaf; 
    scanf("%d", &is_leaf); 
  
    if (is_leaf == 1) { 
        n->leaf = 1; 
        n->num_kids = 0; 
        printf("Enter score for Node %d: ", n->id); 
        scanf("%d", &n->val); 
    } else { 
        n->leaf = 0; 
        printf("How many children for Node %d?: ", n->id); 
        scanf("%d", &n->num_kids); 
  
        for (int i = 0; i < n->num_kids; i++) { 
            printf("> Creating child %d of Node %d...", i + 1, n->id); 
            n->kids[i] = build_tree(level + 1); 
        } 
    } 
    return n; 
} 
  
int solve(struct Node* n, int is_max) { 
    if (n->leaf == 1) { 
        printf("  Found leaf Node %d: value = %d\n", n->id, n->val); 
        return n->val; 
    } 
  
    if (is_max) { 
        int best = -INF; 
        printf("\nNode %d (MAX) is checking its children...\n", n->id); 
        for (int i = 0; i < n->num_kids; i++) { 
            int result = solve(n->kids[i], 0); //  
            printf("  Node %d (MAX) comparing: max(%d, %d)", n->id, best, result); 
            if (result > best) { 
                best = result; 
            } 
            printf(" -> current best is %d\n", best); 
        } 
        printf("Result for Node %d (MAX) = %d\n", n->id, best); 
        return best; 
  
    } else { 
        int best = INF; 
        printf("\nNode %d (MIN) is checking its children...\n", n->id); 
        for (int i = 0; i < n->num_kids; i++) { 
            int result = solve(n->kids[i], 1); //  
            printf("  Node %d (MIN) comparing: min(%d, %d)", n->id, best, result); 
            if (result < best) { 
                best = result; 
            } 
            printf(" -> current best is %d\n", best); 
        } 
        printf("Result for Node %d (MIN) = %d\n", n->id, best); 
        return best; 
    } 
} 
  
int main() { 
  
    struct Node* root = build_tree(0); 
  
    int final_score = solve(root, 1); 
  
    return 0;