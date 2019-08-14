#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int** m;

bool checkvideo(int n, int x, int y) {
	int f = m[x][y];
	bool ans = true;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (m[x + i][y + j] != f) {
				ans = false;
				break;
			}
		}
		if (!ans) break;
	}

	return ans;
}

void cutvideo(int n, int x, int y) {
	string result = "";

	if (n == 1) {
		printf("%d", m[x][y]);
	}
	else {
		if (checkvideo(n, x, y)) {
			printf("%d", m[x][y]);
		}
		else {
			printf("(");
			cutvideo(n / 2, x, y);		cutvideo(n / 2, x, y + n / 2);
			cutvideo(n / 2, x + n / 2, y);	cutvideo(n / 2, x + n / 2, y + n / 2);
			printf(")");
		}
	}
	
}

int main() {
	int n;
	scanf("%d", &n);

	m = new int* [n];

	for (int i = 0; i < n; ++i) {
		m[i] = new int[n];
		for (int j = 0; j < n; ++j) {
			scanf("%1d", &m[i][j]);
		}
	}

	cutvideo(n, 0, 0);

	printf("\n");
}