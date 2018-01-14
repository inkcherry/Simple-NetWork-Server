#include "threadpool.h"
Task ThreadPool::get_task() {
	std::unique_lock<std::mutex>lck{ mtx };
	cv.wait(lck, [this]() {return !tasks.empty(); });   //�ȴ����������ȡ
	Task task{ std::move(tasks.front()) };              			
	tasks.pop();										//����������
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
	//��ֹ���add task
	std::unique_lock<std::mutex> lock(mtx);
	can_add_task = false;


	for (auto &thread : pool)
	{
		thread.join();  //�ȴ��������߳�ִ�н���
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
