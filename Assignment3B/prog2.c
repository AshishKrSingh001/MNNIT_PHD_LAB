#include <stdio.h>
#include <stdlib.h>

/*
Q2. Priority Queue Using a Red-Black Tree
Can a priority queue be implemented as a red-black tree?
What advantages does a heap implementation have over a red-black tree implementation?
*/

#define RED 1
#define BLACK 0

typedef struct node{
    int key;
    int color;
    struct node *left;
    struct node *right;
    struct node *parent;
}node;

// Create a new red node
node* createNode(int key){
    node *newNode=(node*)malloc(sizeof(node));
    newNode->key=key;
    newNode->color=RED;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->parent=NULL;
    return newNode;
}

// Return node color
int getColor(node *n){
    return n==NULL ? BLACK : n->color;
}

// Right rotation
node* LL(node *root){
    node *p=root->left;
    root->left=p->right;
    if(p->right!=NULL)
        p->right->parent=root;
    p->right=root;
    p->parent=root->parent;
    root->parent=p;
    return p;
}

// Left rotation
node* RR(node *root){
    node *p=root->right;
    root->right=p->left;
    if(p->left!=NULL)
        p->left->parent=root;
    p->left=root;
    p->parent=root->parent;
    root->parent=p;
    return p;
}

// Insert key
node* insert(node *root,int key){
    if(root==NULL)
        return createNode(key);

    if(key<root->key){
        root->left=insert(root->left,key);
        root->left->parent=root;
    }
    else if(key>root->key){
        root->right=insert(root->right,key);
        root->right->parent=root;
    }
    else
        return root;

    if(getColor(root->right)==RED &&
       getColor(root->left)==BLACK)
        root=RR(root);

    if(getColor(root->left)==RED &&
       getColor(root->left->left)==RED)
        root=LL(root);

    if(getColor(root->left)==RED &&
       getColor(root->right)==RED){
        root->color=RED;
        root->left->color=BLACK;
        root->right->color=BLACK;
    }

    return root;
}

// Insert and make root black
node* insertNode(node *root,int key){
    root=insert(root,key);
    root->color=BLACK;
    root->parent=NULL;
    return root;
}

// Find maximum
node* maximum(node *root){
    if(root==NULL)
        return NULL;

    while(root->right!=NULL)
        root=root->right;

    return root;
}

// Display tree
void inorder(node *root){
    if(root==NULL)
        return;

    inorder(root->left);
    printf("%d(%c) ",root->key,
           root->color==RED?'R':'B');
    inorder(root->right);
}

// Display highest priority
void top(node *root){
    node *p=maximum(root);

    if(p==NULL)
        printf("Priority Queue is empty\n");
    else
        printf("Highest Priority = %d\n",p->key);
}

// Fix black deletion
node* fixDelete(node *root,node *x,node *parent){
    if(parent==NULL)
        return root;

    if(x==parent->left){
        node *s=parent->right;

        if(getColor(s)==RED){
            s->color=BLACK;
            parent->color=RED;
            root=RR(parent);
            s=parent->right;
        }

        if(getColor(s)==BLACK &&
           getColor(s->left)==BLACK &&
           getColor(s->right)==BLACK){

            if(s!=NULL)
                s->color=RED;

            if(parent->color==RED)
                parent->color=BLACK;
        }
        else{
            if(s!=NULL && getColor(s->right)==RED){
                s->color=parent->color;
                parent->color=BLACK;

                if(s->right!=NULL)
                    s->right->color=BLACK;

                root=RR(parent);
            }
        }
    }
    else{
        node *s=parent->left;

        if(getColor(s)==RED){
            s->color=BLACK;
            parent->color=RED;
            root=LL(parent);
            s=parent->left;
        }

        if(getColor(s)==BLACK &&
           getColor(s->left)==BLACK &&
           getColor(s->right)==BLACK){

            if(s!=NULL)
                s->color=RED;

            if(parent->color==RED)
                parent->color=BLACK;
        }
        else{
            if(s!=NULL && getColor(s->left)==RED){
                s->color=parent->color;
                parent->color=BLACK;

                if(s->left!=NULL)
                    s->left->color=BLACK;

                root=LL(parent);
            }
        }
    }

    return root;
}

// Remove maximum
node* pop(node *root){
    if(root==NULL){
        printf("Priority Queue is empty\n");
        return NULL;
    }

    node *maxNode=maximum(root);
    node *parent=maxNode->parent;
    int color=maxNode->color;

    printf("Removing %d\n",maxNode->key);

    if(maxNode->left!=NULL){
        root=maxNode->left;

        if(parent==NULL)
            root->parent=NULL;
        else{
            parent->right=root;
            root->parent=parent;
        }

        root->color=BLACK;
        free(maxNode);
        return root;
    }

    if(parent==NULL){
        free(maxNode);
        return NULL;
    }

    if(parent->right==maxNode)
        parent->right=NULL;
    else
        parent->left=NULL;

    free(maxNode);

    if(color==BLACK)
        root=fixDelete(root,NULL,parent);

    root->color=BLACK;
    root->parent=NULL;

    return root;
}

// Free tree
void freeTree(node *root){
    if(root==NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Menu
int main(){
    node *root=NULL;
    int choice,key;

    while(1){
        printf("\n1. Insert\n");
        printf("2. Top\n");
        printf("3. Pop\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter priority: ");
                scanf("%d",&key);
                root=insertNode(root,key);
                printf("%d inserted\n",key);
                break;

            case 2:
                top(root);
                break;

            case 3:
                root=pop(root);
                break;

            case 4:
                if(root==NULL)
                    printf("Priority Queue is empty\n");
                else{
                    printf("Priority Queue: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 5:
                freeTree(root);
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}