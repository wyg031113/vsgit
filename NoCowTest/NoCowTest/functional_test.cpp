#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
#include<valarray>
#include<typeindex>
#include<typeinfo>
#include<signal.h>
typedef void(*handler_signale_t)(int sig);

handler_signale_t signal_myx(int sig, handler_signale_t pf);
void (* (*signal_myy)(int, void(*pf)(int)))(int) = signal;

using namespace std;
void show(const vector<int> &vec)
{
	for (auto x : vec)
		cout << x << " ";
	cout << endl;
}
int main()
{
	cout << typeid(signal_myx).name() << endl;
	cout << typeid(signal).name() << endl;
	cout << typeid(signal_myy).name() << endl;
	vector<int> vec = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v2(vec.size(), 0);
	vector<int> v3;
	v3.reserve(vec.size());
	std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) {return x*x; });
	show(vec);
	auto v2_end = std::copy_if(vec.begin(), vec.end(), v2.begin(), [](int x) {return x & 1; });
	show(v2);
	
	cout << std::accumulate(v2.begin(),v2.end(), 0) << endl;
	cout << std::accumulate(v2.begin(), v2_end, 1, [](int x, int y) {return x*y; })<< endl;

	valarray<int> val = {1,2,3,4,5,6};
	cout << val.sum() << endl;
	 val[std::slice(0, 2, 2)] = 7;
	for (std::size_t i = 0; i < val.size(); i++)
		cout << val[i] << " ";
	cout << endl;

	
}