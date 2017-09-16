//
// Created by Handa Wang on 9/15/17.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <queue>
#include <condition_variable>


namespace toy {
	class ThreadPool {
	public:
		ThreadPool(int nWorkers);

		~ThreadPool();

		// TODO: support more types of tasks
		void addTask(std::function<void()> task);

		// TODO: add wait() method to wait all jobs to be done
	private:
		void keepConsuming();

		std::vector<std::thread> _workers;
		std::queue<std::function<void()>> _tasks;
		std::mutex _taskQueueMutex;
		std::condition_variable _hasNewTask;
		int _nTodoTasks;
		std::mutex _nTodoTasksMutex;
		std::condition_variable _noTodoTask;
	};
}

#endif //THREADPOOL_THREADPOOL_H
