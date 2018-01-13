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

	ThreadPool(int number) {};
	~ThreadPool() {};
	template<class F, class... Args>
	auto run_new_task(F&&f, Args&&...args)->std::future<decltype(f(args...))>;
	inline void set_tasks_states(const bool &can_add_task_) {if (can_add_task_==1) can_add_task.store(true);else { can_add_task.store(false); }};            //��������״̬��
private:
	std::vector<std::thread> pool;      //�̳߳�
	std::queue<Task> tasks;				//�������
	std::atomic<bool> can_add_task;		//��������������ʶ��ԭ�Ӳ�����

};

#endif