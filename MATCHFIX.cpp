#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 987654321;
const int MAX_N = 12;
const int MAX_M = 100;
const int MAX_V = MAX_N + MAX_M;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int V;

int networkFlow(int source, int sink) {
	// 1. °æ·Î Å½»ö(by bfs)
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int>parent(MAX_V, -1);
		queue<int>q;
		q.push(source);
		parent[source] = source;
		while (!q.empty()) {
			int here = q.front();
			q.pop();
			for (int there = 0; there < V; there++) {
				if (capacity[here][there] - flow[here][there] > 0
					&& parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		
		if (parent[sink] == -1) break;

		int amount = INF;
		for (int i = sink; i != source; i = parent[i])
			amount = min(amount, capacity[parent[i]][i] - flow[parent[i]][i]);

		for (int i = sink; i != source; i = parent[i]) {
			flow[parent[i]][i] += amount;
			flow[i][parent[i]] -= amount;
		}
		totalFlow+= amount;
	}
	return totalFlow;
}

int N, M;
int wins[20], match[200][2];

bool canWinWith(int totalWins) {
	if (*max_element(wins + 1, wins + N) >= totalWins)
		return false;
	V = 2 + N + M;
	memset(capacity, 0, sizeof(capacity));
	for (int i = 0; i < M; i++) {
		capacity[0][2 + i] = 1;

		for (int j = 0; j < 2; j++)
			capacity[2 + i][2 + M + match[i][j]] = 1;
	}

	for (int i = 0; i < N; i++) {
		int maxWin = (i == 0 ? totalWins : totalWins - 1);
		capacity[2 + M + i][1] = maxWin - wins[i];
	}

	return networkFlow(0, 1) == M;
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		cin >> N >> M;
		for (int i = 0; i < N; i++)
			cin >> wins[i];

		int zero_match = 0;
		for (int i = 0; i < M; i++) {
			cin >> match[i][0] >> match[i][1];
			if (match[i][0] == 0 || match[i][1] == 0)
				zero_match++;
		}

		int totalWins = -1;
		bool can = false;
		for (totalWins=wins[0]; totalWins <=zero_match+wins[0]; totalWins++) {
			if (canWinWith(totalWins)) {
				can = true;
				break;
			}
		}
		cout << (can? totalWins : -1) << "\n";

	}
}
