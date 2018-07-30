#include <stdio.h>
#include <stdlib.h>


struct Node {
    int priority;
    struct Node* left;
    struct Node* right;
};

struct Node* root;

struct Node* GetNewNodes(){
    int random;
    random = rand() % 41;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->priority = random;
    newNode->left = NULL;
    newNode->right = NULL;
}

struct Node* rightRot(struct Node* n){
    struct Node* temp = n->left;
    if(n->left != NULL) {
        n->left = temp->right;
    }
    temp->right = n;
    return temp;
}

struct Node* leftRot(struct Node* n){
    struct Node* temp = n->right;
    if(n->right != NULL) {
        n->right = temp->left;
    }
    temp->left = n;
    return temp;
}

struct Node* splay(struct Node*cur, int prio){
    if(cur == NULL || cur->priority == prio){
        return cur;
    }
    //Left side of cur
    if(cur->priority > prio){
        if(cur->left == NULL){
            return cur;
        }
            //If node is left of parent and parent is left of grand-parent, we do a zig-zig right-right rotation.
        else if (cur->left->priority > prio && cur->left->left != NULL){
            cur->left = rightRot(cur->left);
            cur = rightRot(cur);
            //splay(cur, prio);
        }
            //If node is right of parent but parent is left or grand-parent, we do a zig-zag left-right rotation.
        else if (cur->left->priority < prio  && cur->left->right != NULL){
            cur->left = leftRot(cur->left);
            cur = rightRot(cur);
            //splay(cur, prio);
        }
        else{
            cur = rightRot(cur);
        }
    }


        //Right side of cur
    else if(cur->priority < prio){
        if(cur->right == NULL){
            return cur;
        }
            //If node is right of parent and parent is right of grand-parent, we do a zig-zig left-left rotation.
        else if(cur->right->priority < prio  && cur->right->right != NULL){
            cur->right = leftRot(cur->right);
            cur = leftRot(cur);
            //splay(cur, prio);
        }
            //If node is left of parent but parent is right of grand-parent, we do a zig-zag right-left rotation.
        else if(cur->right->priority > prio  && cur->right->left != NULL){
            cur->right = rightRot(cur->right);
            cur = leftRot(cur);
            //splay(cur,prio);
        }
        else{
            cur = leftRot(cur);
        }
    }
    return cur;

}


struct Node* insert(struct Node* cur, struct Node* newNode) {
    if (newNode->priority < cur->priority)
        if(cur->left == NULL){
            cur->left = newNode;
        }
        else {
            cur->left = insert(cur->left, newNode);
        }
    else  // key >= cur->key
    if(cur->right == NULL){
        cur->right = newNode;
    }
    else {
        cur->right = insert(cur->right, newNode);
    }
}


void insertNodesSplaytree(int numOfNodes) {
    for(int i = 0; i< numOfNodes; i++){
        struct Node *newNode = GetNewNodes();
        printf("%d",newNode->priority);
        if(!root){
            root = newNode;
        }
        else {
            insert(root, newNode);
            while (newNode->priority != root->priority) {
                root = splay(root, newNode->priority);
            }
        }
        printTree(root);
    }
}

//Print tree arranged by priorities (Based on: https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console)
void printTree(struct Node *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _printTree(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

int _printTree(struct Node *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "%f", tree->priority);

    int left  = _printTree(tree->left,  1, offset,                depth + 1, s);
    int right = _printTree(tree->right, 0, offset + left + width, depth + 1, s);


    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) { for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}