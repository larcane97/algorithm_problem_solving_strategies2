#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;


int simple(const vector<int>& signals,int k) {
	int ret = 0;
	for (int head = 0; head < signals.size(); head++) {
		int sum = 0;
		for (int tail = head; tail < signals.size(); tail++) {
			sum += signals[tail];
			if (sum == k) ret++;
			if (sum >= k) break;
		}
	}
	return ret;
}

int optimized(const vector<int>& signals, int k) {
	int ret = 0, tail = 0, rangeSum = signals[0];
	for (int head = 0; signals.size(); head++) {
		while (rangeSum < k && tail + 1 < signals.size())
			rangeSum += signals[tail];

		if (rangeSum == k) ret++;

		rangeSum -= signals[head];
	}
	return ret;
}


struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};

int countRanges(int k, int n) {
	RNG rng;
	queue<int> range;
	int ret = 0, rangeSum = 0;
	for (int i = 0; i < n; i++) {
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);

		while (rangeSum > k) {
			rangeSum -= range.front();
			range.pop();
		}
		if (rangeSum == k) ret++;
	}
	return ret;
}


int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n, k;
		cin >> k >> n;
		cout << countRanges(k, n) << endl;
	}

}