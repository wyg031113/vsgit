#include <iostream>
#include <vector>
#include <cstdio>
#include <iomanip>
using namespace std;
void generate_matrix(vector<vector<int>> &vec, int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++) {
		vec.push_back(vector<int>());
		for (j = 0; j < n; j++) {
			vec[i].push_back(i*n + j + 1);
		}
	}
}
void show_matrix(vector<vector<int>> &vec) {
	for (auto &x : vec) {
		for (auto y : x) {
			cout<<setw(3)<< y;
		}
		cout << endl;
	}
}
void circle_print(vector<vector<int>> &vec)
{
	int x = 0;
	int y = 0;
	int n = vec.size();
	int k = n;
	int dirx[] = {0,1,  0, -1};
	int diry[] = {1,0, -1, 0};
	int d = 0;
	
	while (k>0) {
		
		cout << setw(3) << vec[x][y];
		k--;
		//d = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < (i==3?k-1:k); j++) {
				x += dirx[d];
				y += diry[d];
				cout << setw(3) << vec[x][y];
			}
			d = (d + 1) % 4;
			if (i == 3) {
				x += dirx[d];
				y += diry[d];
			}
		}
		k--;
	}
	cout << endl;
}

void circle_build(vector<vector<int>> &vec)
{
	int x = 0;
	int y = 0;
	int n = vec.size();
	int k = n;
	int dirx[] = { 0,1,  0, -1 };
	int diry[] = { 1,0, -1, 0 };
	int d = 0;
	int cnt = 1;
	while (k>0) {
		vec[x][y] = cnt++;
		k--;
		//d = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < (i == 3 ? k - 1 : k); j++) {
				x += dirx[d];
				y += diry[d];
				vec[x][y] = cnt++;
			}
			d = (d + 1) % 4;
			if (i == 3) {
				x += dirx[d];
				y += diry[d];
			}
		}
		k--;
	}
	cout << endl;
}
void print_roate90(vector<vector<int>> &vec)
{
	int m = vec.size();
	int n = vec[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(3) << vec[m - j - 1][i];
		}
		cout << endl;
	}
}

void print_roate180(vector<vector<int>> &vec)
{
	int m = vec.size();
	int n = vec[0].size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(3) << vec[m-i-1][n-j-1];
		}
		cout << endl;
	}
}

void print_roate270(vector<vector<int>> &vec)
{
	int m = vec.size();
	int n = vec[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(3) << vec[j][n - i - 1];
		}
		cout << endl;
	}
}

int main()
{
	vector<vector<int>> vec;
	int n = 7;
	generate_matrix(vec, n,n);
	show_matrix(vec);
	cout << endl;
	circle_build(vec);
	circle_print(vec);
	show_matrix(vec);
	cout << endl;
	vector<vector<int>> vx;
	int m = 5;
	n = 7;
	generate_matrix(vx, m, n);
	show_matrix(vx);
	cout << endl;
	print_roate90(vx);
	cout << endl;

	print_roate180(vx);
	cout << endl;

	print_roate270(vx);
	cout << endl;
	return 0;
}