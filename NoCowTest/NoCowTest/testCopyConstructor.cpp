#include <iostream>
#include <cstdio>
using namespace std;

class Demo {

public:
	int a;
	Demo();
	~Demo();
	Demo(const Demo &demo);
};

Demo::Demo() {
	cout << "Demo" << this << endl;
}

Demo::Demo(const Demo &demo) {
	a = demo.a;
	cout << "Demo copy" << this << endl;
}

Demo::~Demo() {
	cout << "~Demo" << endl;
}

Demo test() {
	Demo demo;
	demo.a = 1000;
	cout << "test()" << endl;
	return demo;
}

int main(int argc, char **argv) {
	Demo demo(test());
	cout << "a=" << demo.a << endl;
	printf("%p\n", &demo);
}