#include <iostream>

using namespace std;

int n;
const int MAX_N = 1000;
unsigned char sieve[(MAX_N + 7) / 8];

inline bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7));
}

inline void setComposite(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7));
}

void eratosthenes() {
	memset(sieve, 255, sizeof(sieve));
	setComposite(0);
	setComposite(1);
	int sqrtn = sqrt(n);
	for (int i = 0; i <= sqrtn; i++) {
		if (isPrime(i))
			for (int j = i * i; j <= n; j += i)
				setComposite(j);
	}
}