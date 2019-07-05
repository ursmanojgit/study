#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

using namespace std::chrono;



long long countBSTs(int n) {
	if (n <= 1)
		return 1;
	long long sum = 0;
	for (int i = 1; i <= n; i++) {

		long long rn = countBSTs(n - i);
		//int ln = countBSTs(n - (n - i) - 1));
		long long ln = countBSTs(i - 1);

		sum += rn * ln;
	}
	return sum;
}

long long dp[500];

long long countBSTsDP(int n) {
	if (n <= 1)
		return 1;
	long long sum = 0;
	for (int i = 1; i <= n; i++) {


		if (dp[n - i] == 0)
			dp[n - i] = countBSTs(n - i);
		long long rn = dp[n - i];

		if (dp[i - 1] == 0)
			dp[i - 1] = countBSTs(i - 1);

		long long ln = dp[i - 1];

		sum += rn * ln;
	}
	return sum;
}

long long pureDP[200];



void initPureDP(int N) {
	pureDP[0] = pureDP[1] = 1;
	pureDP[2] = 2;


	for (int n = 3; n <= N; n++) {
		long long sum = 0;
		for (int i = 1; i <= n; i++) {
			sum += pureDP[n - i] * pureDP[i - 1];
		}
		pureDP[n] = sum;
		cout << "PureDP Thread: pureDP[" << n << "]: " << pureDP[n] << endl;
	}
}

int main(void) {

	//std::thread pureDPThread(initPureDP, 100);

	initPureDP(35);

	for (int n = 15; n <= 50; n++) {
		// TODO: reset dp array
		cout << "n=" << n << endl;
		cout<<"Pure DP: "<<pureDP[n]<<endl;


		cout << "DP started.." << endl;
		milliseconds ms1 = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		cout << countBSTsDP(n) << endl;
		milliseconds ms2 = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		int diff = (ms2 - ms1).count();
		cout << "time in ms: " << diff << endl << endl;

		cout << "Recursive started.." << endl;
		ms1 = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		cout << countBSTs(n) << endl;
		ms2 = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		diff = (ms2 - ms1).count();
		cout << "time in ms: " << diff << endl << endl;

		cout << endl << endl;
	}

	//pureDPThread.join();

	return 0;
}