#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);

	int* a = new int[n + 1];
	int* b = new int[m + 1];
	int* r = new int[m + n + 1];

	for (int idx = 1; idx <= n; ++idx) 
		scanf("%d", &a[idx]);

	for (int idx = 1; idx <= m; ++idx) 
		scanf("%d", &b[idx]);

	int i = 1, j = 1;	//i는 a의 인덱스, j는 b의 인덱스
	int k = 1;			//k는 r의 인덱스

	while ((i <= n) && (j <= m)) {
		if (a[i] < b[j]) {
			r[k] = a[i];
			++i;
			++k;
		}
		else {
			r[k] = b[j];
			++j;
			++k;
		}
	}	

	//남은거 합치기
	if (i <= n)
		for (i; i <= n; ++i, ++k)
			r[k] = a[i];

	if (j <= m)
		for (j; j <= m; ++j, ++k)
			r[k] = b[j];

	for (int idx = 1; idx <= (n + m); ++idx)
		printf("%d ", r[idx]);

	printf("\n");
}