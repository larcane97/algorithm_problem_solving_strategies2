#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct suffixComparator {
	const string& s;
	suffixComparator(const string& s) : s(s) {};
	bool operator() (int i, int j) {
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;
	}
};

vector<int> getSuffixArrayNaive(const string& s) {
	vector<int> perm;

	for (int i = 0; i < s.size(); i++) perm.push_back(i);

	sort(perm.begin(), perm.end(), suffixComparator(s));
	return perm;
}


struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {
		t = _t;
		group = _group;
	}
	bool operator() (int a, int b) {
		if (group[a] != group[b]) return group[a] > group[b];

		return group[a + t] < group[b + t];
	}
};