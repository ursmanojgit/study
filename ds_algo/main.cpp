#include <stdio.h>
#include <iostream>
using namespace std;

#define TEST_FUNC_NAME main_segmintreelazy

#define DECLARE_TESTMAIN extern int TEST_FUNC_NAME()

int main() {
	DECLARE_TESTMAIN;

	TEST_FUNC_NAME();
	return 0;
}
