#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
using Task = std::function<void()>;
class ThreadPool {
public:

	ThreadPool(int number=4);
	~ThreadPool();
	template<class F, class... Args>
	auto run_new_task(F&&f, Args&&...args)->std::future<decltype(f(args...))>;
	inline void set_tasks_states(const bool &can_add_task_) {if (can_add_task_==1) can_add_task.store(true);else { can_add_task.store(false); }};            //设置任务状态；
private:
	Task get_task();					//pop a task
	std::vector<std::thread> pool;      //线程池
	std::queue<Task> tasks;				//任务队列tasks
	std::atomic<bool> can_add_task;		//允许添加新任务标识（原子操作）
	std::condition_variable  cv;        //条件标志
	std::mutex mtx;						//互斥锁(用于任务的添加和移除）
	void dispatch();					//get task
};


template<class F, class... Args>
auto ThreadPool::run_new_task(F&&f, Args&&...args)->std::future<decltype(f(args...))> {
	if (can_add_task.load())    //ture
	{
		using ReturnType = decltype(f(args...));
		auto task = std::make_shared<std::packaged_task<ReturnType()>>(   //绑定参数，创建任务函数，智能指针管理
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);

		{    // 添加任务到队列
			std::lock_guard<std::mutex> lock{ mtx };
			tasks.emplace([task]() {     //添加任务
				(*task)();
			});
		}
		cv.notify_all();                //唤醒线程

		std::future<ReturnType> future = task->get_future();
		return future;

	}
	else
	{
		throw std::runtime_error("can not add new task");
	}
}



#endif