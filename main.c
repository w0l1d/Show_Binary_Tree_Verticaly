#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Nd {
    int info;
    int cpt;
    struct Nd *left;
    struct Nd *right;
}Node;


Node* create_NodePt(int val) {
    Node *ne = (Node*) malloc(sizeof(Node));
    if (!ne) {
        printf("\n\n Memory Error \n");
        exit(0);
    }

    ne->right = ne->left = NULL;
    ne->info = val;
    ne->cpt = 1;
    return ((Node*) ne);
}

Node* insert_Pt(Node *root, int val) {
    if (!root)
    {
        Node *ne = create_NodePt(val);
        return ((Node*) ne);
    }
    if (root->info > val)
        root->left = insert_Pt(root->left, val);
    else if (root->info < val)
        root->right = insert_Pt(root->right, val);
    else
        root->cpt++;

    return ((Node*)root);
}

int tree_deepness(Node *root) {
    if (!root)
        return 0;
    int right = tree_deepness(root->right) + 1;
    int left = tree_deepness(root->left) + 1;
    return (right>left)?right:left;
}

void assign_val_to_Mtx(Node *root, int *matrice, int cols, int line, int col, int ss) {
    if (!root)
        return;
    *((matrice+(line*cols))+col) = root->info;

    assign_val_to_Mtx(root->right, matrice, cols, line + 1, col + ss, ss/2);
    assign_val_to_Mtx(root->left, matrice, cols, line + 1, col - ss, ss/2);

}

void Show_Real_Tree(Node *root) {
    int prof = tree_deepness(root);
    int segma = 0;
    int tmp;
    for (int i = 0; i < prof; ++i) {
        tmp = (int)pow(2, i);
        segma+=tmp;
    }

    int matrice[prof][segma];
    int *pt = (int *) matrice;

    for (int i = 0; i < prof; ++i)
        for (int j = 0; j < segma; ++j)
            matrice[i][j] = -99;

    assign_val_to_Mtx(root, pt, segma,  0, segma/2+1, (segma/2+1)/2);

    for (int i = 0; i < prof; ++i) {
        for (int j = 0; j < segma; ++j) {
            if (matrice[i][j] == -99)
                printf("**");
            else
                printf("%02d", matrice[i][j]);
        }
        printf("\n");
    }
}

int main() {

    Node *root = NULL;

    root = insert_Pt(root, 11);


    root = insert_Pt(root, 5);

    root = insert_Pt(root, 14);
    root = insert_Pt(root, 6);
    root = insert_Pt(root, 13);
    root = insert_Pt(root, 7);
    root = insert_Pt(root, 12);

    printf("\n\n");
    Show_Real_Tree(root);
    printf("\n\n");
    return 0;
}
