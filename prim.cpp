#include <vector>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;

int V;
vector<pair<int, int>> adj[MAX_V];

// 1. root부터 정점을 추가
// 2. 각 정점마다 인접 노드를 탐색하면서 인접 노드의 weight값이 최소인 부모노드와 값을 저장
// 3. V번 탐색하면서 추가되지 않은 정점 중 최소 weight를 선택 후 정점 추가
int prim(vector<pair<int, int>>& selected) {
	selected.clear();
	vector<bool> added(V, false);

	vector<int> minWeight(V, INF);
	vector<int>parent(V, -1);
	
	int ret = 0;

	minWeight[0] = parent[0] = 0;
	for (int iter = 0; iter < V; iter++) {
		int u = -1;

		// 추가되지 않은 정점 중 추가된 edge의 weight값이 가장 작은 정점을 선택
		// 추가된 정점의 edge를 선택하면 cycle이 발생하므로
		for (int v = 0; v < V; v++) 
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
				u = v;
		// 가장 처음(root)는 edge가 아니므로 추가 X
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
