#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int height;
    struct node *left;
    struct node *right;
} node;

/* Return height of node */
int height(node *n) {
    return (n == NULL) ? 0 : n->height;
}

/* Return maximum of two values */
int max(int a, int b) {
    return (a >= b) ? a : b;
}

/* Calculate balance factor */
int balanceFactor(node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

/* Create a new node */
node* createNode(int val) {
    node *newNode = (node*)malloc(sizeof(node));

    newNode->val = val;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* LL case: Right rotation */
node* LL(node *x) {
    if (x == NULL)
        return x;

    node *y = x->left;

    x->left = y->right;
    y->right = x;

    /* Update heights */
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/* RR case: Left rotation */
node* RR(node *x) {
    if (x == NULL)
        return x;

    node *y = x->right;

    x->right = y->left;
    y->left = x;

    /* Update heights */
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/* LR case: Left rotation + Right rotation */
node* LR(node *x) {
    if (x == NULL)
        return x;

    x->left = RR(x->left);
    return LL(x);
}

/* RL case: Right rotation + Left rotation */
node* RL(node *x) {
    if (x == NULL)
        return x;

    x->right = LL(x->right);
    return RR(x);
}

/* Search a value */
node* search(node *root, int val) {
    if (root == NULL || root->val == val)
        return root;

    if (root->val < val)
        return search(root->right, val);
    else
        return search(root->left, val);
}

/* Inorder traversal */
void inorder(node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d\t", root->val);
    inorder(root->right);
}

/* AVL insertion */
node* insertion(node *root, int val) {

    /* Do not insert duplicate */
    if (root != NULL && root->val == val)
        return root;

    /* Insert new node */
    if (root == NULL)
        return createNode(val);

    if (root->val < val)
        root->right = insertion(root->right, val);
    else
        root->left = insertion(root->left, val);

    /* Update height */
    root->height = 1 + max(height(root->left), height(root->right));

    int bal_f = balanceFactor(root);

    /* LR case */
    if (bal_f > 1 && val > root->left->val)
        return LR(root);

    /* LL case */
    if (bal_f > 1 && val < root->left->val)
        return LL(root);

    /* RR case */
    if (bal_f < -1 && val > root->right->val)
        return RR(root);

    /* RL case */
    if (bal_f < -1 && val < root->right->val)
        return RL(root);

    return root;
}

/* Find minimum node */
node* minimum(node *root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

/* AVL deletion */
node* deletion(node *root, int val) {

    if (root == NULL)
        return root;

    /* Search for node */
    if (root->val < val)
        root->right = deletion(root->right, val);

    else if (root->val > val)
        root->left = deletion(root->left, val);

    else {
        /* Leaf node */
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        /* Only right child */
        else if (root->left == NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        }

        /* Only left child */
        else if (root->right == NULL) {
            node *temp = root->left;
            free(root);
            return temp;
        }

        /* Two children */
        else {
            node *temp = minimum(root->right);

            /* Copy successor value */
            root->val = temp->val;

            /* Delete successor */
            root->right = deletion(root->right, temp->val);
        }
    }

    /* Update height */
    root->height = 1 + max(height(root->left), height(root->right));

    int bal_f = balanceFactor(root);

    /* Left heavy */
    if (bal_f > 1) {

        if (balanceFactor(root->left) >= 0)
            return LL(root);       /* LL */

        else
            return LR(root);       /* LR */
    }

    /* Right heavy */
    if (bal_f < -1) {

        if (balanceFactor(root->right) <= 0)
            return RR(root);       /* RR */

        else
            return RL(root);       /* RL */
    }

    return root;
}

/* Main menu */
int main() {

    node *root = NULL;
    int choice, val;

    while (1) {

        printf("\n\n--- AVL TREE ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value: ");
                scanf("%d", &val);

                root = insertion(root, val);

                printf("Value inserted.");
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &val);

                if (search(root, val) == NULL) {
                    printf("Value not found.");
                } else {
                    root = deletion(root, val);
                    printf("Value deleted.");
                }
                break;

            case 3:
                printf("Enter value: ");
                scanf("%d", &val);

                if (search(root, val) != NULL)
                    printf("Value found.");
                else
                    printf("Value not found.");

                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice.");
        }
    }

    return 0;
}