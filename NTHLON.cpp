#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int V;
vector<pair<int, int>>adj[410];
const int START = 401;
const int INF = 987654321;

int vertex(int delta) {
	return delta + 200;
}

vector<int> dijkstra() {
	vector<int> dist(V, INF);
	dist[START] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push(make_pair(0, START));
	while (!pq.empty()) {
		int here = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int next = adj[here][i].second + cost;

			if (dist[there] > next) {
				pq.push(make_pair(-next, there));
				dist[there] = next;
			}
		}
	}
	return dist;
}

int solve(const vector<int>& a, const vector<int>& b) {
	V = 402;
	for (int i = 0; i < V; i++) adj[i].clear();
	for (int i = 0; i < a.size(); i++) {
		int delta = a[i] - b[i];
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}
	for (int delta = -200; delta <= 200; delta++) {
		for (int i = 0; i < a.size(); i++) {
			int next = delta + a[i] - b[i];
			if (abs(next) > 200) continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra();
	int ret = shortest[vertex(0)];
	if (ret == INF) return -1;
	return ret;
}


void input(vector<int>&A,vector<int>&B) {
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		A.push_back(a);
		B.push_back(b);
	}
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		vector<int>A,B;
		input(A,B);
		int ret = solve(A, B);
		if (ret == -1) cout << "IMPOSSIBLE" << endl;
		else cout << ret << endl;
	}
}