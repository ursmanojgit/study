#include <stdio.h>
#include <iostream>
using namespace std;

struct node {
	node *br[26];
	bool isWord;
	node() {
		for (int i = 0; i < 26; i++) {
			br[i] = 0;
		}
		isWord = 0;
	}
	~node() {
		for (int i = 0; i < 26; i++) {
			if (br[i])
				delete br[i];
		}
	}
};

static void insert(char *str, node *cur) {
	char* p = str;
	while (*p) {
		int i = *p - 'a';

		if (cur->br[i] == 0)
			cur->br[i] = new node;
		cur = cur->br[i];
		p++;
	}
	cur->isWord = 1;
}


static bool search(char *str, node *cur) {
	char *p = str;

	while (*p) {
		int i = *p - 'a';

		if (cur->br[i] == 0)
			return false;
		cur = cur->br[i];
		p++;
	}
	return cur->isWord;
}

static char pWord[50];
static void printTrie(char *str, node *n) {
	if (n->isWord) {
		*str = 0;
		cout << pWord << endl;
	}

	for (int i = 0; i < 26; i++) {
		if (n->br[i]) {
			*str = 'a' + i;
			printTrie(str + 1, n->br[i]);
		}
	}
}

static void testSearch(node * root, char * word) {
	if (search(word, root))
		cout << "word=" << word << " is FOUND" << endl;
	else
		cout << "word=" << word << " is NOT FOUND" << endl;
}

int main_trie_loop() {
	node * root = new node;

	insert("m", root);

	insert("manoj", root);
	insert("man", root);
	insert("amit", root);
	insert("amitabh", root);
	insert("mahesh", root);

	printTrie(pWord, root);
	testSearch(root, "mano");
	testSearch(root, "manoj");
	testSearch(root, "m");
	testSearch(root, "amit");
	testSearch(root, "amita");
	testSearch(root, "mahesha");

	delete root;
}