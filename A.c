#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
    struct tree *left, *right, *prev;
    int key, data;
} tree;

tree* append(int key, int data, tree *root, tree* prev);
tree* search(int key, tree *root);
void delete(int key, tree *root);
void rebuild(tree *root);
int mypow(int a, int b);


int main()
{
    tree *root = NULL;
    /*root = append(10, 20, root, NULL);
    root = append(10, 30, root, NULL);
    root = append(20, 20, root, NULL);
    root = append(5, 5, root, NULL);
    root = append(25, 5, root, NULL);
    root = append(15, 6, root, NULL);
    printf("%d %d\n", root->key, root->data);
    printf("%d %d\n", root->right->key, root->right->data);
    printf("%d %d %d\n", root->left->key, root->left->data, root->left->prev->key);
    tree *pointer = search(20, root);
    printf("%d %d %p\n",pointer->key, pointer->data, pointer);
    delete(20, root);
    if (root->right == NULL) {
        printf("Удалён\n");
    }
    else {
        printf("%d\n", root->right->left->key);
    }*/
    char s[100];
    int a = 0, b = 0;
    int i = 2;
    
    fgets(s, 100, stdin);
    while (s[0] != 'F') {
        a = 0;
        b = 0;
        i = 2;
        if (s[0] == 'A') {
            while (s[i] != ' ') {
                i++;
            }
            i--;
            for (int j = i; j > 1; j--) {
                a += ((int)s[j]-48)*mypow(10, i-j);
            }
            for (int j = strlen(s)-2; j > i+1; j--) {
                b += ((int)s[j]-48)*mypow(10, strlen(s)-2-j);
            }
            root = append(a, b, root, NULL);
        }
        if (s[0] == 'S') {
            for (int j = strlen(s)-2; j > 1; j--) {
                b += ((int)s[j]-48)*mypow(10, strlen(s)-2-j);
            }
            if (search(b, root)!=NULL) {
                printf("%d %d ", search(b, root)->key, search(b, root)->data);
            }
        }
        if (s[0] == 'D') {
            for (int j = strlen(s)-2; j > 1; j--) {
                b += ((int)s[j]-48)*mypow(10, strlen(s)-2-j);
            }
            delete(b, root);
        }
        
        fgets(s, 100, stdin);
    }
    while (root->right != NULL) {
        delete(root->right->key, root);
    }
    while (root->left != NULL) {
        delete(root->left->key, root);
    }
    delete(root->key, root);
    return 0;
}

tree* append(int key, int data, tree *root, tree* prev) {  
        
    if (root == NULL) {  
        root = (tree*)malloc(sizeof(tree));
        if (root == NULL) {
            printf("LOX");
            exit(1);
        }
        root->key = key;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->prev = prev;
    }
    else if (root->key > key) {
        root->left = append(key, data, root->left, root);
    }
    else if (root->key < key) {
        root->right = append(key, data, root->right, root);
    }
    else {
        root->data = data;
    }
    return root;
}

tree* search(int key, tree *root) {
    if (root == NULL) {
        return NULL;
    }    
    else if (root->key == key) {
        return root;
    }
    else if (root->key > key) {
        return search(key, root->left);
    }
    else {
        return search(key, root->right);
    }
}

void delete(int key, tree *root) {
    tree *what_del = search(key, root);
    if (what_del != NULL) {
        if (what_del->left == NULL && what_del->right == NULL) {
            if (what_del->prev != NULL) {            
                if (what_del->prev->key > key) {
                    what_del->prev->left = NULL;
                }
                else {
                    what_del->prev->right = NULL;
                }
            }
            free(what_del);
        }
        else if (what_del->left == NULL && what_del->right != NULL) {
            if (what_del->prev != NULL) {
                what_del->right->prev = what_del->prev;
                if (what_del->prev->key > key) {
                    what_del->prev->left = what_del->right;
                }
                else {
                    what_del->prev->right = what_del->right;
                }
                free(what_del);
            }
            else {
                what_del->right->prev = NULL;
                free(what_del);
            }
        }
        else if (what_del->left != NULL && what_del->right == NULL) {
            if (what_del->prev != NULL) {
                what_del->left->prev = what_del->prev;
                if (what_del->prev->key > key) {
                    what_del->prev->left = what_del->left;
                }
                else {
                    what_del->prev->right = what_del->left;
                }
                free(what_del);
            }
            else {
                what_del->left->prev = NULL;
                free(what_del);
            }
        }
        else {
            rebuild(what_del);
        }
    }
}

void rebuild(tree *root) {
    tree *current_root = root;
    if (current_root->right != NULL) {
        current_root->data = current_root->right->data;
        current_root->key = current_root->right->key;
        rebuild(current_root->right);
    }
    else {
        if (current_root->left == NULL) {
            free(current_root);
        }
        else {
            current_root->left->prev = current_root->prev;
            current_root->prev->right = current_root->left;
            free(current_root);
        }
    }
}

int mypow(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c = c*a;
    }
    return c;
}
