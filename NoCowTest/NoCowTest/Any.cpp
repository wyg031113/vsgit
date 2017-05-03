#include <iostream>
#include <functional>
#include <typeindex>
#include <queue>
#include <chrono>
using namespace std;
queue < std::function<void()> > call_backs;
class Any
{
public:
	template<typename T >
	Any(T t) :m_ptr((void*)(new T(std::forward<T>(t)))), m_tpIndex(std::type_index(typeid(T)))
	{
	}
	template<typename T>
	T &get()
	{
		if (std::type_index(typeid(T)) != m_tpIndex)
			throw std::bad_cast();
		return *static_cast<T*>(m_ptr);
	}
	~Any()
	{
		delete m_ptr;
	}
private:
	void * m_ptr;
	std::type_index  m_tpIndex;
};
void func(int a)
{
	cout << "Hello " << a << endl;
}
void test(int a, int b)
{
	cout << a + b << endl;
}
class A
{
public:
	A() { cout << "A constructed." << endl; }
	~A() { cout << "A deconstructed." << endl; }
	A(const A& a) {
		cout << "A copy constructed." << endl;
	}
	A &operator=(const A &a) {
		cout << "A assign copyed." << endl;
	}
	void func(int x) 
	{
		cout << x*x << endl;
	}
};
void run()
{
	while (!call_backs.empty()) {
		auto f = call_backs.front();
		f();
		call_backs.pop();
	}
}
void addd()
{
	A a;
	call_backs.push(std::bind(&A::func, a, 3));
}
int main(int argc, char *argv[])
{
	
	call_backs.push(std::bind(func, 3));
	call_backs.push(std::bind(test, 2, 4));
	A a;
	call_backs.push(std::bind(&A::func, &a, 3));
	run();

	return 0;
}