#include <iostream>
#include "cstring"

struct Node {
    char* data;
    Node* left;
    Node* right;
};

struct var {
    char name;
    float value;
};

int priority(char* data) {
    if (strcmp(data, "+") == 0) {
        return 2;
    }
    else if (strcmp(data, "-") == 0) {
        return 2;
    }
    else if (strcmp(data, "*") == 0) {
        return 1;
    }
    else if (strcmp(data, "/") == 0) {
        return 1;
    }
    else return 3;
}

int cntLen(float x) {
    int cnt = 0;
    while (x != 0) {
        cnt++;
        x /= 10;
    }
    return cnt;
}

void addNode(Node** Tree, Node* cur) {
    if (*Tree == NULL) {
        (*Tree) = cur;
    }
    else {
        if (priority(cur->data) >= priority((*Tree)->data)) {
            addNode(&(*Tree)->left, cur);
        }
        else {
            addNode(&(*Tree)->right, cur);
        }
    }
}

bool inBrackets(char* sent, int len) {
    bool result = false;
    if (sent[0] == '(') {
        result = true;
        int brackets = 1;
        for (int i = 1; (i < len - 2) && result; i++) {
            if (sent[i] == '(') {
                brackets++;
            }
            else if (sent[i] == ')') {
                brackets--;
            }
            if (brackets == 0) {
                result = false;
            }
        }
    }
    return result;
}

int findOperation(char* sent, int first, int last) {
    int max_pr = -1;
    int oper_id = -1;
    int brackets = 0;
    for (int i = first; i < last + 1; ++i) {
        if (sent[i] == '(') {
            brackets++;
        }
        else if (sent[i] == ')') {
            brackets--;
        }
        if (brackets == 0) {
            char tmp[2];
            tmp[0] = sent[i];
            tmp[1] = '\0';
            if (priority(tmp) >= max_pr && priority(tmp) < 3) {
                max_pr = priority(tmp);
                oper_id = i;
            }
        }
    }
    return oper_id;
}

void makeTree(Node** Tree, char* sent, int first, int last) {
    int oper_id;
    while (inBrackets(sent + first, last - first + 1)) {
        first++;
        last--;
    }
    oper_id = findOperation(sent, first, last);
    if (oper_id != -1) {
        Node* cur = new Node;
        cur->data = new char[2];
        cur->data[0] = sent[oper_id];
        cur->data[1] = '\0';
        cur->left = NULL;
        cur->right = NULL;
        addNode(Tree, cur);
        makeTree(&(*Tree)->left, sent, first, oper_id - 1);
        makeTree(&(*Tree)->right, sent, oper_id + 1, last);
    }
    else {
        Node* cur = new Node;
        cur->data = new char[last - first + 1];
        strncpy(cur->data, sent + first, last - first + 1);
        cur->data[last - first + 1] = '\0';
        cur->left = NULL;
        cur->right = NULL;
        addNode(Tree, cur);
    }
}

double calcNode(Node** Tree, char* num1, char* num2) {
    double tmp1 = atof(num1);
    double tmp2 = atof(num2);
    if (strcmp((*Tree)->data, "+") == 0) {
        return tmp1 + tmp2;
    }
    else if (strcmp((*Tree)->data, "-") == 0) {
        return tmp1 - tmp2;
    }
    else if (strcmp((*Tree)->data, "*") == 0) {
        return tmp1 * tmp2;
    }
    else if (strcmp((*Tree)->data, "/") == 0) {
        if (tmp2 == 0) {
            puts("ERROR: Division by zero!");
            puts("Result of the division was changed to 0!");
            return NULL;
        }
        return tmp1 / tmp2;
    }
    else return NULL;
}

void replaceVar(Node** Tree, char* data) {
    if ((*Tree)->left != NULL) {
        replaceVar(&(*Tree)->left, data);
    }
    if ((*Tree)->right != NULL) {
        replaceVar(&(*Tree)->right, data);
    }
    if (strcmp(data, (*Tree)->data) == 0) {
        double tmp;
        printf("Enter %s:\n", data);
        scanf("%lf", &tmp);
        int len = snprintf(NULL, 0, "%f", tmp);
        delete (*Tree)->data;
        (*Tree)->data = new char[len + 1];
        snprintf((*Tree)->data, len + 1, "%f", tmp);
    }
}

double calcTree(Node** Tree) {
    if (strchr("1234567890+-/*", (*Tree)->data[0]) == 0) {
        replaceVar(Tree, (*Tree)->data);
    }
    if ((*Tree)->left != NULL) {
        calcTree(&(*Tree)->left);
    }
    if ((*Tree)->right != NULL) {
        calcTree(&(*Tree)->right);
    }
    if ((*Tree)->left != NULL && (*Tree)->right != NULL) {
        if (priority((*Tree)->left->data) == 3 && priority((*Tree)->left->data) == 3) {
            double num = calcNode(Tree, (*Tree)->left->data, (*Tree)->right->data);
            delete (*Tree)->data;
            int len = snprintf(NULL, 0, "%f", num);
            (*Tree)->data = new char[len + 1];
            snprintf((*Tree)->data, len + 1, "%f", num);
            (*Tree)->left = NULL;
            (*Tree)->right = NULL;
        }
    }
    return atof((*Tree)->data);
}

void PreOrder_BinaryTree(Node* MyTree) {
    if (MyTree != NULL) {
        printf("%s ", MyTree->data);
        PreOrder_BinaryTree(MyTree->left);
        PreOrder_BinaryTree(MyTree->right);
    }
}

void SymmetricOrder_BinaryTree(Node* MyTree) {
    if (MyTree != NULL) {
        SymmetricOrder_BinaryTree(MyTree->left);
        printf("%s ", MyTree->data);
        SymmetricOrder_BinaryTree(MyTree->right);
    }
}
void PostOrder_BinaryTree(Node* MyTree) {
    if (MyTree != NULL) {
        PostOrder_BinaryTree(MyTree->left);
        PostOrder_BinaryTree(MyTree->right);
        printf("%s ", MyTree->data);
    }
}

int main() {
    char sent[20];
    puts("Enter the expression:");
    gets(sent);
    Node* Tree = NULL;
    makeTree(&Tree, sent, 0, strlen(sent) - 1);
    puts("Pre Order:");
    PreOrder_BinaryTree(Tree);
    puts("");
    puts("Symmetric Order:");
    SymmetricOrder_BinaryTree(Tree);
    puts("");
    puts("Post Order:");
    PostOrder_BinaryTree(Tree);
    puts("");
    double ans = calcTree(&Tree);
    printf("Answer is %lf", ans);
    return 0;
}