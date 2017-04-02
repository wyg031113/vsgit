#include <iostream>
#include <exception>
#include <functional>
#include <vector>
#include <algorithm>
#include <tuple>
namespace detail_range
{
	template<typename T> 
	class iterator
	{
	public:
		using value_type = T;
		using size_type = size_t;
		iterator(const size_type sz, const value_type val, const value_type step) :
			cursor_(sz), value_(val), step_(step)
		{
			value_ += cursor_ * step_;
		}
		iterator &operator++(void)
		{
			++cursor_;
			value_ += step_;
			return *this;
		}
		const value_type operator*()const
		{
			return value_;
		}
		bool operator != (const iterator &rhs)
		{
			return cursor_ != rhs.cursor_;
		}
	private:
		size_type cursor_;
		const value_type step_;
		value_type	value_;
	};

	template<typename T>
	class impl
	{
	public:
		using value_type = T;
		using reference = const value_type &;
		using const_reference = const value_type &;
		using iterator = const iterator<value_type>;
		using const_iterator = const detail_range::iterator<value_type>;
		using size_type = typename detail_range::iterator<value_type>::size_type;
		impl(value_type start, value_type end, value_type step) :
			 start_(start), end_(end), step_(step)
		{
			if (start_ < end_ && step_ < 0)
				throw std::logic_error("Bad range, step must be greater than 0");
			if (start_ > end_ && step_ > 0)
				throw std::logic_error("Bad range, step must be less than 0");
			size_type sz = static_cast<size_type>((end_ - start_) / step_);
			if (sz * step_ != end_ - start_)
				++sz;
			max_count_ = sz;
		}
		detail_range::iterator<value_type> begin()
		{
			return{ 0, start_, step_ };
		}
		detail_range::iterator<value_type> end()
		{
			return detail_range::iterator<value_type>(max_count_, start_, step_);
		}
	private:
		value_type start_;
		value_type end_;
		value_type step_;
		size_type max_count_;
	};

	template<typename T, typename D, typename U>
	auto range(T begin, D end, U step)->impl<decltype(begin + step + end)>
	{
		using r_t = impl<decltype(begin + step + end)>;
		return r_t(begin, end, step);
	}

	template<typename T, typename D>
	auto range(T begin, D end)->impl<decltype(begin + end + 1)>
	{
		using r_t = impl<decltype(begin + end + 1)>;
		if (begin < end)
			return r_t(begin, end, 1);
		else
			return r_t(begin, end, -1);
	}

	template<typename T>
	impl<T> range(T n)
	{
		return{ 0, n,1 };
	}
}
void fun(int &x, std::function<void(int &)> f)
{
	f(x);
}
void inc(int &x)
{
	++x;
}
void out(int &x)
{
	std::cout << x << std::endl;
}
template<typename T>
void print(std::initializer_list<T> it)
{
	for (auto i :it)
		std::cout << i << " ";
	std::cout << std::endl;
}

template<typename T>
void print(std::vector<T> vec)
{
	for (auto i : vec)
		std::cout << i << " ";
	std::cout << std::endl;
}

std::tuple<double, double> calc(double r)
{
	double PI = 3.141592653;
	double C = 2 * PI * r;
	double S = PI * r * r;
	return std::make_tuple(C, S);
}
class A
{
public:
	A(int a = 1) :a_(a) {}
	A(const A &b) {
		a_ = b.a_;
		std::cout << "COPY" << std::endl;
	}
	A &operator=(const A &b) {
		a_ = b.a_;
		std::cout << "COPY=" << std::endl;
		return *this;
	}
	void show()
	{
		[=]() mutable {std::cout << "a_=" << this->a_++ << std::endl; }();
		std::cout << this->a_ << std::endl;
	}
private:
	int a_;
};
int main()
{
	using detail_range::range;
	for (auto x : range(20.2, 10))
		std::cout << x << " ";
	std::cout << std::endl;

	int x = 6;
	fun(x, inc);
	fun(x, out);
	auto ff = std::bind(fun, std::placeholders::_1, inc);
	ff(x);
	fun(x, [](int &y)->void {y *= y; });
	[&]() mutable{++x; }();
	fun(x, out);
	std::initializer_list<int> ite = { 1,3,5,45,234 };
	print(ite);
	print({"Hello", "world"});
	std::vector<int> vec{23, -234, 34, 55, 7, 22, 10 };
	sort(vec.begin(), vec.end(), [](const int &a, const int &b)->bool {return a > b; });
	for (auto y : vec)
		std::cout << y << " ";
	std::cout << std::endl;
	std::vector<int> ans;
	std::cout << "count(5<X<30)=" 
		      << std::count_if(vec.begin(), vec.end(),
				  [&ans](int x)->bool {if (x > 5 && x < 30) { ans.push_back(x); return true; }
									     else return false; }
				  )
		     << std::endl;
	print(ans);
	double C, S;
	std::tie(C, S) = calc(6);
	std::cout << "C=" << C << ", S=" << S << std::endl;
	A ax(234);
	ax.show();

	int &&i = 0;
	i = 3;
	int &j = i;
	int &&k = std::move(j);
	return 0;
}