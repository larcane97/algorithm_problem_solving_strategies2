#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;



struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) :a(_a), b(_b), seed(1983) {};
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;

		return ret;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>>maxHeap;
	priority_queue<int, vector<int>, greater<int>>minHeap;
	int ret = 0;

	for (int cnt = 1; cnt <= n; cnt++) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());

		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = minHeap.top(), b = maxHeap.top();
			minHeap.pop(); maxHeap.pop();
			minHeap.push(b); maxHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}


int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n, a, b;
		cin >> n >> a >> b;
		cout << runningMedian(n,RNG(a,b))<< endl;
	}


}