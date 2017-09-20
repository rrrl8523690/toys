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
#include <memory>
#include <queue>
#include <condition_variable>


namespace toy {
	// Current policy: assume that all jobs are added before the destruction of ThreadPool. When going to destruct ThreadPool, wait for all jobs to finish, and then reap all the threads.
	class ThreadPool {
	public:
		enum class DestructionMode {
			WAIT, TERMINATE, TERMINATE_ASYNC
		};

		ThreadPool(int nWorkers, DestructionMode mode = DestructionMode::WAIT);

		ThreadPool(const ThreadPool &other) = delete;

		ThreadPool(ThreadPool &&other) = delete;

		~ThreadPool();

		ThreadPool &operator=(const ThreadPool &other) = delete;

		ThreadPool &operator=(ThreadPool &&other) = delete;

		template<class Callable, class ...Args>
		std::future<typename std::result_of<Callable(Args...)>::type> addTask(Callable &&f, Args &&... args);

		void wait();

		void terminate(bool isAsync);


	private:
		void keepConsuming();

		const DestructionMode _destructionMode;
		bool _done;

		std::vector<std::thread> _workers;
		std::queue<std::function<void()>> _tasks;

		std::mutex _taskQueueMutex;
		std::condition_variable _taskChangedCV;

		std::condition_variable _noTodoTaskCV;

		bool _killingThreads;
	};

	template<class Callable, class ...Args>
	std::future<typename std::result_of<Callable(Args...)>::type> ThreadPool::addTask(Callable &&f, Args &&... args) {
		std::unique_lock<std::mutex> taskQueueLock(_taskQueueMutex);
		using result_type = typename std::result_of<Callable((Args...))>::type;
		auto tsk = std::bind(std::forward<Callable>(f), std::forward<Args>(args)...);
		auto task = std::make_shared<std::packaged_task<result_type()>>(std::packaged_task<result_type()>(tsk));
		auto result = task->get_future();
		_tasks.emplace([task]() { (*task)(); });
		_taskChangedCV.notify_one();
		return result;
	}
}


#endif //THREADPOOL_THREADPOOL_H
