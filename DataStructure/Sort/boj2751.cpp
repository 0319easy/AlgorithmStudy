#include <iostream>
using namespace std;

template <class T>
void Merge(T* initList, T* mergedList, const int l, const int m, const int n) {
	//initList[l:m]과 initList[m+1:n]은 정렬된 리스트
	//이들은 정렬된 리스트 merged[l:n]으로 합병된다
	int i1, iResult, i2;
	for (i1 = l, iResult = l, i2 = m + 1; //i1, i2와 iResult는 리스트 위치
		i1 <= m && i2 <= n; //어떤 입력 리스트도 소진되지 않음
		iResult++) {
		if (initList[i1] <= initList[i2]) {
			mergedList[iResult] = initList[i1];
			i1++;
		}
		else {
			mergedList[iResult] = initList[i2];
			i2++;
		}
	}

	//첫 번째 리스트의 나머지 레코드(있다면)을 복사
	copy(initList + i1, initList + m + 1, mergedList + iResult);

	//두 번째 리스트의 나머지 레코드(있다면)을 복사
	copy(initList + i2, initList + n + 1, mergedList + iResult);
}

template <class T>
void MergePass(T* initList, T* resultList, const int n, const int s) {
	//길이가 s인 서브리스트의 인접 쌍들이
	//initList에서부터 resultList로 합병된다. n은 initList에 있는 레코드 수이다.
	int i;
	for (i = 1; //i는 합병되는 첫 번째 리스트의 첫 번째 위치
		i <= n - 2 * s + 1; //길이가 s인 두 서브리스트를 위해 원소들이 충분한지?
		i += 2 * s) {
		Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
		//2 * s보다 작은 나머지 리스트를 합병
		
	}
	if ((i + s - 1) < n) Merge(initList, resultList, i, i + s - 1, n);
	else copy(initList + i, initList + n + 1, resultList + i);
}

template <class T>
void MergeSort(T* a, const int n) {
	//a[1:n]을 비감소순으로 정렬한다
	T* tempList = new T[n + 1];
	//l은 현재 합병되고 있는 서브리스트의 길이이다
	for (int l = 1; l < n; l *= 2) {
		MergePass(a, tempList, n, l);
		l *= 2;
		MergePass(tempList, a, n, l); //list와 tempList의 역할을 교환
	}
	delete[] tempList;
}


int main() {
	int n;
	scanf("%d", &n);

	int* a = new int[n + 1];
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}

	MergeSort(a, n);

	for (int i = 1; i <= n; ++i) {
		printf("%d\n", a[i]);
	}
}