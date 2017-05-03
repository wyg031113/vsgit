#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
struct Node
{
	int a = 0;
	int b = 0;
	bool flag = false;
};
void max_min_node(Node &nd, int x)
{
	if (nd.flag) {
		nd.a = min(nd.a, x);
		nd.b = max(nd.b, x);

	}
	else {
		nd.flag = true;
		nd.a = nd.b = x;
	}
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int N, L;
	while (cin >> N >> L) {
		Node nd;
		vector<int> vec;
		vector<Node> t(1001, Node());
		for (int i = 0; i < N; i++) { //读取数据，获得最大值最小值。
			int x;
			cin >> x;
			vec.push_back(x);
			max_min_node(nd, x);
		}

		double maxdiff = 0;
		int diff = nd.b - nd.a;
		if (diff) {//多于一个灯
			for (int i = 0; i < vec.size(); i++) {
				//N个灯放到N+1个桶中，必然有一个空桶。
				//vec[i]在第vec[i]/(diff/N)个桶中，一个桶中可以有多个元素，但只保留最大值和最小值。
				
				int k = N * ((vec[i] - nd.a) *1.0 / diff); 
				max_min_node(t[k], vec[i]);
			}// end for

			//一个桶中的元素最大差不会超过diff/N。由于必然有一个空桶，或者可能有多个空桶，所以
			//空桶两端的元素差必然>=diff/N,所以只要找到连续空桶两端最大差值
			bool bz = false; //一开始认为空桶，且pre=0刚好。可能算(nd.a - 0)/2
			int pre = 0;
			for (int i = 0; i <= N; i++) {
				if (t[i].flag) {//遇到非空桶
					if (!bz) {//由空桶变到了非空桶，
						maxdiff = std::max(maxdiff, (t[i].a - t[pre].b)*1.0);
						bz = true;
					}
					pre = i;  //上一个非空桶
				}else {
					bz = false; //遇到空桶
				}
			}//end for
			
		}//end if
		maxdiff = max(maxdiff / 2.0, 1.0*max(nd.a, L - nd.b)); //nd.a -0, L - nd.b,两端是不用除2的。
		printf("%.2f\n", maxdiff);
	}//end while
	return 0;
}