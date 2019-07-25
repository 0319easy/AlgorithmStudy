#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];			//새로운 배열
	int number = min(oldSize, newSize);	//복사할 원소 수
	copy(a, a + number, temp);
	delete[] a;							//이전 메모리를 제거
	a = temp;
}

template <class T>
class MaxHeap {
public:
	MaxHeap(int theCapacity = 10);
	bool IsEmpty() const;
	//최대힙이 공백이면 true를 반환
	const T& Top() const;
	//최대 원소에 대한 참조를 반환
	void Push(const T& e);
	//최대 힙에 원소를 삽입
	void Pop();
	//최대 우선순위를 가진 원소를 삭제
private:
	T* heap;		//원소 배열
	int heapSize;	//히프에 있는 원소 수
	int capacity;	//배열 히프의 크기
};

template <class T>
MaxHeap<T>::MaxHeap(int theCapacity) {
	if (theCapacity < 1) throw "Capacity must be >= 1.";
	capacity = theCapacity;
	heapSize = 0;
	heap = new T[capacity + 1];	//heap[0]은 사용되지 않음
}

template <class T>
bool MaxHeap<T>::IsEmpty() const {
	return heapSize == 0;
}

template <class T>
const T& MaxHeap<T>::Top() const {
	return heap[1];
}

template <class T>
void MaxHeap<T>::Push(const T& e) {
	//최대 히프에 e를 삽입한다
	if (heapSize == capacity) {//크기를 두배로
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e) {
		//루트로 올라감
		heap[currentNode] = heap[currentNode / 2];	//부모 노드로 이동
		currentNode /= 2;
	}
	heap[currentNode] = e;
}

template <class T>
void MaxHeap<T>::Pop() {
	//최대 원소를 삭제한다
	if (IsEmpty()) throw "Heap is empty. Cannot delete";
	heap[1].~T();	//최대 원소 삭제

	//히프의 마지막 원소 제거
	T lastE = heap[heapSize--];

	//trickle down
	int currentNode = 1;	//루트
	int child = 2;			//currentNode의 자식
	while (child <= heapSize) {
		//child를 currentNode의 큰 자식으로 설정
		if (child < heapSize && heap[child] < heap[child + 1]) child++;

		//currentNode에 lastE를 삽입할 수 있는가?
		if (lastE >= heap[child]) break;	//yes

		//no
		heap[currentNode] = heap[child];	//자식으로 이동
		currentNode = child; child *= 2;	//한 레벨 내려감
	}
	heap[currentNode] = lastE;
}