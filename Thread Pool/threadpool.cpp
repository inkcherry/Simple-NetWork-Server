#include "threadpool.h"
Task ThreadPool::get_task() {
	std::unique_lock<std::mutex>lck{ mtx };
	cv.wait(lck, [this]() {return !tasks.empty(); });   //等待至有任务可取
	Task task{ std::move(tasks.front()) };              			
	tasks.pop();										//弹队首任务
	return task;
}

ThreadPool::ThreadPool(int number) :can_add_task(true)
{
	for (int i = 0; i < number; ++i)
	{
		pool.emplace_back(&ThreadPool::dispatch, this);
	}
}
ThreadPool::~ThreadPool()
{
	//禁止添加add task
	std::unique_lock<std::mutex> lock(mtx);
	can_add_task = false;


	for (auto &thread : pool)
	{
		thread.join();  //等待所有子线程执行结束
	}
}
void ThreadPool::dispatch()
{
	while (true) {
		if (Task task = get_task())
		{
			task();
		}
		else {
			return;
		}
	}
}
