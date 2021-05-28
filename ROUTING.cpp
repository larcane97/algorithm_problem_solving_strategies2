#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<pair<int, double>>>adj;
int n, k;
vector<double>dist;
double solve() {
	dist = vector<double>(n, 98765321);
	dist[0] = 1;
	
	priority_queue<pair<double, int>>pq;
	pq.push(make_pair(-1, 0));

	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			double nextDist = adj[here][i].second * cost;

			if (nextDist < dist[there]) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist[dist.size() - 1];
}


int main() {
	int t;
	cin >> t;
	for (int iter = 0; iter < t; iter++) {
		adj.clear();
		cin >> n >> k;
		adj = vector<vector<pair<int, double>>>(n);
		for (int i = 0; i < k; i++) {
			int a, b;
			double c;
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
		}
		printf("%.10f\n", solve());
	}
}