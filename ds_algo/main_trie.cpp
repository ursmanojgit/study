#include <iostream>

using namespace std;

////////////////////// NOTE: crash on MS studio 2016, constructor not called perhaps

struct node {
	node *br[26];
	bool isWord;
	void init() {
		/*for (int i = 0; i < 26; i++) {
		br[i] = 0;
		}*/
	}
	node() {
		for (int i = 0; i < 26; i++) {
			br[i] = 0;
		}
	}
	~node() {
		for (int i = 0; i < 26; i++) {
			if (br[i])
				delete br[i];
		}
	}

};

void insert(char * str, node * n) {
	if (*str == 0) {
		n->isWord = 1;
		return;
	}

	int i = *str - 'a';
	if (n->br[i] == 0) {
		n->br[i] = new node;
		n->br[i]->init();
	}

	insert(str + 1, n->br[i]);
}

bool search(char *str, node *n) {
	if (*str == 0)
		return n->isWord;

	int i = *str - 'a';

	if (n->br[i])
		return search(str + 1, n->br[i]);

	return false;
}

static char pWord[50];
void printTrie(char *str, node *n) {
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

int main_trie() {
	node * root = new node();
	root->init();

	insert("m", root);

	insert("manoj", root);
	insert("man", root);
	insert("amit", root);
	insert("amitabh", root);
	insert("mahesh", root);

	//printTrie(pWord, root);
	testSearch(root, "mano");
	testSearch(root, "manoj");
	testSearch(root, "m");
	testSearch(root, "amit");
	testSearch(root, "amita");
	testSearch(root, "mahesha");

	delete root;
	return 0;
}