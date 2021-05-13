#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

map<int, int> coords;

bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);

	if (it == coords.end()) return false;
	
	return y < it->second;
}

void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);

	if (it == coords.begin()) return;
	it--;
	while (true) {
		if (it->second > y) break;

		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int>::iterator jt = it;
			jt--;
			coords.erase(it);
			it = jt;
		}
	}
}

int registered(int x, int y) {
	if (isDominated(x, y)) return coords.size();

	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n;
		cin >> n;
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int p, q;
			cin >> p >> q;
			ret +=registered(p, q);
		}
		cout << ret << endl;
	}
}

