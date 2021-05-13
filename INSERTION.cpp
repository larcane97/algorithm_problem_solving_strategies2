#include "Treap.cpp"


int shifted[50000];
int A[50000];
void solve(int n) {
	Node* candidates = NULL;
	for (int i = 0; i < n; i++)
		candidates = insert(candidates, new Node(i + 1));

	for (int i = n - 1; i >= 0; i--) {
		int larger = shifted[i];
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> shifted[i];
		solve(n);
		for (int i = 0; i < n; i++)
			cout << A[i] << " ";
		cout << endl;
	}
}

