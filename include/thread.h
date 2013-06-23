/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CPPUTIL_SRC_THREAD_H
#define CPPUTIL_SRC_THREAD_H

#include <pthread.h>

namespace cpputil {

class Thread {
	public:
		typedef pthread_t id_type;

		Thread();
			
		bool good() const;

		id_type id() const;
		void start();
		void detach();
		void join();

	protected:
		virtual void run() = 0;

	private:
		static void* start_helper(void* t);

		pthread_t id_;
		pthread_attr_t attr_;

		int error_;
};

inline Thread::Thread() {
	id_ = 0;
	error_ = pthread_attr_init(&attr_);
}

inline bool Thread::good() const {
	return error_ == 0;
}

inline Thread::id_type Thread::id() const {
	return id_;
}

inline void Thread::start() {
	error_ = pthread_create(&id_, &attr_, &start_helper, this);
}

inline void Thread::detach() {
	error_ = pthread_detach(id_);
}

inline void Thread::join() {
	error_ = pthread_join(id_, 0);
}

inline void* Thread::start_helper(void* t) {
	auto p = static_cast<Thread*>(t);
	p->run();

	return 0;
}

} // namespace cpputil

#endif
