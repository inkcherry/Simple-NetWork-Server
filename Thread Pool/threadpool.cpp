#include "threadpool.h"
template<class F, class... Args>
auto ThreadPool::run_new_task(F&&f, Args&&...args)->std::future<decltype(f(args...))>{

}
