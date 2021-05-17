#include <iostream>
#include "RMQ.cpp"




int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n, q;
		cin >> n >> q;

		vector<int> arrMax(n);
		vector<int> arrMin(n);
		for (int i = 0; i < n; i++) {
			cin >> arrMax[i];
			arrMin[i] = -arrMax[i];
		}
		RMQ rmqMAX = RMQ(arrMax);
		RMQ rmqMIN = RMQ(arrMin);
	
		for (int i = 0; i < q; i++) {
			int a, b;
			cin >> a >> b;
			int max = rmqMAX.query(a, b);
			int min = -rmqMIN.query(a, b);
			cout << min - max << endl;
		}
	}
}