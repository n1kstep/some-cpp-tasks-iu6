#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdlib.h"


struct Node {
	char value[80];
	Node* left;
	Node* right;
};


void AddNode(Node** MyTree, Node* TreeElement)
{
	Node* current;
	current = *MyTree;
	if (current == NULL) *MyTree = TreeElement;
	else
	{
		if (strlen(TreeElement->value) < strlen(current->value))
			AddNode(&current->left, TreeElement);
		else if (strlen(TreeElement->value) == strlen(current->value))
			if (strcmp(TreeElement->value, current->value) < 0)
				AddNode(&current->left, TreeElement);
			else
				AddNode(&current->right, TreeElement);
		else
			AddNode(&current->right, TreeElement);
	}
}


int SizeofNodeTree(Node* myTree) {
	if (myTree == NULL)
		return 0;
	else
		return (SizeofNodeTree(myTree->left) + 1 + SizeofNodeTree(myTree->right));
}


int countDepth(Node* MyTree)
{
	if (MyTree == NULL)
		return 0;
	else
	{
		int lchild = countDepth(MyTree->left);
		int rchild = countDepth(MyTree->right);
		if (lchild <= rchild)
			return rchild + 1;
		else
			return lchild + 1;
	}
}


void PreOrder_BinaryTree(Node* MyTree) {
	if (MyTree != NULL) {
		printf("(%s, %d) ", MyTree->value, strlen(MyTree->value));
		PreOrder_BinaryTree(MyTree->left);
		PreOrder_BinaryTree(MyTree->right);
	}
}


void SymmetricOrder_BinaryTree(Node* MyTree) {
	if (MyTree != NULL) {
		SymmetricOrder_BinaryTree(MyTree->left);
		printf("(%s, %d) ", MyTree->value, strlen(MyTree->value));
		SymmetricOrder_BinaryTree(MyTree->right);
	}
}


void PostOrder_BinaryTree(Node* MyTree) {
	if (MyTree != NULL) {
		PostOrder_BinaryTree(MyTree->left);
		PostOrder_BinaryTree(MyTree->right);
		printf("(%s, %d) ", MyTree->value, strlen(MyTree->value));
	}
}


void Del1(Node** r, Node** q)
{
	Node* s;
	if ((*r)->right == NULL)
	{
		strcpy((*q)->value, (*r)->value);
		*q = *r;
		s = *r;
		*r = (*r)->left;
		delete s;
	}
	else
		Del1(&((*r)->right), q);
}


void Del_Node(Node** MyTree, char k[80])
{
	Node* current, * q;
	current = *MyTree;
	if (*MyTree == NULL)
		printf("\nУзел дерева с заданным значением не найден!\n");
	else
		if ((strlen(k) < strlen(current->value)) & (strcmp(k, current->value) > 0)) 
			Del_Node(&current->left, k);
		else
			if ((strlen(k) > strlen(current->value)) & (strcmp(k, current->value) < 0)) 
				Del_Node(&current->right, k);
			else 
			{
				q = *MyTree;
				if (q->right == NULL) 
				{ 
					*MyTree = q->left;
					delete q; 
				}
				else
					if (q->left == NULL) 
					{ 
						*MyTree = q->right;
						delete q; 
					}
					else
						Del1(&q->left, &q);			
			}
}


void DeleteFromBinaryTree(Node*& MyTree, int limit)
{
	if (MyTree != NULL) 
	{
		DeleteFromBinaryTree(MyTree->left, limit);
		DeleteFromBinaryTree(MyTree->right, limit);
		if ((strlen(MyTree->value) > limit) & ((MyTree->value[0] == 's') | (MyTree->value[0] == 'n')))
		{
			printf("\nУдаление слова %s.", MyTree->value);
			Del_Node(&MyTree, MyTree->value);
		}
	}
}


void Del_Mem(Node** MyTree)
{
	Node* current;
	current = *MyTree;
	if (*MyTree != NULL) 
	{
		Del_Mem(&(*MyTree)->left);
		Del_Mem(&(*MyTree)->right);
		delete* MyTree;
	}
}


