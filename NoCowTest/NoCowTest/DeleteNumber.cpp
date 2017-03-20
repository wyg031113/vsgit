#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 1002
int A[N];
int main()
{
	int n;
	while (cin >> n) {
		memset(A, 0, sizeof(A));
		int k = n;
		int i =0;
		while (k > 1) {
			for (int j = 0; j < 3; ) {
				if (A[i] != -1)
					++j;
				if (j == 3)
					break;
				++i;
				i %= n;
			}
			k--;
			A[i] = -1;
			//printf("delete:%d\n", i);
		}
		while (A[i] == -1)
			i = (i + 1) % n;
		printf("%d\n", i);
	}
	return 0;
}