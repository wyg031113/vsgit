#include <iostream>
#include <vector>
#include <memory>
#include <queue>
using namespace std;

template<typename T>
class Tree {
public:
	template<typename T>
	struct TreeNode
	{
		TreeNode<T> *left = NULL;
		TreeNode<T> *right = NULL;
		T val;
	};
	void build(void)
	{
		k = 0;
		dfs_destroy(root);
		dfs_build(root, 0, middle.size() - 1);
		print_tree(root);
	}
	void set_first_middle(vector<T> &f, vector<T> &m) 
	{
		cout << "left ref" << endl;
		first = f;
		middle = m;
	}
	void set_first_middle(vector<T> &&f, vector<T> &&m)
	{
		cout << "right ref" << endl;
		first = std::move(f);
		middle = std::move(m);
	}
	void dfs_build(TreeNode<T> *&root,  int L, int R)
	{
		if (k == first.size() || L > R) {
			root = NULL;
			return;
		}
		root = new TreeNode<T>;
		root->val = first[k];
		int i;
		for (i = L; i <= R; i++)
			if (middle[i] == first[k])
				break;
		k++;
		dfs_build(root->left, L, i - 1);
		dfs_build(root->right, i + 1, R);
	}

	void print_tree(const TreeNode<T> *root)
	{
		if (root == NULL)
			return;
		queue<const TreeNode<T>*> Q;
		Q.push(root);
		while (!Q.empty()) {
			auto pnd = Q.front();
			Q.pop();
			std::cout << pnd->val << " ";
			if (pnd->left)
				Q.push(pnd->left);
			if (pnd->right)
				Q.push(pnd->right);
		}
		std::cout << endl;
	}
	void dfs_destroy(TreeNode<T> *&root)
	{
		if (root == NULL)
			return;
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
			return;
		}
		if(root->left)
			dfs_destroy(root->left);
		if(root->right)
			dfs_destroy(root->right);
		//root = NULL;
	}
	~Tree()
	{
		dfs_destroy(root);
	}
private:
	vector<T> first;
	vector<T> middle;
	int k = 0;
	TreeNode<T> *root = NULL;
};
template<int N>
struct int_
{
	static const int value = N;
};

template<int a, int b, int c, int d, int e, int f, int g>
struct vec_int
{
	static const int v0 = a;
	static const int v1 = b;
	static const int v2 = c;
	static const int v3 = d;
	static const int v4 = e;
	static const int v5 = f;
	static const int v6 = g;
};
template<typename T, typename U>
struct vec_equal
{
	static const bool value = (T::v0 == U::v0) &&
		(T::v1 == U::v1) &&
		(T::v2 == U::v2) &&
		(T::v3 == U::v3) &&
		(T::v4 == U::v4) &&
		(T::v5 == U::v5) &&
		(T::v6 == U::v6);
};
template<typename T, typename U>
struct vec_plus
{
	static const int v0 = T::v0 + U::v0;
	static const int v1 = T::v1 + U::v1;
	static const int v2 = T::v2 + U::v2;
	static const int v3 = T::v3 + U::v3;
	static const int v4 = T::v4 + U::v4;
	static const int v5 = T::v5 + U::v5;
	static const int v6 = T::v6 + U::v6;
};

template<typename T, typename U>
struct vec_minus
{
	static const int v0 = T::v0 - U::v0;
	static const int v1 = T::v1 - U::v1;
	static const int v2 = T::v2 - U::v2;
	static const int v3 = T::v3 - U::v3;
	static const int v4 = T::v4 - U::v4;
	static const int v5 = T::v5 - U::v5;
	static const int v6 = T::v6 - U::v6;
};

typedef vec_int<1, 0, 0, 0, 0, 0, 0> mass;
typedef vec_int<0, 1, 0, 0, 0, 0, 0> length;
typedef vec_int<0, 0, 1, 0, 0, 0, 0> time;
typedef vec_int<0, 0, 0, 1, 0, 0, 0> charge;
typedef vec_int<0, 0, 0, 0, 1, 0, 0> temperature;
typedef vec_int<0, 0, 0, 0, 0, 1, 0> intensity;
typedef vec_int<0, 0, 0, 0, 0, 0, 1> amount_of_substance;

typedef vec_int<0, 1, -1, 0, 0, 0, 0> velocity;
typedef vec_int<0, 1, -2, 0, 0, 0, 0> acceleration;
typedef vec_int<1, 1, -1, 0, 0, 0, 0> momentum;
typedef vec_int<1, 1, -2, 0, 0, 0, 0> force;
typedef vec_int<0, 0,  0, 0, 0, 0, 0> scalar;

template<class T, class Dimesions>
struct quantity
{
	using value_type = T;
	using dim_type = Dimesions;
	explicit quantity(T x) :m_value(x) {}
	T value()const { return m_value; }
	template<class D>
	quantity(const quantity<T, D> &rhs)
	{
		static_assert(vec_equal<dim_type, D>::value, "Bad construct quantity, type not equal");
		this->m_value = rhs.value();
	}
	template<class D>
	quantity<value_type, D> &operator=(const quantity<T,D> &rhs)
	{
		static_assert(vec_equal<dim_type, D>::value, "Bad assign quantity, type not equal");
		this->m_value = rhs.value();
		return *this;
	}

	template<class D>
	bool operator==(const quantity<T, D> &rhs)
	{
		static_assert(vec_equal<dim_type, D>::value, "Bad compare quantity, type not equal");
		return fabs(this->m_value - rhs.value()) < 1e-6;
	}

private:
	T m_value;

};
template<class T, class D>
quantity<T, D> operator+(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() + y.value());
}
template<class T, class D>
quantity<T, D> operator-(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() - y.value());
}

template<class T, class D1, class D2>
quantity<T, vec_plus<D1, D2>> operator*(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, vec_plus<D1, D2>>(x.value() * y.value());
}

template<class T, class D1, class D2>
quantity<T, vec_minus<D1, D2>> operator/(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, vec_minus<D1, D2>>(x.value() / y.value());
}

template<typename T>
void print_vec()
{
	cout << T::v0 << " "
		<< T::v1 << " "
		<< T::v2 << " "
		<< T::v3 << " "
		<< T::v4 << " "
		<< T::v5 << " "
		<< T::v6 << endl;
}
int main(int argc, char *argv[])
{
	int x = 4;
	int y = 6;
	vector<int> firstRoot = {1,2,4,5,8,3,6,9,7};
	vector<int> middleRoot = {4,2,8,5,1,6,9,3,7};
	Tree<int> tree;
	tree.set_first_middle(std::move(firstRoot), std::move(middleRoot));
	//tree.set_first_middle(firstRoot, middleRoot);
	tree.build();

	cout << int_<45>::value << endl;
	quantity<double, length> L(1.0);
	quantity<double, mass> m(2.0);
	quantity<double, acceleration> a(9.8);
	 
	quantity<double, force> f = m*a;
	auto xx = m*a*L;
	quantity<double, force> f2(0);
	f2 = f;
	print_vec<decltype(xx)::dim_type>();
	cout << vec_equal<force, decltype(f)::dim_type>::value << endl;
	
	return 0;
}