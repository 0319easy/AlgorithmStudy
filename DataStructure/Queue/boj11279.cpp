#include <iostream>
#include <queue>
using namespace std;

int main() {
	priority_queue<int, vector<int>, less<int> > pq;

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);

		if (x == 0) {
			if (pq.empty())
				printf("0\n");
			else {
				x = pq.top();
				pq.pop();
				printf("%d\n", x);
			}
		}
		else {
			pq.push(x);
		}
	}
}