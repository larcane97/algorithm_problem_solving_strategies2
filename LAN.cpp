#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DisjointSet {
	vector<int>parent;
	vector<int>rank;

	DisjointSet(int n) :parent(n), rank(n, -1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}


	int find(int u) {
		if (parent[u] == u) return u;
		else return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = parent[u], v = parent[v];
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}

};



const int MAX_V = 500;
vector<pair<int, double>>adj[MAX_V];
int V,E;
double kruskal() {
	double ret = 0;

	vector<pair<double, pair<int, int>>>edges;
	for (int u = 0; u < V; u++) {
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			double cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	}
	sort(edges.begin(), edges.end());

	DisjointSet sets(V);

	for (int i = 0; i < edges.size(); i++) {
		double cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		if (sets.find(u) == sets.find(v)) continue;
		sets.merge(u, v);
		ret += cost;
	}

	return ret;
}

double dis(int x1, int x2, int y1, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void solve() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		for (int i = 0; i < MAX_V; i++)
			adj[i].clear();

		cin >> V >> E;
		vector<int>x(V);
		vector<int>y(V);
		for (int i = 0; i < V; i++)
			cin >> x[i];
		for (int i = 0; i < V; i++)
			cin >> y[i];
		for(int i=0;i<V;i++)
			for (int j = 0; j < V; j++)
				adj[i].push_back(make_pair(j, dis(x[i], x[j], y[i], y[j])));

		for (int i = 0; i < E; i++) {
			int a, b;
			cin >> a >> b;
			adj[a][b].second = 0;
			adj[b][a].second = 0;
		}

		double ret =kruskal();
		cout << ret << "\n";
	}
}

int main() {
	solve();
}