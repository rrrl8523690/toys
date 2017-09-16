#include <iostream>
#include "ThreadPool.h"
#include <atomic>

int main() {
	using namespace toy;
	auto tp = new ThreadPool(3);
	std::atomic<int> cnt(0);
	auto now = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 20000; ++i) {
		tp->addTask([&]() {
			for (int j = 0; j < 1000; ++j) {
				++cnt;
			}
		});
	}
	delete tp;
	std::cerr << cnt << std::endl;
	auto duration = std::chrono::high_resolution_clock::now() - now;
	std::cerr << "Time consumed: " << (duration.count() * 1e-6) << "ms" << std::endl;
	return 0;
}