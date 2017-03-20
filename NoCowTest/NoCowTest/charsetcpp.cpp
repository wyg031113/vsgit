#include<cstdio>
#include<iostream>
using namespace std;
int A[256];
int B[256];
int head = -1;
int tail = -1;
char str[102];
int main()
{
	scanf("%s", str);
	char c = 0;
	for (int i = 0; str[i]; i++) {
		c = str[i];

		if (A[c] == 1)
			continue;
		A[c] = 1;
		if (head == -1) {
			head = tail = c;
			B[head] = -1;
		}
		else {
			B[tail] = c;
			tail = c;
			B[tail] = -1;
		}
	}
	while (head != -1) {
		putchar(head);
		head = B[head];
	}
	putchar('\n');
	fflush(stdout);
	return 0;
}