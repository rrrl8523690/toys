#include <iostream>
#include "ThreadPool.h"

int main() {
	using namespace toy;
	auto tp = new ThreadPool(3);
	std::mutex cntMutex;
	int cnt = 0;
	for (int i = 0; i < 200; ++i) {
		tp->addTask([&]() {
			for (int j = 0; j < 10000; ++j) {
				std::unique_lock<std::mutex> cntLock(cntMutex);
				++cnt;
			}
		});
	}
	delete tp;
	std::cerr << cnt << std::endl;
	return 0;
}