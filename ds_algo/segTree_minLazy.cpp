#include <stdio.h>
#include <iostream>
using namespace std;

#define MIN(a,b)	((a)<(b)?(a):(b))

static int st[64];
static int lazy[64];
static int a[] = { 45,16,88,4,12,10,55,37 };

static void constructST(int ri, int b, int e) {
	if (b == e) {
		st[ri] = a[b];
		return;
	}
	int mid = b + (e - b) / 2;
	constructST(2 * ri + 1, b, mid);
	constructST(2 * ri + 2, mid + 1, e);

	st[ri] = MIN(st[2 * ri + 1], st[2 * ri + 2]);
}

static void passToChildren(int ri, int b, int e) {
	if (lazy[ri] == 0)
		return;
	
	if (b != e) {
		lazy[2 * ri + 1] += lazy[ri];
		lazy[2 * ri + 2] += lazy[ri];
	}
	st[ri] += lazy[ri];
	lazy[ri] = 0;
}

#define OUT_OF_RANGE(b,e,rb,re) (rb>e||re<b)
#define FULL_OVERLAP(b,e,rb,re) (rb<=b&&re>=e)
#define BIG_NUM 32500

static int findMin(int ri, int b, int e, int rb, int re) {
	passToChildren(ri, b, e);

	if (OUT_OF_RANGE(b, e, rb, re))
		return BIG_NUM;

	if (FULL_OVERLAP(b, e, rb, re))
		return st[ri];

	//partial overlap, check both subtrees
	int mid = b + (e - b) / 2;
	int m1 = findMin(2 * ri + 1, b, mid, rb, re);
	int m2 = findMin(2 * ri + 2, mid + 1, e, rb, re);

	return MIN(m1, m2);
}

static void updateST(int ri, int b, int e, int rb, int re, int num) {
	passToChildren(ri, b, e);

	if (OUT_OF_RANGE(b, e, rb, re))
		return;

	if (FULL_OVERLAP(b, e, rb, re)) {
		st[ri] += num;
		if (b != e) {
			lazy[2 * ri + 1] += num;
			lazy[2 * ri + 2] += num;
		}
		return;
	}
	//partial ovlap
	int mid = b + (e - b) / 2;
	updateST(2 * ri + 1, b, mid, rb, re, num);
	updateST(2 * ri + 2, mid + 1, e, rb, re, num);
	st[ri] = MIN(st[2 * ri + 1], st[2 * ri + 2]);
}

static void testMinFind(int rb, int re) {
	int m = findMin(0, 0, sizeof(a) / sizeof(a[0]) - 1, rb, re);

	cout << " Range ( ";
	for (int i = rb; i <= re; i++)
		cout << a[i] << " ";
	cout << " )'s Min: " << m << endl;
}

static void testUpdate(int rb, int re, int num) {
	for (int i = rb; i <= re; i++) {
		a[i] += num;
	}
	updateST(0, 0, sizeof(a) / sizeof(a[0]) - 1, rb, re, num);
}

int main_segmintreelazy() {
	constructST(0, 0, sizeof(a) / sizeof(a[0]) - 1);


	testUpdate(3, 5, 16);
	testUpdate(1, 5, 4);


	testMinFind(2, 7);
	testMinFind(0, 7);
	testMinFind(0, 3);
	testMinFind(3, 4);
	testMinFind(5, 7);

	return 0;
}