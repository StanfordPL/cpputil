// Copyright 2014 eric schkufza
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPPUTIL_INCLUDE_SIGNAL_SIG_HANDLER_H
#define CPPUTIL_INCLUDE_SIGNAL_SIG_HANDLER_H

#include <cassert>
#include <csignal>
#include <cstring>
#include <signal.h>
#include <sys/ucontext.h>
#include <unistd.h>

namespace cpputil {

class SigHandler {
	public:
		virtual ~SigHandler() { }

		void install_sigsegv() {
			const auto raise = [](int sig, siginfo_t* si, void* context) { 
				((SigHandler*) context)->handle_sigsegv(sig, si);
			};
			install(SIGSEGV, raise, (void*) this);
		}

		void install_sigill() {
			const auto raise = [](int sig, siginfo_t* si, void* context) { 
				((SigHandler*) context)->handle_sigill(sig, si);
			};
			install(SIGILL, raise, (void*) this);
		}

	protected:
		virtual int handle_sigsegv(int sig, siginfo_t* siginfo) = 0;
		virtual int handle_sigill(int sig, siginfo_t* siginfo) = 0;

	private:
		typedef void (*handler_t)(int, siginfo_t *, void *);

		void install(int signum, handler_t h, void* context) {
			struct sigaction sa;
			memset (&sa, '\0', sizeof(sa));
			sigfillset(&sa.sa_mask);
			sa.sa_sigaction = h;
			sa.sa_flags = SA_ONSTACK;

			assert(sigaction(signum, &sa, context) >= 0);
		}
};

} // namespace cpputil 

#endif
