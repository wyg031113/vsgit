#include "ObjectPool.h"
#include <iostream>
#include <string>
#include <time.h>
#include <>
using namespace std;
class WYG
{
public:
	WYG(string nm = "wyg", int ag = 26) :name(nm), age(ag) {}
	void show() {
		cout << name << " " << age << endl;
	}
private:
	int age;
	string name;
};
WYG *tmp[1001];
#define USE_POOL
class A
{
public:
	A() { cout << "A" << endl; }
};
int main()
{
	objpool::ObjectPool<WYG> pool(500);
	clock_t start = clock();
	for (int k = 0; k < 300; k++) {
		for (int i = 0; i < 1000; i++) {
#ifdef USE_POOL
			tmp[i] = pool.alloc();
#else
			tmp[i] = new WYG;
#endif
		}
		for (int j = 0; j < 1000; j++){
#ifdef USE_POOL
			pool.free(tmp[j]);
#else
			delete tmp[j];
#endif
		}
	}
	clock_t end = clock();
	printf("use time:%f seconds.\n", 1.0 * (end - start) / CLOCKS_PER_SEC);
	[]() {cout << "Hello world" << endl; }();

	return 0;
}