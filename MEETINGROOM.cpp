#include <iostream>
#include <vector>
#include "tarjanSCC.cpp"
#include <algorithm>
using namespace std;



bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second <= b.first || b.second <= a.first;
}

void makeGraph(const vector<pair<int, int>>& meetings) {
	int vars = meetings.size();

	adj.clear(); adj.resize(vars * 2);
	for (int i = 0; i < vars; i += 2) {
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2);
		adj[j * 2 + 1].push_back(i * 2);
	}
	for (int i = 0; i < vars; i++) {
		for (int j = 0; j < i; j++) {
			if (!disjoint(meetings[i], meetings[j])) {
				adj[i * 2].push_back(j * 2 + 1);
				adj[j * 2].push_back(i * 2 + 1);
			}
		}
	}
}

vector<int> solve2SAT() {
	int n = adj.size() / 2;

	vector<int>label = tarjanSCC();

	for (int i = 0; i < 2 * n; i += 2)
		if (label[i] == label[i + 1])
			return vector<int>();

	vector<int> value(2 * n, -1);

	vector<pair<int, int>> order;
	for (int i = 0; i < 2 * n; i++)
		order.push_back(make_pair(-label[i], i));
	sort(order.begin(), order.end());

	for (int i = 0; i < 2 * n; i++) {
		int vertex = order[i].second;
		int variable = vertex / 2, isTrue = vertex % 2 == 0;
		if (value[variable] != -1) continue;
		value[variable] = !isTrue;
	}
	return value;
}
