#include <vector>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;

int V;
vector<pair<int, int>> adj[MAX_V];

// 1. root���� ������ �߰�
// 2. �� �������� ���� ��带 Ž���ϸ鼭 ���� ����� weight���� �ּ��� �θ���� ���� ����
// 3. V�� Ž���ϸ鼭 �߰����� ���� ���� �� �ּ� weight�� ���� �� ���� �߰�
int prim(vector<pair<int, int>>& selected) {
	selected.clear();
	vector<bool> added(V, false);

	vector<int> minWeight(V, INF);
	vector<int>parent(V, -1);
	
	int ret = 0;

	minWeight[0] = parent[0] = 0;
	for (int iter = 0; iter < V; iter++) {
		int u = -1;

		// �߰����� ���� ���� �� �߰��� edge�� weight���� ���� ���� ������ ����
		// �߰��� ������ edge�� �����ϸ� cycle�� �߻��ϹǷ�
		for (int v = 0; v < V; v++) 
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
				u = v;
		// ���� ó��(root)�� edge�� �ƴϹǷ� �߰� X
		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;

		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			int weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
			}
		}
	}
	return ret;
}
