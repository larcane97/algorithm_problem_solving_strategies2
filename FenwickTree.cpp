#include <vector>

using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) :tree(n + 1) {};

	int sum(int pos) {
		// 2���� ������ ���ؼ� ���������� �ε����� 1���� ����
		pos++;

		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			// ���� Ʈ�� : ���� ���� 2���� ��Ʈ���� ���� ��Ʈ�� ���� �ε���
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