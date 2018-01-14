#include "threadpool.h"
#include <iostream>

int main()
{
	ThreadPool threadpool(5);
	std::vector<std::future<void>>funs;
	for (int i = 0; i < 10; i++)
	{
		funs.emplace_back(
			threadpool.run_new_task([i] {
			std::cout <<"I am "<< i << "\n";
		}));
	}

	std::cin.get();
	return 0;
}