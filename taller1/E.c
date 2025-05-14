// https://vjudge.net/contest/713089#problem/E

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int clave;
    int valor;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int clave, int valor){
    Node* node = (Node*)malloc(sizeof(Node));
    node->clave = clave;
    node->valor = valor;
    node->left =  NULL;
    node->right = NULL;

    return node;
}

Node* insert(Node* root, int clave, int valor ){
    if (root == NULL) {
        return createNode(clave, valor);
    }

    if (clave < root->clave) {
        root->left = insert(root->left, clave, valor);
    } else if (clave > root->clave) {
        root->right = insert(root->right, clave, valor);
    } else {
        root->valor = valor;
    }

    return root;
}

int search(Node* root, int clave){
    if( root == NULL)
        return -1;

    if(root->clave == clave)
        return root->valor;

    if(clave < root->clave)
        return search(root->left, clave);

    else
        return search(root->right, clave);
}
void freeMemory(Node* root){
    if(root){
        freeMemory(root->left);
        freeMemory(root->right);
        free(root);
    }
}

int main(){
    int N, Q;
    scanf("%d %d", &N, &Q);

    Node* root = NULL;
    
    for(int i = 0; i < N; i++){
        int value;
        scanf("%d", &value);
        root = insert(root, value, i);
    }

    // querys
    for(int i = 0; i < Q; i++){
        int query;
        scanf("%d", &query);
        query = search(root, query);
        printf("%d\n", query);
    }

    freeMemory(root);

    return 0;
}