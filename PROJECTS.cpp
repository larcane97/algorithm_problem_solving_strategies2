#include <iostream>
#include <vector>
#include <cstring>
#include <numeric>
#include <queue>
using namespace std;

const int INF = 987654321;
const int MAX_V = 202;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V], requires[MAX_V][MAX_V];
int profit[200], cost[200];
int n, m;
int V;

int networkFlow(int src, int snk);

int maxProfit() {
	const int SRC = 0, SNK = 1;
	V = n + m + 2;
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));
	for (int i = 0; i < n; i++)
		capacity[SRC][2 + i] = profit[i];
	for (int i = 0; i < m; i++)
		capacity[2 + n + i][SNK] = cost[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (requires[i][j])
				capacity[2 + i][2 + n + j] = INF;
	int M = accumulate(profit, profit + n, 0);
	int C = networkFlow(SRC, SNK);
	return M - C;
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			cin >> profit[i];
		for (int i = 0; i < m; i++)
			cin >> cost[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> requires[i][j];
		cout << maxProfit() << "\n";
	}
}


int networkFlow(int src, int snk) {
	int totalflow = 0;
	while (true) {
		vector<int> parent(V, -1);
		queue<int>q;
		parent[src] = src;
		q.push(src);

		while (!q.empty()) {
			int here = q.front();
			q.pop();

			for (int there = 0; there < V; there++) {
				if (capacity[here][there] - flow[here][there] > 0 &&
					parent[there] == -1) {
					parent[there] = here;
					q.push(there);
				}
			}
		}

		if (parent[snk] == -1) break;

		int amount = INF;
		for (int p = snk; p != src; p = parent[p])
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

		for (int p = snk; p != src; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalflow += amount;
	}
	return totalflow;
}