void print_tree(Node* MyTree, int space) {
	if (MyTree == NULL) {
		return;
	}
	space += 8;
	print_tree(MyTree->right, space);
	printf("\n");
	for (int i = 8; i < space; i++) {
		printf(" ");
	}
	printf("(%s, %d)\n", MyTree->value, strlen(MyTree->value));
	print_tree(MyTree->left, space);
}


int main(int argc, char* argv[])
{
	Node* MyTree = NULL;
	Node* TreeElement;
	char word[80];
	int limit, n, cnt, depth;
	bool flag = false;
	setlocale(0, "russian");
	puts("Введите число. Слова с большим размером и начинающиеся на n- или s- будут удалены.");
	scanf("%d", &limit);
	getchar();
	puts("Вводите слова по одному. Для окончания ввода введите пустую строку.");
	while (strlen(gets_s(word)) != 0)
	{
		TreeElement = new Node;
		strcpy(TreeElement->value, word);
		TreeElement->left = NULL;
		TreeElement->right = NULL;
		AddNode(&MyTree, TreeElement);
	}
	puts("Построенное двоичное дерево:");
	print_tree(MyTree, 3);
	puts("\nПрямой обход:");
	SymmetricOrder_BinaryTree(MyTree);
	puts("\nСимметричный обход:");
	PostOrder_BinaryTree(MyTree);
	puts("\nОбратный обход:");
	PreOrder_BinaryTree(MyTree);
	puts("");

	cnt = SizeofNodeTree(MyTree);
	printf("\nКоличество узлов в дереве: %d", cnt);
	depth = countDepth(MyTree);
	printf("\nГлубина дерева: %d", depth);

	DeleteFromBinaryTree(MyTree, limit);

	puts("\nИзмененное двоичное дерево:");
	print_tree(MyTree, 3);
	puts("\nПрямой обход:");
	SymmetricOrder_BinaryTree(MyTree);
	puts("\nСимметричный обход:");
	PostOrder_BinaryTree(MyTree);
	puts("\nОбратный обход:");
	PreOrder_BinaryTree(MyTree);
	puts("");

	cnt = SizeofNodeTree(MyTree);
	printf("\nКоличество узлов в дереве: %d", cnt);
	depth = countDepth(MyTree);
	printf("\nГлубина дерева: %d", depth);

	puts("\nВведите слова по одному, чтобы вставить их в двоичное дерево.");
	puts("Введите пустую строку, чтобы завершить работу программы:");
	while (strlen(gets_s(word)) != 0)
	{
		TreeElement = new Node;
		strcpy(TreeElement->value, word);
		TreeElement->left = NULL;
		TreeElement->right = NULL;
		AddNode(&MyTree, TreeElement);
		flag = true;
	}
	if (flag)
	{
		puts("Дополненное двоичное дерево:");
		print_tree(MyTree, 3);
		puts("\nПрямой обход:");
		SymmetricOrder_BinaryTree(MyTree);
		puts("\nСимметричный обход:");
		PostOrder_BinaryTree(MyTree);
		puts("\nОбратный обход:");
		PreOrder_BinaryTree(MyTree);
		puts("");

		cnt = SizeofNodeTree(MyTree);
		printf("\nКоличество узлов в дереве: %d", cnt);
		depth = countDepth(MyTree);
		printf("\nГлубина дерева: %d", depth);

		DeleteFromBinaryTree(MyTree, limit);

		puts("\nИзмененное двоичное дерево:");
		print_tree(MyTree, 1);
		puts("\nПрямой обход:");
		SymmetricOrder_BinaryTree(MyTree);
		puts("\nСимметричный обход:");
		PostOrder_BinaryTree(MyTree);
		puts("\nОбратный обход:");
		PreOrder_BinaryTree(MyTree);
		puts("");

		cnt = SizeofNodeTree(MyTree);
		printf("\nКоличество узлов в дереве: %d", cnt);
		depth = countDepth(MyTree);
		printf("\nГлубина дерева: %d", depth);
	}
	Del_Mem(&MyTree);
	return 0;
}