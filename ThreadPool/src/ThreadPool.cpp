//
// Created by Handa Wang on 9/15/17.
//

#include <iostream>
#include <future>
#include "ThreadPool.h"

namespace toy {
	ThreadPool::ThreadPool(int nWorkers, DestructionMode mode)
					: _nTodoTasks(0), _killingThreads(false), _destructionMode(mode) {
		for (int i = 0; i < nWorkers; ++i) {
			std::function<void()> func = std::bind(&ThreadPool::keepConsuming, this);
			_workers.emplace_back(func);
		}
	}

	ThreadPool::~ThreadPool() {
		if (_destructionMode == DestructionMode::WAIT) {
			std::unique_lock<std::mutex> nTodoTasksLock(_nTodoTasksMutex);
			_noTodoTask.wait(nTodoTasksLock, [&]() {
				return !_nTodoTasks;
			});
		}
		{
			std::unique_lock<std::mutex> taskQueueLock(_taskQueueMutex);
			_killingThreads = true;
		}
		_taskChangedCV.notify_all();
		if (_destructionMode == DestructionMode::WAIT || _destructionMode == DestructionMode::TERMINATE) {
			for (auto &worker : _workers) {
				worker.join();
			}
		}
	}


	void ThreadPool::keepConsuming() {
		while (true) {
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> taskQueueLock(_taskQueueMutex);
				_taskChangedCV.wait(taskQueueLock, [&]() {
					return !_tasks.empty() || _killingThreads;
				});
				if (_killingThreads) {
					break;
				} else {
					task = std::move(_tasks.front());
					_tasks.pop();
				}
			}
			task();
			{
				std::unique_lock<std::mutex> nRunningTasksLock(_nTodoTasksMutex);
				--_nTodoTasks;
				if (!_nTodoTasks) {
					_noTodoTask.notify_all();
				}
			}
		}
	}
}

