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
	inline void set_tasks_states(const bool &can_add_task_) {if (can_add_task_==1) can_add_task.store(true);else { can_add_task.store(false); }};            //��������״̬��
private:
	Task get_task();					//pop a task
	std::vector<std::thread> pool;      //�̳߳�
	std::queue<Task> tasks;				//�������tasks
	std::atomic<bool> can_add_task;		//��������������ʶ��ԭ�Ӳ�����
	std::condition_variable  cv;        //������־
	std::mutex mtx;						//������(�����������Ӻ��Ƴ���
	void dispatch();					//get task
};


template<class F, class... Args>
auto ThreadPool::run_new_task(F&&f, Args&&...args)->std::future<decltype(f(args...))> {
	if (can_add_task.load())    //ture
	{
		using ReturnType = decltype(f(args...));
		auto task = std::make_shared<std::packaged_task<ReturnType()>>(   //�󶨲���������������������ָ�����
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);

		{    // ������񵽶���
			std::lock_guard<std::mutex> lock{ mtx };
			tasks.emplace([task]() {     //�������
				(*task)();
			});
		}
		cv.notify_all();                //�����߳�

		std::future<ReturnType> future = task->get_future();
		return future;

	}
	else
	{
		throw std::runtime_error("can not add new task");
	}
}



#endif