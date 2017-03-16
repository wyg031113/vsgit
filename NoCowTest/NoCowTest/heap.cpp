#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T> 
bool default_cmp(const T &a, const T &b)
{
	return a < b;
}
template<>bool default_cmp(const int &a, const int &b)
{
	return a < b;
}

template<typename T, typename F>
void heap_adjust(T *A, int i, int N, F cmper = less<T>())
{
	while (true) {
		int k = i;
		if (i * 2 <= N && cmper(A[k], A[i * 2]))
			k = i * 2;
		if (i * 2 + 1 <= N && cmper(A[k], A[i * 2 + 1]))
			k = i * 2 + 1;
		if (k == i)
			break;
		swap(A[k], A[i]);
		i = k;
	}
}

template<typename T, typename F>
void heap_add(T *A, int v, int N, F cmper = less<T>())
{
	A[N + 1] = v;
	int cur = (N + 1) >> 1;
	while (cur) {
		heap_adjust(A, cur, N + 1, cmper);
		cur >>= 1;
	}
}
template<typename T>
void heap_add(T *A, int v, int N)
{
	heap_add(A, v, N, less<T>());
}

template<typename T>
void heap_adjust(T *A, int i, int N)
{
	heap_adjust(a, i, N, less<T>());
}

int heap_remove(int *A, int N)
{
	
	swap(A[1], A[N]);
	heap_adjust(A, 1, N - 1, less<int>());
	return A[N];
}
void print(int *arr, int N)
{
	for (int i = 1; i <= N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main()
{
	int i;
	int n = 7;
	int arr[100] = { 0,1,10,2,34,0,-1,4 };
	for (i = n / 2; i >= 1; i--)
		heap_adjust(arr, i, n, less<int>());
	print(arr, n);
	heap_add(arr, 5, n++);
	for (i = 0; i < n - 1; i++)
		heap_remove(arr, n - i);
	print(arr, n);
	make_heap(arr+1, arr + n + 1);
	print(arr, n);
	sort_heap(arr+1, arr+n+1);
	print(arr, n);
	
	return 0;
}