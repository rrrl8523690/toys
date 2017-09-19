#include <iostream>
#include "ThreadPool.h"
#include <atomic>


int main() {
	auto tp = new toy::ThreadPool(3, toy::ThreadPool::DestructionMode::WAIT);
	std::atomic<int> cnt(0);
	auto now = std::chrono::high_resolution_clock::now();
	std::vector<std::future<int> > results;
	for (int i = 0; i < 20000; ++i) {
		auto res = tp->addTask([&]() {
			for (int j = 0; j < 1000; ++j) {
				++cnt;
			}
			return cnt.load();
		});
		results.emplace_back(std::move(res));
	}
//	delete tp;
//	tp->wait();
//	tp->terminate(true);
	std::cerr << cnt << std::endl;
	auto duration = std::chrono::high_resolution_clock::now() - now;
	std::cerr << "Time consumed: " << (duration.count() * 1e-6) << "ms" << std::endl;
	delete tp;
	return 0;
}