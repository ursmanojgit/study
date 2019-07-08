#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct Node {
	int key;
	Node* left, * right;
	Node(int k) {
		key = k;
		left = 0;
		right = 0;
	}
};

Node* newNode(int item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

Node* current;

Node* addRec(Node* node, int key) {
	if (node == NULL)
		return newNode(key);

	if (key < node->key)
		node->left = addRec(node->left, key);
	else if (key > node->key)
		node->right = addRec(node->right, key);

	return node;
}

void add(int key) {
	current = addRec(current, key);
}

bool findRec(Node* node, int key) {
	if (node != NULL) {
		if (key == node->key)
			return true;
		if (findRec(node->left, key))
			return true;
		if (findRec(node->right, key))
			return true;
	}

	return false;
}

bool contains(int key) {
	return findRec(current, key);
}

void printAll(Node* node) {
	if (node != NULL) {
		printAll(node->left);
		printf("%d ", node->key);
		printAll(node->right);
	}
}

void printAll() {
	printAll(current);
}

Node* minValueNode(Node* node) {
	Node* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

Node* removeRec(Node* node, int key) {
	if (node == NULL)
		return node;

	if (key < node->key)
		node->left = removeRec(node->left, key);
	else if (key > node->key)
		node->right = removeRec(node->right, key);
	else {
		if (node->left == NULL) {
			Node* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			Node* temp = node->left;
			free(node);
			return temp;
		}

		Node* temp = minValueNode(node->right);
		node->key = temp->key;
		node->right = removeRec(node->right, temp->key);
	}

	return node;
}

void remove(int key) {
	current = removeRec(current, key);
}

void printDlist();
void  convertToDList();

int bigTree(void) {
	int data[] = {100, 2,4,1,12, 89, 23 , 45,99 };

	int N;

	
	current = NULL;

	N = sizeof(data) / (sizeof(int));

	for (int i = 0; i < N; ++i) {

		int key;

		key = data[i];

		add(key);			
	}

	
	printAll();
	printf("\n\n Converting to Dllist");

	convertToDList();
	printDlist();

	return 0;
}


void printDlist() {
	printf("\n Converted Linked list.....\n\n");
	Node* t = current;
	while (t) {
		printf("%d ", t->key);
		t = t->right;
	}
}

void makeList(Node* root, Node** pTail) {
	Node* tail = *pTail;

	if (root == 0)
		return;

	//leaf node
	if (root->left == 0 && root->right == 0) {
		//Detach this node from Tree and attach to tail, adjust prev, next pointers accordingly
		tail->right = root;
		root->left = tail;
		*pTail = (*pTail)->right;
		return;
	}


	//Non leaf: do in-order processing
	makeList(root->left, pTail);
	//Detach this node from Tree and attach to tail, adjust prev, next pointers accordingly
	tail = *pTail;
	tail->right = root;
	root->left = tail;
	*pTail = (*pTail)->right;
	// recursive process on right subtree
	makeList(root->right, pTail);
}


void convertToDList() {
	Node head(0);
	Node* tail = &head;

	makeList(current, &tail);
	if (head.right != 0)
		head.right->left = 0;
	current = head.right;
}


