#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector < vector<pair<int, int>>>adj;
vector<int>fired;
vector<int>stations;
int v, e, n, m;

vector<int> dijkstra() {
	vector<int>dist(v + 1,987654321);
	dist[v] = 0; // 시작점
	priority_queue<pair<int, int>>pq;
	pq.push(make_pair(0, v));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (cost > dist[here]) continue;

		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextCost = cost + adj[here][i].second;

			if (nextCost < dist[there]) {
				dist[there] = nextCost;
				pq.push(make_pair(-nextCost, there));
			}
		}
	}
	return dist;
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		cin >> v >> e >> n >> m;
		v++;
		adj = vector<vector<pair<int, int>>>(v+1);
		for (int i = 0; i < e; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}
		for(int i=0;i<n;i++){
			int a;
			cin >> a;
			fired.push_back(a);
		}

		for (int i = 0; i < m; i++) {
			int a;
			cin >> a;
			stations.push_back(a);
			// 가상의 선
			adj[v].push_back(make_pair(a, 0));
		}
		vector<int>dist = dijkstra();
		int ret = 0;
		for (int i = 0; i < fired.size(); i++) {
			ret += dist[fired[i]];
		}
		cout << ret << endl;
	}
}