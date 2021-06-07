#include <vector>
#include <queue>
using namespace std;


// edmonds-Karp
// => ford fulkerson + BFS
const int INF = 987654321;
const int MAX_V = 50;
int V;
// using adjcancy array 
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int networkFlow(int source, int sink) {
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

		if (parent[sink] == - 1)break;

		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);

		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}


// using adjcancy list
struct Edge {
	int target, capacity, flow;
	Edge* reverse;

	int residualCapacity() const {
		return capacity - flow;
	}

	void push(int amt) {
		flow += amt;
		reverse->flow -= amt;
	}
};

vector<Edge*>adj[MAX_V];

void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge(), * vu = new Edge();
	uv->target = v;
	uv->capacity = capacity;
	uv->flow = 0;
	uv->reverse = vu;

	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;
	adj[u].push_back(uv);
	adj[v].push_back(vu);
}
