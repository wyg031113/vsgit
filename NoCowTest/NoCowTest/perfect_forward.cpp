#include <iostream>
#include <algorithm>
#include <type_traits>
#include <memory>
#include <thread>
#include <cstdio>
#include <vector>
#include <mutex>
#include <queue>
#include <string>
#include <atomic>
#include <condition_variable>
#include <future>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;
queue<std::function<void()>>tasks;
int i = 0;
std::mutex mtx;
std::condition_variable_any cond;
//int ntasks = 0;
std::atomic<int> ntasks = 0;
void thread_fun(int x)
{
	while (1) {
		std::lock_guard<std::mutex> locker(mtx);
		printf("thread %d goto sleep.\n", x);
		cond.wait(mtx, []() {return ntasks > 0; });
		auto fun = tasks.front();
		tasks.pop();
		--ntasks;
		printf("thread %d get tasks.\n", i);
		fun();
	}
}
void submit(function<void()> f) 
{
	//std::lock_guard<std::mutex> locker(mtx);
	tasks.push(f);
	++ntasks;
	cond.notify_all();
}
void add(int a, int b)
{
	std::cout << a << "+" << b << "=" << a + b << endl;
}
int mul(int a, int b)
{
	std::this_thread::sleep_for(std::chrono::seconds(4));
	return a*b;
}
void test_future()
{
	std::future_status status;
	std::packaged_task<int(int, int)>task(mul);
	std::future<int> future = task.get_future();
	std::thread(std::move(task), 3, 5).detach();
	
	do {
		status = future.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred)
			std::cout << "task deferred\n";
		else if (status == std::future_status::timeout)
			cout << "future wait timed out.\n";
		else if (status == std::future_status::ready)
			cout << "task finished ret:" << future.get() << endl;
	} while (status != std::future_status::ready);
}
int main()
{
	auto t = chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	cout << std::atoi("234") << endl;
	string s = R"(C:\abcdefg)";
	cout << s << endl;
	std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %X") << endl;
	test_future();
	vector<thread> thrds;
	for (int i = 0; i < 3; i++)
		thrds.emplace_back(thread_fun,i);
	submit([]() {std::cout << "hello world" << endl; });
	submit(std::bind(add, 3,4));
	for (auto &th : thrds)
		th.join();

	return 0;
}