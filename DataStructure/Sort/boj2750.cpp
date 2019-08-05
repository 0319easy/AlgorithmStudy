#include <iostream>
using namespace std;

template <class T>
void QuickSort(T* a, const int left, const int right) {
	//a[left:right]를 비감소 순으로 정렬한다
	//a[left]는 피벗으로 임의로 선정한다. 변수 i와 j는
	//서브리스트를 분할하는 데 사용되어 항상 a[m] <= pivot, m < i와
	//a[m] >= pivot, m > j을 만족시킨다. a[left] <= a[right+1]이라고 가정한다.
	if (left < right) {
		int i = left,
			j = right + 1,
			pivot = a[left];
		do {
			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i < j) swap(a[i], a[j]);
		} while (i < j);
		swap(a[left], a[j]);

		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right);
	}
}

int main() {
	int n, t;
	scanf("%d", &n);

	int* a = new int[n + 1];

	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t);
		a[i] = t;
	}

	QuickSort(a, 1, n);

	for (int i = 1; i <= n; ++i) {
		printf("%d\n", a[i]);
	}
}