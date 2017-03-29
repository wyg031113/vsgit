#pragma once
#include <queue>
namespace objpool
{
	template<class T> class ObjectPool
	{
	public:
		ObjectPool(int sz);
		T *alloc();
		void free(T *obj);
	private:
		unsigned size;
		std::queue<T*> free_objs;
	};

	template<class T> ObjectPool<T>::ObjectPool(int sz) :
		size(sz), free_objs()
	{
		if (size <= 0)
			throw logic_error("Bad Object Pool Size.");
	}
	template<class T> T* ObjectPool<T>::alloc() 
	{
		if (free_objs.size() > 0) {
			T *t = free_objs.front();
			free_objs.pop();
			return t;
		}
		else {
			return new T;
		}
	}
		
	template<class T> void ObjectPool<T>::free(T* obj)
	{
		if (free_objs.size() == size)
			delete obj;
		else
			free_objs.push(obj);
	}
}