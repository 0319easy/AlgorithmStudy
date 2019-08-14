#include <iostream>
using namespace std;

int** m;
int minuspaper = 0;
int zeropaper = 0;
int pluspaper = 0;

bool check(int n, int x, int y) {
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

void cutpaper(int n, int x, int y) {
	if (n == 1) {
		if (m[x][y] == -1) ++minuspaper;
		else if (m[x][y] == 0) ++zeropaper;
		else if (m[x][y] == 1) ++pluspaper;
	}
	else {
		if (check(n, x, y)) {
			if (m[x][y] == -1) ++minuspaper;
			else if (m[x][y] == 0) ++zeropaper;
			else if (m[x][y] == 1) ++pluspaper;
		}
		else {
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					cutpaper(n / 3, x + i * n / 3, y + j * n / 3);
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);

	m = new int*[n];

	for (int i = 0; i < n; ++i) {
		m[i] = new int[n];
		for (int j = 0; j < n; ++j)
			scanf("%d", &m[i][j]);
	}

	cutpaper(n, 0, 0);

	printf("%d\n%d\n%d\n", minuspaper, zeropaper, pluspaper);
}