#include <iostream>
#include "ThreadPool.h"

int main() {
	using namespace toy;
	ThreadPool tp(3);
	std::mutex cntMutex;
	int cnt = 0;
	for (int i = 0; i < 20; ++i) {
		tp.add([&]() {
			for (int j = 0; j < 10000; ++j) {
				std::unique_lock<std::mutex> cntLock(cntMutex);
				++cnt;
			}
		});
	}
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cerr << cnt << std::endl;
	return 0;
}