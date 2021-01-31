#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

class Bizcard {
	private:
		char* name;
		char* phone;
	public:
		void ShowInfo() {
			cout << "Name : " << name << "\nPhone Number : " << phone << endl;
		}
		Bizcard() { }
		
		Bizcard(const char* name, const char* phone) {
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
			this->phone = new char[strlen(phone) + 1];
			strcpy(this->phone, phone);
		}

		Bizcard (const Bizcard& copy) {
			name = new char[strlen(copy.name) + 1];
			phone = new char[strlen(copy.phone) + 1];
			strcpy(name, copy.name);
			strcpy(phone, copy.phone);
		}
		Bizcard& operator=(const Bizcard& ref) {
			delete[] this->name;
			delete[] this->phone;
			name=NULL;
			phone=NULL;
			this->name = new char[strlen(ref.name) + 1];
			this->phone = new char[strlen(ref.name) + 1];
			strcpy(this->name, ref.name);
			strcpy(this->phone, ref.phone);
			return *this;
		}

		~Bizcard() {
			delete []name;
			delete []phone;
		}
};

template <class T>
class Bag 
{
	public:
		Bag(int bagCapacity = 3);
		~Bag();

		int Size() const;
		bool IsEmpty() const;
		T& Element() const;

		void Push(const T&);
		void Pop();

	private:
		T *array;
		int capacity;
		int top;
};

template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity) {
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag() { 
	delete[] array;
   		
}

template <class T>
void Bag<T>::Push(const T& x) {
	if (capacity == top + 1)
	{
		ChangeSize1D(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

int min(const int a, const int b) {
	if(a<=b) return a;
	else return b;
}

template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0)
		throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete []a;
	a = temp;
}

template <class T>
void Bag<T>::Pop() {
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int delpos = top / 2;
	copy(array + delpos + 1, array + top + 1, array + delpos);
	
}

template <class T>
int Bag<T>::Size() const {
	return capacity;
}

template <class T>
bool Bag<T>::IsEmpty() const {
	return (top==-1);
}

template <class T>
T& Bag<T>::Element() const {
	srand(time(NULL));
	int Element_num;
	if (IsEmpty()) cout << "No Data" << endl;
	else {
		Element_num = rand() % top;
		return *(array+Element_num);
	}
}

int main(void) {
	Bizcard b1("Hello", "01012345678");
	Bizcard b2("Alice", "01099998888");
	Bizcard b3("Jason", "01029736847");
	Bizcard b4("Michael", "01087267362");
	Bizcard b5("Simpson", "0192765365");
	Bizcard b6("Harry Porter", "0119738267");
	Bizcard b7("Anonymous", "01029738726");

	Bag <Bizcard> b(3);
	
	cout<<"빈 Bag에 대한 연산 확인"<<endl;
	cout<<"Size() : "<<b.Size()<<" , IsEmpty() : "<<((b.IsEmpty())?"True":"False")<<endl;
	cout<<"Element() 연산 결과 : "<<endl;
	b.Element();
	
	b.Push(b1);
	b.Push(b2);
	b.Push(b3);
	cout<<endl<<"Push() 연산 3번 수행 후 확인"<<endl;
	cout<<"Size() : "<<b.Size()<<" , IsEmpty() : "<<((b.IsEmpty())?"True":"False")<<endl;
	cout<<"Element() 연산 결과 : "<<endl;
	b.Element().ShowInfo();

	b.Push(b4);
	b.Push(b5);
	b.Push(b6);
	b.Push(b7);
	cout<<endl<<"Push() 연산 4번 추가 수행 후 확인"<<endl;
	cout<<"Size() : "<<b.Size()<<" , IsEmpty() : "<<((b.IsEmpty())?"True":"False")<<endl;
	cout<<"Element() 연산 결과 : "<<endl;
	b.Element().ShowInfo();
	
	b.Pop();
	b.Pop();
	cout<<endl<<"Pop() 연산 2번 실행 후 확인"<<endl;
	cout<<"Size() : "<<b.Size()<<" , IsEmpty() : "<<((b.IsEmpty())?"True":"False")<<endl;
	cout<<"Element() 연산 결과 : "<<endl;
	b.Element().ShowInfo();
	cout<<endl;
	return 0;	
}

