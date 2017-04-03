#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
using namespace std;
#define HAS_MEMBER(member)\
template<typename T, typename ...Args> struct has_member_##member\
{\
private:\
	template<typename U> static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type());\
	template<typename U> static std::false_type Check(...);\
public:\
	enum{value = std::is_same<decltype(Check<T>(0)), std::true_type>::value};\
};

HAS_MEMBER(Before);
HAS_MEMBER(After);
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable &) = delete;
	NonCopyable(const NonCopyable &&) = delete;
	NonCopyable &operator=(const NonCopyable &) = delete;
	NonCopyable &operator=(const NonCopyable &&) = delete;
};

template<typename Func, typename ...Args>
struct Aspect :public NonCopyable
{
	Aspect(Func &f) :m_func(std::forward<Func>(f)) {}
	template<typename T>
	typename std::enable_if<has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type
	Invoke (Args && ...args, T &&aspect)
	{
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}

	template<typename T>
	typename std::enable_if<has_member_Before<T, Args...>::value && !has_member_After<T, Args...>::value>::type
		Invoke(Args && ...args, T &&aspect)
	{
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
	}

	template<typename T>
	typename std::enable_if<!has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type
		Invoke(Args && ...args, T &&aspect)
	{
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}

	template<typename Head, typename ...Tail>
	typename std::enable_if<has_member_Before<Head, Args...>::value && has_member_After<Head, Args...>::value>::type
	Invoke(Args && ...args, Head && headAspect, Tail && ... tailAspect)
	{
		headAspect.Before(std::forward<Args>(args)...);
		Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
		headAspect.After(std::forward<Args>(args)...);
	}

	template<typename Head, typename ...Tail>
	typename std::enable_if<has_member_Before<Head, Args...>::value && !has_member_After<Head, Args...>::value>::type
		Invoke(Args && ...args, Head && headAspect, Tail && ... tailAspect)
	{
		headAspect.Before(std::forward<Args>(args)...);
		Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
	}

	template<typename Head, typename ...Tail>
	typename std::enable_if<!has_member_Before<Head, Args...>::value && has_member_After<Head, Args...>::value>::type
		Invoke(Args && ...args, Head && headAspect, Tail && ... tailAspect)
	{
		Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
		headAspect.After(std::forward<Args>(args)...);
	}
private:
	Func m_func;
};

template<typename T> using identity_t = T;
template<typename ... AP, typename ...Args, typename Func>
void Invoke(Func &&f, Args &&...args)
{
	Aspect<Func, Args...> asp(std::forward<Func>(f));
	asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
}
struct EE
{
	void Before(int i)
	{
		cout << "Before from EE:" << i << endl;
	}
	void After(int i)
	{
		cout << "After from EE:" << i << endl;
	}
};
struct AA
{
	void Before(int i)
	{
		cout << "Before from AA:" << i << endl;
	}
	void After(int i)
	{
		cout << "After from AA:" << i << endl;
	}
};

struct CC
{
	void Before()
	{
		cout << "Before from CC:" << endl;
	}
	void After()
	{
		cout << "After from CC:"  << endl;
	}
};

struct DD
{
	void Before()
	{
		cout << "Before from DD:" << endl;
	}
	void After()
	{
		cout << "After from DD:" << endl;
	}
};


struct BB
{
	void Before(int i)
	{
		cout << "Before from BB:" << i << endl;
	}
	void After(int i)
	{
		cout << "After from BB:" << i << endl;
	}
};

void HT(int a)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << "real HT function:" << a << endl;
}
int GT(int a, int b)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1234));
	cout << "Real GT function:" << a << "+" << b << "=" << a + b << endl;
	return a + b;
}

class Timer
{
public:

	Timer() :m_begin(std::chrono::high_resolution_clock::now()) {}
	void reset() { m_begin = std::chrono::high_resolution_clock::now(); }
	template<typename Duration = std::chrono::milliseconds>
	int64_t elapsed()const
	{
		return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;

};
class TimeElapsedAspect
{
public:
	template<typename ...Args>
	void Before(Args ...args)
	{
		m_lastTime = static_cast<double>(m_t.elapsed());
	}

	template<typename ...Args>
	void After(Args ...args)
	{
		cout << "Time elapsed: " << (m_t.elapsed() - m_lastTime) / 1000.0 << " second(s)." << endl;
	}
private:
	double m_lastTime;
	Timer m_t;
};

class ParamPrint
{
public:
	template<typename T>
	void Before(T arg)
	{
		std::cout <<"Param: "<< arg << endl;
	}

	template<typename T, typename ...Args>
	void Before(T arg, Args ...args)
	{
		Before(std::forward<T>(arg));
		Before(std::forward<Args>(args)...);
	}
	
private:
	double m_lastTime;
	Timer m_t;
};

int main()
{
	int x = 5;
	//cin >> x;
	std::function<void(int)> f = std::bind(&HT, std::placeholders::_1);
	std::function<void(void)> f2 = std::bind(&HT, x);
	//Invoke<AA, BB>(std::function<void(int)>(std::bind(&HT, std::placeholders::_1)), 1);

	Invoke<TimeElapsedAspect,AA, BB, EE, ParamPrint>(f, 2);
	Invoke<TimeElapsedAspect>(f2);
	Invoke<TimeElapsedAspect, ParamPrint>(GT, 2, 4);
	Invoke<TimeElapsedAspect, ParamPrint>([](int n) { int x = 1; while (n--) x *= (n + 1); cout << x << endl; }, 10);
	return 0;
}