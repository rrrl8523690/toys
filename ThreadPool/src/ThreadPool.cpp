//
// Created by Handa Wang on 9/15/17.
//

#include "ThreadPool.h"

namespace toy {
	ThreadPool::ThreadPool(int nWorkers) : _nTodoTasks(0) {
		for (int i = 0; i < nWorkers; ++i) {
			std::function<void()> func = std::bind(&ThreadPool::keepConsuming, this);
			_workers.emplace_back(func);
		}
	}

	ThreadPool::~ThreadPool() {
		std::unique_lock<std::mutex> allTaskDoneLock(_nTodoTasksMutex);
		_noTodoTask.wait(allTaskDoneLock, [&]() {
			return !_nTodoTasks;
		});
	}

	void ThreadPool::keepConsuming() {
		while (true) {
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> taskQueueLock(_taskQueueMutex);
				_hasNewTask.wait(taskQueueLock, [&]() {
					return !_tasks.empty();
				});
				task = _tasks.front();
				_tasks.pop();
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

	void ThreadPool::add(std::function<void()> task) {
		std::unique_lock<std::mutex> taskQueueLock(_taskQueueMutex);
		std::unique_lock<std::mutex> nTodoTasksLock(_nTodoTasksMutex);
		_tasks.emplace(move(task));
		++_nTodoTasks;
	}
}

