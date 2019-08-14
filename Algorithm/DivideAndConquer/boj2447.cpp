#include <iostream>
using namespace std;

void printempty(int n, char** m, int x, int y) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			m[x + i][y + j] = ' ';
		}
	}
}

void printstar(int n, char** m, int x, int y) {
	if (n == 3) {
		m[x][y] = '*';	m[x + 1][y] = '*';	m[x + 2][y] = '*';
		m[x][y + 1] = '*';	m[x + 1][y + 1] = ' ';	m[x + 2][y + 1] = '*';
		m[x][y + 2] = '*';	m[x + 1][y + 2] = '*';	m[x + 2][y + 2] = '*';
	}
	else {
		printstar(n / 3, m, x, y);	printstar(n / 3, m, x + n / 3, y); printstar(n / 3, m, x + 2 * n / 3, y);
		printstar(n / 3, m, x, y + n / 3);	printempty(n / 3, m, x + n / 3, y + n / 3); printstar(n / 3, m, x + 2 * n / 3, y + n / 3);
		printstar(n / 3, m, x, y + 2 * n / 3);	printstar(n / 3, m, x + n / 3, y + 2 * n / 3); printstar(n / 3, m, x + 2 * n / 3, y + 2 * n / 3);
	}
}


int main() {
	int n;
	scanf("%d", &n);

	char** m = new char* [n];
	for (int i = 0; i < n; ++i) m[i] = new char[n];

	printstar(n, m, 0, 0);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%c", m[i][j]);
		}
		printf("\n");
	}
}