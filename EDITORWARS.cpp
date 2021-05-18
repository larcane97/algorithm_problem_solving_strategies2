#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct DisjointSet {
	vector<int> parent;
	vector<int>rank;
	vector<int>size;
	int maxSize;

	DisjointSet(int n) : maxSize(n),parent(n),rank(n,1), size(n, 1){
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	// flag 0 : DIS
	// flag 1 : ACK
	bool merge(int u, int v,int flag) {
		u = find(u), v = find(v);

		if (flag == 0) {
			if (u == v) return false;
			else {
				maxSize = max(maxSize - size[u], maxSize - size[v]);
				return true;
			}
		}
		if (u == v) 
			return true;
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v])
			rank[v]++;
		size[v] += size[u];
		maxSize = max(maxSize, size[v]);
		return true;
	}

};



int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n, m;
		int chk = -1;
		cin >> n >> m;
		DisjointSet ds = DisjointSet(n);
		for (int i = 0; i < m; i++) {
			int a, b,flag;
			string comment;
			cin >> comment >> a >> b;
			flag = comment == "ACK" ? 1 : 0;

			if (!ds.merge(a, b, flag))
				chk = i + 1;
		}
		if (chk == -1)
			cout << "MAX PARTY SIZE IS " + to_string(ds.maxSize) << endl;
		else
			cout << "CONTRADICTION AT " + to_string(chk) << endl;


	}
}