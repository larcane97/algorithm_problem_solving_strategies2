#include <iostream>
#include <vector>
#include "RMQ.cpp"

const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];

int no2serial[MAX_N], serial2no[MAX_N];

int locInTrip[MAX_N], depth[MAX_N];

int nextSerial;

void traverse(int here, int d, vector<int>& trip) {
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	nextSerial++;
	depth[here] = d;

	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);

	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		trip.push_back(no2serial[here]);
	}
}

RMQ* prepareRMQ() {
	nextSerial = 0;
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

int distance(RMQ* rmq, int u, int v) {
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);

	int lca = serial2no[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}