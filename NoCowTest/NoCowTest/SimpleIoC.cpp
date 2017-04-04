#include <iostream>
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <typeindex>
using namespace std;

class Any
{
public:
	Any(void):m_tpIndex(std::type_index(typeid(void))) {}
	Any(const Any &that):m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex){}
	Any(Any &&that):m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex){}
	template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
	Any(U &&value) : m_ptr(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),
		             m_tpIndex(type_index(typeid(typename std::decay<U>::type))) {}
	bool IsNull()const { return !bool(m_ptr); }
	template<class U> bool Is()const
	{
		return m_tpIndex == type_index(typeid(U));
	}
	template<class U>
	U &AnyCast()
	{
		if (!Is<U>())
		{
			std::cout << "can not cast" << typeid(U).name() << " to " << m_tpIndex.name() << endl;
			throw bad_cast();
		}
		auto derived = dynamic_cast<Derived<U> *>(m_ptr.get());
		return derived->m_value;
	}
	Any &operator=(const Any &a)
	{
		if (m_ptr == a.m_ptr)
			return *this;
		m_ptr = a.Clone();
		m_tpIndex = a.m_tpIndex;
		return *this;
	}
private:
	struct Base;
	typedef std::unique_ptr<Base> BasePtr;
	struct Base
	{
		virtual ~Base(){}
		virtual BasePtr Clone()const = 0;
	};
	template<typename T>
	struct Derived :Base
	{
		template<typename U>
		Derived(U &&value) :m_value(std::forward<U>(value)) {}
		virtual BasePtr Clone()const override
		{
			return BasePtr(new Derived<T>(m_value));
		}
		T m_value;
	};
	BasePtr Clone()const
	{
		if (m_ptr != nullptr)
			return m_ptr->Clone();
		else
			return nullptr;
	}
	BasePtr m_ptr;
	std::type_index  m_tpIndex;
};
void TestAny()
{
	Any n = 1.2;
	Any y = "Hello";
	Any x;
	cout << x.IsNull() << endl;
	x = 3432;
	cout << y.AnyCast<const char*>() << endl;
	cout << n.AnyCast<double>() << endl;

}

class NonCopyable
{
public:
	NonCopyable() {}
	virtual ~NonCopyable() {}
private:
	NonCopyable(const NonCopyable &) = delete;
	NonCopyable &operator=(const NonCopyable &) = delete;
};

class IocContainer :NonCopyable
{
public:
	IocContainer(void) {}
	~IocContainer(void) {}
	template<class T, typename Depend, typename ...Args>
	typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
		RegisterType(const string &strKey)
	{
		std::function<T*(Args ...)> function = [](Args ...args) {return new T(new Depend(args...));  };
		RegisterType(strKey, function);
	}

	template<class T, typename Depend, typename ...Args>
	typename std::enable_if<std::is_base_of<T, Depend>::value>::type
		RegisterType(const string &strKey)
	{
		std::function<T*(Args...)> function = [](Args ...args) {return new Depend(args...); };
		RegisterType(strKey, function);
	}

	template<class T, typename ...Args>
	void RegisterSimple(const string &strKey)
	{
		std::function<T*(Args...)> function = [](Args... args) {return new T(args...); };
		RegisterType(strKey, function);
	}

	template<class T, typename ...Args>
	T *Resolve(const string &strKey, Args ...args)
	{
		auto it = m_creatorMap.find(strKey);
		if (it == m_creatorMap.end())
			return nullptr;
		Any resolver = it->second;
		std::function<T*(Args...)> function = resolver.AnyCast<std::function<T*(Args...)>>();
		return function(args...);
	}

	template<class T, typename ...Args>
	std::shared_ptr<T> ResolveShared(const string &strKey, Args ...args)
	{
		T * t = Resolve<T>(strKey, args...);
		return std::shared_ptr<T>(t);
	}
private:
	void RegisterType(const string &strKey, Any constructor)
	{
		if (m_creatorMap.find(strKey) != m_creatorMap.end())
			throw std::invalid_argument("this key has already exist!");
		m_creatorMap.emplace(strKey, constructor);
	}
	unordered_map<string, Any> m_creatorMap;
};

struct IX
{
	virtual ~IX() {}
	virtual void g() = 0;
};
class X :public IX
{
public:
	void g()
	{
		std::cout << "It is a test in x" << std::endl;
	}
};

class Y :public IX
{
public:
	Y(int a) :m_a(a) {}
	void g()
	{
		std::cout << "It is a test in y" << std::endl;
	}
private:
	int m_a;
};

struct MyStructA
{
	MyStructA(IX *x) :m_x(x)
	{

	}
	~MyStructA()
	{
		if (m_x != nullptr)
		{
			delete m_x;
		}
	}
	void fun() { m_x->g(); }
private:
	IX *m_x;
};
void TestIoC()
{
	IocContainer ioc;
	ioc.RegisterType<MyStructA, X>("A");
	auto pa = ioc.ResolveShared<MyStructA>("A");
	pa->fun();

	ioc.RegisterType<MyStructA, Y, int>("A1");
	auto pa1 = ioc.ResolveShared<MyStructA>("A1", 23);
	pa1->fun();

}
int main()
{
	TestAny();
	TestIoC();
	return 0;
}