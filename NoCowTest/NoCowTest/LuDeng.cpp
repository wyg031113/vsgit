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
		for (int i = 0; i < N; i++) { //��ȡ���ݣ�������ֵ��Сֵ��
			int x;
			cin >> x;
			vec.push_back(x);
			max_min_node(nd, x);
		}

		double maxdiff = 0;
		int diff = nd.b - nd.a;
		if (diff) {//����һ����
			for (int i = 0; i < vec.size(); i++) {
				//N���Ʒŵ�N+1��Ͱ�У���Ȼ��һ����Ͱ��
				//vec[i]�ڵ�vec[i]/(diff/N)��Ͱ�У�һ��Ͱ�п����ж��Ԫ�أ���ֻ�������ֵ����Сֵ��
				
				int k = N * ((vec[i] - nd.a) *1.0 / diff); 
				max_min_node(t[k], vec[i]);
			}// end for

			//һ��Ͱ�е�Ԫ������ᳬ��diff/N�����ڱ�Ȼ��һ����Ͱ�����߿����ж����Ͱ������
			//��Ͱ���˵�Ԫ�ز��Ȼ>=diff/N,����ֻҪ�ҵ�������Ͱ��������ֵ
			bool bz = false; //һ��ʼ��Ϊ��Ͱ����pre=0�պá�������(nd.a - 0)/2
			int pre = 0;
			for (int i = 0; i <= N; i++) {
				if (t[i].flag) {//�����ǿ�Ͱ
					if (!bz) {//�ɿ�Ͱ�䵽�˷ǿ�Ͱ��
						maxdiff = std::max(maxdiff, (t[i].a - t[pre].b)*1.0);
						bz = true;
					}
					pre = i;  //��һ���ǿ�Ͱ
				}else {
					bz = false; //������Ͱ
				}
			}//end for
			
		}//end if
		maxdiff = max(maxdiff / 2.0, 1.0*max(nd.a, L - nd.b)); //nd.a -0, L - nd.b,�����ǲ��ó�2�ġ�
		printf("%.2f\n", maxdiff);
	}//end while
	return 0;
}