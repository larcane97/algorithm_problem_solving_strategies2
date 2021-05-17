#include <iostream>
#include <vector>
#include "FenwickTree.cpp"

using namespace std;


long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); i++) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
}
