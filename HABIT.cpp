#include <iostream>
#include <vector>
#include <string>
#include "suffix.cpp"

using namespace std;

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int k;
		string script;
		cin >> k;
		cin >> script;
		cout << longestFrequent(k,script) << endl;

	}
}


int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j])
	{
		i++, j++, k++;
	}
	return k;
}


int longestFrequent(int k, const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	for (int i = 0; i + k <= s.size(); i++) {
		ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
	}
	return ret;
}