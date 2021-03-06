#include <iostream>
#include "ThreadPool.h"
#include <atomic>


int main() {
	auto tp = new toy::ThreadPool(3, toy::ThreadPool::DestructionMode::WAIT);
	std::atomic<int> cnt(0);
	auto now = std::chrono::high_resolution_clock::now();
	std::vector<std::future<int>> results;
	std::vector<std::thread> ts;
	for (int i = 0; i < 20000; ++i) {
//		ts.emplace_back([&]() {
//			for (int j = 0; j < 1000; ++j) {
//				++cnt;
//			}
//			return cnt.load();
//		});
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
//	tp->terminate(false);
	std::cerr << cnt << std::endl;
	delete tp;
	auto duration = std::chrono::high_resolution_clock::now() - now;
	std::cerr << "Time consumed: " << (duration.count() * 1e-6) << "ms" << std::endl;
	return 0;
}