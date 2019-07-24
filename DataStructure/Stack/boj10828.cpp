#include <iostream>
#include <algorithm>
#include <string>
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

class Stack {
private:
	int* stack;
	int stacktop;
	int capacity;
public:
	Stack(int capacity = 10);
	void push(int item);
	int pop();
	int size();
	int empty();
	int top();
};

Stack::Stack(int capacity) :capacity(capacity) {
	stack = new int[capacity];
	stacktop = -1;
	this->capacity = capacity;
}

void Stack::push(int item) {
	if (stacktop == capacity - 1) {
		ChangeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}

	stack[++stacktop] = item;
}

int Stack::pop() {
	if (empty() == 1)
		return -1;
	
	return stack[stacktop--];
}

int Stack::size() {
	return stacktop + 1;
}

int Stack::empty() {
	if (stacktop == -1)
		return 1;
	else
		return 0;
}

int Stack::top() {
	if (empty() == 1)
		return -1;
	
	return stack[stacktop];
}


int main() {
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	cin.ignore();

	Stack stack;

	for (int i = 0; i < n; ++i) {
		string str; int x, result;
		cin >> str;

		if (str.compare("push") == 0) {
			cin >> x;
			stack.push(x);
		}
		else if (str.compare("pop") == 0) {
			result = stack.pop();
			cout << result << endl;
		}
		else if (str.compare("size") == 0) {
			result = stack.size();
			cout << result << endl;
		}
		else if (str.compare("empty") == 0) {
			result = stack.empty();
			cout << result << endl;
		}
		else if (str.compare("top") == 0) {
			result = stack.top();
			cout << result << endl;
		}

		cin.ignore();
	}
}