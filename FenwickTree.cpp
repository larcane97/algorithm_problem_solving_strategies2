#include <vector>

using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) :tree(n + 1) {};

	int sum(int pos) {
		// 2진수 연산을 위해서 내부적으로 인덱스가 1부터 시작
		pos++;

		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			// 팬윅 트리 : 다음 합은 2진수 비트에서 최종 비트를 지운 인덱스
			pos &= (pos - 1);
		}
		return ret;
	}

	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}

};