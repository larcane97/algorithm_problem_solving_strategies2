#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 12;
const int INF = 987654321;
int n, k, m, l;

int prerequisite[MAXN];
int classes[10];
int cache[10][1 << MAXN];

int bitCount(int n) {
	int ret = 0;
	for (int i = 1; i <= n; i = (i << 1)) {
		if (n & i) ret++;
	}
	return ret;
}

void main() {

}


int graduate(int semester, int taken) {
	if (bitCount(taken) >= k) return 0;

	if (semester == m) return INF;

	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;

	int canTake = (classes[semester] & ~taken);

	for (int i = 0; i < n; i++) {
		if (
			(canTake & (1 << i)) &&
			((taken & prerequisite[i]) != prerequisite[i]))
			canTake &= ~(1 << i);
	}
	for (int take = canTake; take > 0;
		take = ((take - 1) & canTake)) {
		if (bitCount(take) > l) continue;

		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}

	ret = min(ret, graduate(semester + 1, taken));
	return ret;


}