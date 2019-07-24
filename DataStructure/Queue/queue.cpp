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
class Queue {
	//0개 이상의 원소를 가진 유한 순서 리스트
public:
	Queue(int queueCapacity = 10);
	//처음에 크기가 queueCapacity인 공백 큐를 생성

	bool IsEmpty() const;
	//큐의 원소 수가 0이면 true, 아니면 false를 반환

	T& Front() const;
	//큐의 앞에 있는 원소를 반환

	T& Rear() const;
	//큐의 뒤에 있는 원소를 반환

	void Push(const T& item);
	//큐의 뒤에 item을 삽입

	void Pop();
	//큐의 앞 원소를 삭제

private:
	T* queue;		//큐 원소를 위한 배열
	int front;		//첫 번째 원소로부터 반시계 방향으로 한 위치 뒤
	int rear;		//마지막 원소의 위치
	int capacity;	//큐 배열의 크기
};

template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity) {
	if (capacity < 1) throw "Queue capacity must be > 0";
	queue = new T[capacity];
	front = rear = 0;
}

template <class T>
inline bool Queue<T>::IsEmpty() const { return front == rear; }

template <class T>
inline T& Queue<T>::Front() const {
	if (IsEmpty()) throw "Queue is empty. No front element";
	return queue[(front + 1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear() const {
	if (IsEmpty()) throw "Queue is empty. No rear element";
	return queue[rear];
}

template <class T>
void Queue<T>::Push(const T& item) {
	//큐의 리어에 item을 삽입한다
	if ((rear + 1) % capacity == front) {
		//큐가 만원이면 크기를 두 배로
		/*//(1) 크기가 두 배가 되는 새로운 배열 newQueue 생성
		T* newQueue = new T[capacity * 2];

		//(2) 두 번째 부분(즉 queue[front + 1]과 queue[capacity - 1] 사이에 있는 원소들)을 newQueue의 0에서부터 복사해 넣는다.
		copy(a + front + 1, a + capacity - 1, newQueue);
		
		//(3) 첫 번째 부분(즉 queue[0]와 queue[rear] 사이에 있는 원소들)을 newQueue의 capacity-front-1에서부터 복사해 넣는다
		copy(a, a + rear, newQueue + capacity - front - 1);

		delete[] queue;
		queue = newQueue;

		rear += (capacity - front - 1);
		capacity *= 2;
		front = capacity - 1;*/

		//두 배 크기의 배열을 할당
		T* newQueue = new T[2 * capacity];

		//queue를 newQueue로 복사
		int start = (front + 1) % capacity;
		if (start < 2)
			//둘러쌀 필요가 없음
			copy(queue + start, queue + start + capacity - 1, newQueue);
		else
		{
			//둘러싸서 큐를 만듦
			copy(queue + start, queue + capacity, newQueue);
			copy(queue, queue + rear + 1, newQueue + capacity - start);
		}

		//newQueue로 전환
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}

	rear = (rear + 1) % capacity;
	queue[rear] = item;
}

template <class T>
void Queue<T>::Pop() {
	//큐로부터 원소를 삭제한다.
	if (IsEmpty()) throw "Queue is empty. Cannot delete.";
	front = (front + 1) % capacity;
	queue[front].~T();	//T를 위한 파괴자
}