#include <iostream>
#include <functional>
#include <cstdio>
#include <vector>
using namespace std;
template<int...>
struct seq{};




template<int N, int ... Indexes>
struct MakeIndexes
{
	using type = typename MakeIndexes<N - 1, N - 1, Indexes...>::type;
};

template<int ... Indexes>
struct MakeIndexes<0, Indexes...>
{
	using type = seq<Indexes...>;
};

template<typename T, typename ...Args>
void call(T f, Args && ...arg)
{
	f(std::forward<Args>(arg)...);
}
void f1()
{
	cout << "f1" << endl;
}
int f2(int x)
{
	cout << "f1:" <<x<<endl;
	return x;
}
double f3(int x, double y)
{
	cout << "f1xy:" << x+y << endl;
	return x+y;
}
double f4(std::initializer_list<int> var)
{
	return 0;
}
template<typename T>
void printx(T param)
{
	cout << param << "  ";
}
template<typename T>
int print_param(T param)
{
	cout << param << "  ";
	return 0;
}

template<typename T, typename ...Args>
int print_param(T arg, Args ...param)
{
	print_param(arg);
	print_param(param...);
	return 0;
}
template<typename ...Args>
int print(Args && ...args)
{
	printf("--------print_start-----------\n");
	//print_param(args...);
	auto arr = {(printx(args),0)...};
	printf("\n------print_end-------------\n\n");
	size_t len = printf(std::forward<Args>(args)...);
	return len;
}
template<typename F, typename D, typename ...Args>
void test_addif(vector<D> &vec, F f, Args ...arg)
{
	auto arr = { (f(arg)?(vec.push_back(arg),0):1)...};
}
int main()
{

	using T = MakeIndexes<4>::type;
	cout << typeid(T).name() << endl;
	int y = 3;
	//cin >> y;
	auto ff = std::bind(f2, y);
	auto x = ff();
	auto f = { 1,4,4,9 };
	cout << typeid(f).name() << endl;
	print("a=%d b=%d\n", ff(), 56);
	vector<int> vec;
	test_addif(vec, [](int x) { if (x > 2 && x < 8) return true; else return false; }, 1, 2, 3, 4, 5, 6, 12, 23);
	for (auto yy : vec)
		cout << yy << endl;
}