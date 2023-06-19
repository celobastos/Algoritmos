#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>      
using namespace std;

typedef struct Node{
    int data;
    Node* left;
    Node* right;
}Node;

Node* insert(Node* root, int val){    
    if (root == NULL) {
        root = new Node;
        root->data = val;
        root->left = NULL;
        root->right = NULL;
    }
    else if (val < root->data) {
        root->left = insert(root->left, val);
    }
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}
Node* rotate_r(Node* root){
    Node* aux = root->left;
    Node* leaf = aux->right;

    aux->right = root;
    root->left = leaf;

    return aux;
}

Node* rotate_l(Node* root){
    Node* aux = root->right;
    Node* leaf = aux->left;

    aux->left = root;
    root->right = leaf;

    return aux;
}
Node* arvoreTorta(Node* root, int *contador){
    if(root == NULL)return root;
    if(root->right!=NULL){
        root = rotate_l(root);
        *contador = *contador + 1;
        

        root = arvoreTorta(root,contador);
    }
    else root->left = arvoreTorta(root->left,contador);

    return root;
}
void printaArvore(Node* root, int altura, int &contador){
    if(root == NULL) return;
    printaArvore(root->left, altura, contador);
    printaArvore(root->right, altura, contador);
    contador = contador + 1;
    //cout << "ALTURA : " << altura << "CONTADOR " << contador << endl;

    if(contador == altura) {cout << root->data;
    contador = 0;}    
    else cout << root->data << " ";
    
}
Node* part2(Node* root, int *contadorL, int *contadorR){
    if(root == NULL)return root;
    
    if(root->right==NULL){
        int value;
        cin >> value;
        while(root->data!=value){
            root = rotate_r(root);
            *contadorR = *contadorR + 1;
            
        }
    }
    else{
        int value;
        cin >> value;
        while(root->data!=value){
            root = rotate_l(root);
            *contadorL = *contadorL + 1;
        }
    }
    root->left = part2(root->left,contadorL,contadorR);
    root->right = part2(root->right,contadorL,contadorR);

    return root;
}
int max(int a, int b){
    return(a >= b)? a : b;
}
int height(Node* root){
    if(root == NULL)return 0;
    return 1 + max(height(root->left), height(root->right));
}
bool ta_Balanceada(Node* root){
    int left_height;
    int right_height;

    if(root == NULL)return 1;

    left_height = height(root->left);
    right_height = height(root->right);
    
    if(abs(left_height-right_height) <= 1 && ta_Balanceada( root->left) && ta_Balanceada( root->right))
    return 1;

    return 0;
}

int main(){
    int tam;
    while(scanf("%d",&tam)!=EOF){
        int valor;
        Node *raiz = NULL;
        int altura;
        int contador1;
        int contadorR = 0, contadorL = 0;
        for(int contador = 0; contador < tam; contador++){
        cin >> valor;
        raiz = insert(raiz, valor);

    }
  
        raiz = arvoreTorta(raiz, &contadorL);

        raiz = part2(raiz,&contadorL, &contadorR);
    

        altura = height(raiz);
        cout <<  contadorL<<" " ;
        cout << contadorR<< endl;
        printaArvore(raiz, tam, contador1);
        cout << endl;
        if(ta_Balanceada(raiz))cout << "true";
        if(!ta_Balanceada(raiz))cout << "false";
        cout << endl;
        cout << endl;

    }
    return 0;
} 