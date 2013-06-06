#ifndef CPPUTIL_SRC_THREAD_H
#define CPPUTIL_SRC_THREAD_H

#include <pthread.h>

namespace cpputil {

class Thread {
	public:
		typedef pthread_t id_type;

		Thread() {
			id_ = 0;
			error_ = pthread_attr_init(&attr_);
		}
			
		void detach() {
			error_ = pthread_detach(id_);
		}

		bool good() const {
			return error_ == 0;
		}

		id_type id() const {
			return id_;
		}

		void start() {
			error_ = pthread_create(&id_, &attr_, &start_helper, this);
		}

		void join() {
			error_ = pthread_join(id_, 0);
		}

	protected:
		virtual void run() = 0;

	private:
		static void* start_helper(void* t) {
			auto p = static_cast<Thread*>(t);
			p->run();

			return 0;
		}

		pthread_t id_;
		pthread_attr_t attr_;

		int error_;
};

} // namespace cpputil

#endif
