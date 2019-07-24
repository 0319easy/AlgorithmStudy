#include <iostream>
#include <algorithm>
using namespace std;

class Queue {
	//0개 이상의 원소를 가진 유한 순서 리스트
public:
	Queue(int queueCapacity = 10);
	//처음에 크기가 queueCapacity인 공백 큐를 생성

	int IsEmpty() const;
	//큐의 원소 수가 0이면 true, 아니면 false를 반환

	int Front() const;
	//큐의 앞에 있는 원소를 반환

	int Rear() const;
	//큐의 뒤에 있는 원소를 반환

	void Push(const int item);
	//큐의 뒤에 item을 삽입

	int Pop();
	//큐의 앞 원소를 삭제

	int Size();

private:
	int* queue;		//큐 원소를 위한 배열
	int front;		//첫 번째 원소로부터 반시계 방향으로 한 위치 뒤
	int rear;		//마지막 원소의 위치
	int capacity;	//큐 배열의 크기
	int size;
};


Queue::Queue(int queueCapacity) : capacity(queueCapacity) {
	if (capacity < 1) throw "Queue capacity must be > 0";
	queue = new int[capacity];
	front = rear = 0;
	size = 0;
}

int Queue::IsEmpty() const { 
	if (front == rear)
		return 1;
	else return 0;
}

inline int Queue::Front() const {
	if (IsEmpty()) return -1;
	return queue[(front + 1) % capacity];
}

inline int Queue::Rear() const {
	if (IsEmpty()) return -1;
	return queue[rear];
}

void Queue::Push(const int item) {
	//큐의 리어에 item을 삽입한다
	if ((rear + 1) % capacity == front) {
		//큐가 만원이면 크기를 두 배로
		//두 배 크기의 배열을 할당
		int* newQueue = new int[2 * capacity];

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
	++size;
}

int Queue::Pop() {
	//큐로부터 원소를 삭제한다.
	if (IsEmpty()) return -1;
	front = (front + 1) % capacity;
	--size;
	return queue[front];
}

int Queue::Size() {
	return size;
}

int main() {
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	Queue queue;

	for (int i = 0; i < n; ++i) {
		string str; int n;

		cin >> str;

		if (str.compare("push") == 0) {
			cin >> n;
			queue.Push(n);
		}
		else if (str.compare("pop") == 0) {
			n = queue.Pop();
			cout << n << endl;
		}
		else if (str.compare("size") == 0) {
			n = queue.Size();
			cout << n << endl;
		}
		else if (str.compare("empty") == 0) {
			n = queue.IsEmpty();
			cout << n << endl;
		}
		else if (str.compare("front") == 0) {
			n = queue.Front();
			cout << n << endl;
		}
		else if (str.compare("back") == 0) {
			n = queue.Rear();
			cout << n << endl;
		}
	}
}