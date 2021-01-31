#include<iostream>
using namespace std;

template<class T> class Chain;

template<class T>
class ChainNode {
	friend class Chain<T>;
public:
	ChainNode(T element = NULL, ChainNode<T> *node = NULL)
	{
		data = element;
		link = node;
	}
private:
	T data;
	ChainNode *link;
};

template<class T>
class Chain {
public:
	Chain();                              // 생성자
	~Chain();                             // 소멸자
	void Print();                         // 출력
	void Insert(int i, ChainNode<T> *&x); // i 번째  삽입
	void InsFront(ChainNode<T> *p);       // 맨 앞에 삽입
	void InsBack(ChainNode<T> *p);	      // 맨 뒤에 삽입
	void Delete(ChainNode<T> *x);         // 삭제
	int Front();						  // 첫 번째 원소를 반환
	int Back();                           // 마지막 원소를 반환
	int Get(int i);                       // i 번째 원소를 반환
	void DelFront();                      // 체인 맨 앞의 원소 삭제
	void DelBack();						  // 체인 맨 뒤의 원소 삭제
	void Delete(int i);                   // 체인 i 번째 원소 삭제

	class ChainIterator {             // 체인 반복자
	public:
		ChainIterator(ChainNode<T> *node = 0) {
			current = node;
		}
		ChainIterator operator++(int) {
			ChainIterator temp = *this;
			current = current->link;
			return temp;
		}
		ChainIterator operator++() {
			current = current->link;
			return *this;
		}
		bool operator==(const ChainIterator& temp) const {
			return current == temp.current;
		}
		bool operator!=(const ChainIterator& temp) const {
			return current != temp.current;
		}
		T* operator->() const {	return &current -> data; }
		T& operator*() const { return current -> data; }
		ChainNode<T>* GetCurrent() { return current; }
	private:
		ChainNode<T> *current;
	};
	
	ChainIterator begin() const {
		return ChainIterator(first);
	}
	ChainIterator end() const {
		return ChainIterator(NULL);
	}

private:
	ChainNode<T> *first;
	ChainNode<T> *last;
};

template<class T>
Chain<T>::Chain()     // 공백 체인 생성자
{
	first = last = 0;
}

template<class T>
Chain<T>::~Chain()    // 체인 소멸자
{
	while(first) {
		DelFront();
	}
	delete first;
}

template <class T>
int Chain<T>::Front(){   // 맨 앞의 원소 반환
	Chain::ChainIterator it(begin());
	return *it;
}

template <class T>
int Chain<T>::Back() {  // 맨 뒤의 원소 반환
	int i = 0;
	ChainIterator it(begin());
	for( ; it != end(); it++)
		i++;
	ChainIterator it2(begin());
	for(int j = 0; j != i - 1;j++)
		it2++;
	return *it2;
}

template <class T>
int Chain<T>::Get(int i) {   // i 번째 윈소 반환
	ChainIterator it(begin());
	for(int j = 0; j < i; j++)
		it++;
	return *it;
}

template<class T>
void Chain<T>::Print()   // 체인 출력 함수
{
	ChainIterator tmp(begin());
	for ( ; tmp != end(); tmp++)
		cout << " " << *tmp;
	cout << endl;
}

template<class T>
void Chain<T>::Insert(int i, ChainNode<T> *&x) // i번째 원소 뒤에 삽입
{
	ChainIterator it(first);
	ChainNode<T> *tmp = first;
	for(int j = 0; j < i; j++)
		it++;
	tmp = it.GetCurrent();
	x -> link = tmp -> link;
	tmp -> link = x;
}

template <class T>
void Chain<T>::InsFront(ChainNode<T> *p) 
{          // 맨 앞에 삽입
	p->link = first;
	first = p;
}

template <class T>
void Chain<T>::InsBack(ChainNode<T> *p) 
{    // 맨 뒤에 삽입
	if (first) {
		last->link = p;
		last = p;
		last->link = NULL;
	}
	else {
		first = last = p;
	}
}

template<class T>
void Chain<T>::Delete(int i)
{        // i 번째 원소 삭제
	if (first){
		ChainNode<T> *tmp = first;
		ChainNode<T> *tmp2 = first;
		ChainIterator it(begin());
		for(int j = 0; j < i - 1; j++) {
			it++;
		}
		tmp = it.GetCurrent();
		it++;
		tmp2 = it.GetCurrent();
		tmp -> link = tmp2 -> link;
		delete tmp2;
	}
	else {
		delete first;
		first = NULL;
	}
}

template <class T>
void Chain<T>::DelFront() 
{     // 맨 앞의 원소 삭제
	if(first == 0) {
		cout<<"Chain is Empty!"<<endl;
	}
	else if (first == last) {
		delete first;
		first = NULL;
	}
	else {
		ChainNode<T> *tmp = first;
		first = first -> link;
		delete tmp;
	}
}

template <class T>
void Chain<T>::DelBack() 
{	// 맨 뒤의 원소 삭제
	int i = 0;
	ChainNode<T> *tmp = first;
	ChainIterator it(begin());
	if(first == 0)
		cout<<"Chain is Empty!"<<endl;
	else if (first == last) {
		delete first;
		first = NULL;
	}
	else {
		for(i = 0; it != end(); it++)
			i++;
		ChainIterator it(begin());
		for(int j = 0; j < i - 2; j++)
			it++;
		tmp = it.GetCurrent();
		delete tmp -> link;
		tmp -> link = NULL;
		last = tmp;
	}
}

int main(void) {
	int i;
	cout << "1부터 9까지의 정수를 갖는 노드를 추가" << endl;
	Chain<int> chainlist;
	ChainNode<int>* arr[9];
	Chain<int>::ChainIterator it = chainlist.begin();
	for (i = 0; i < 9; i++) {
		arr[i] = new ChainNode<int>(i + 1);
	}
	for (i = 0; i < 9; i++) {
		chainlist.InsBack(arr[i]);
	}
	cout << "노드 추가 완료" << endl;
	cout << "전체 출력 확인" << endl;
	chainlist.Print();

	cout << "0을 맨 앞에 추가" << endl;
	ChainNode<int> *tmp = new ChainNode<int>(0);
	chainlist.InsFront(tmp);
	chainlist.Print();

	cout << "10을 맨 뒤에 추가" << endl;
	tmp = new ChainNode<int>(10);
	chainlist.InsBack(tmp);
	chainlist.Print();

	cout << "Front를 호출하여 0이 나오는지 확인" << endl;
	i = chainlist.Front();
	cout<<i<<endl;

	cout << "Back을 호출하여 10이 나오는지 확인" << endl;
	i = chainlist.Back();
	cout<<i<<endl;

	cout << "Get(2)를 통해 2가 나오는지 확인" << endl;
	i = chainlist.Get(2);
	cout<<i<<endl;

	cout << "맨 앞에 있는 0을 삭제" << endl;
	chainlist.DelFront();
	chainlist.Print();

	cout << "맨 뒤에 있는 10을 삭제" << endl;
	chainlist.DelBack();
	chainlist.Print();

	cout << "3과 4 사이에 100을 삽입(2번째 윈소 뒤 삽입)" << endl;
	tmp = new ChainNode<int>(100);
	chainlist.Insert(2,tmp);
	chainlist.Print();

	cout << "6번째 원소 삭제" << endl;
	chainlist.Delete(6);
	chainlist.Print();
	return 0;
}
