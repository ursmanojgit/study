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
	if (*str==0) {
		cur->isWord = 1;
		return;
	}
	int i = *str - 'a';
	if (cur->br[i] == 0)
		cur->br[i] = new node;

	insert(str + 1, cur->br[i]);
}


static bool search(char *str, node *cur) {
	if (cur == 0)
		return false;
	if (*str == 0)
		return cur->isWord;

	int i = *str - 'a';
	return search(str + 1, cur->br[i]);
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

int main_trie_rec2() {
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