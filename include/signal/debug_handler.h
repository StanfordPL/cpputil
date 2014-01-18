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

#ifndef CPPUTIL_INCLUDE_SIGNAL_DEBUG_HANDLER_H
#define CPPUTIL_INCLUDE_SIGNAL_DEBUG_HANDLER_H

#include <cassert>
#include <csignal>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string>
#include <sys/ucontext.h>
#include <unistd.h>

namespace cpputil {

class DebugHandler {
	public:
		static void install_sigsegv() {
			install(SIGSEGV, sigsegv);
		}

		static void install_sigill() {
			install(SIGILL, sigill);
		}

	private:
		typedef void (*handler_t)(int, siginfo_t*, void*);

		static void install(int signum, handler_t h) {
			struct sigaction sa;
			memset (&sa, '\0', sizeof(sa));
			sigfillset(&sa.sa_mask);
			sa.sa_sigaction = h;
			sa.sa_flags = SA_ONSTACK;

			assert(sigaction(signum, &sa, 0) >= 0);
		}

		static void print_quad(uint64_t val) {
			for ( int i = 7; i >=0; --i ) {
				std::cout << std::hex << std::noshowbase;
				std::cout	<< std::setfill('0') << std::setw(2);
				std::cout << (((uint64_t)val >> (i*8)) & 0x0ff) << " ";
			}
		}

		static void print_reg(const std::string& reg, uint64_t val) {
			std::cout << reg << " = ";
			print_quad(val);
			std::cout << std::endl;
		}

		static void print_mem(unsigned char* addr) {
			auto p = (uint64_t*)addr;
			std::cout << std::hex << std::showbase << std::setfill('0') << p << ": ";
			print_quad(*p);
			std::cout << std::endl;
		}

		static void print_cpu(void* context) {
			const auto regs = ((ucontext_t*)context)->uc_mcontext.gregs;

			std::cout << "Register Contents:" << std::endl;
			std::cout << std::endl;

			print_reg("%rip", regs[REG_RIP]); 
			print_reg("%rfl", regs[REG_EFL]);
			std::cout << std::endl;

			print_reg("%rax", regs[REG_RAX]);
			print_reg("%rdx", regs[REG_RDX]);
			print_reg("%rcx", regs[REG_RCX]);
			print_reg("%rbx", regs[REG_RBX]);
			print_reg("%rdi", regs[REG_RDI]);
			print_reg("%rsi", regs[REG_RSI]);
			print_reg("%rbp", regs[REG_RBP]);
			print_reg("%rsp", regs[REG_RSP]);
			print_reg("%r8 ", regs[REG_R8]); 
			print_reg("%r9 ", regs[REG_R9]); 
			print_reg("%r10", regs[REG_R10]);
			print_reg("%r11", regs[REG_R11]);
			print_reg("%r12", regs[REG_R12]);
			print_reg("%r13", regs[REG_R13]);
			print_reg("%r14", regs[REG_R14]);
			print_reg("%r15", regs[REG_R15]);
			std::cout << std::endl;

			const auto ip = (unsigned char*)regs[REG_RIP];
			if (ip == 0) {
				std::cout << "Unable to print memory in vicinity of %rip" << std::endl;
				exit(1);
			}

			std::cout << "Preceeding 64 bytes of %rip" << std::endl;
			std::cout << std::endl;

			for ( unsigned char* i = ip - 64; i < ip; i += 8 )
				print_mem(i);
			std::cout << std::endl;

			std::cout << "Next 128 bytes of %rip" << std::endl;
			std::cout << std::endl;

			for( unsigned char* i = ip; i < ip + 128; i += 8 )
				print_mem(i);
			std::cout << std::endl;
		}

		static void sigsegv(int sig, siginfo_t* siginfo, void* context) {
			std::cout << "SIGNAL: SIGSEGV" << std::endl;
			std::cout << std::endl;

			std::cout << "Address: ";
			std::cout << std::hex << std::showbase;
			std::cout	<< (uint64_t) siginfo->si_addr << std::endl;
			std::cout << "Cause: ";
			if (siginfo->si_code == SEGV_MAPERR)
				std::cout << "Address not mapped" << std::endl;
			else
				std::cout << "Bad permissions" << std::endl;
			std::cout << std::endl;

			print_cpu(context);
			exit(1);
		}

		static void sigill(int sig, siginfo_t* siginfo, void* context) {
			std::cout << "SIGNAL: SIGILL" << std::endl;
			std::cout << std::endl;

			std::cout << "Caused by: ";
			switch (siginfo->si_code) {
				case ILL_ILLOPC:
					std::cout << "Illegal opcode" << std::endl;
					break;
				case ILL_ILLOPN:
					std::cout << "Illegal operand" << std::endl;
					break;
				case ILL_ILLADR:
					std::cout << "Illegal addressing mode" << std::endl;
					break;
				case ILL_PRVOPC:
					std::cout << "Privileged opcode" << std::endl;
					break;
				case ILL_PRVREG:
					std::cout << "Privileged register" << std::endl;
					break;
				case ILL_COPROC:
					std::cout << "Coprocessor error" << std::endl;
					break;
				case ILL_BADSTK:
					std::cout << "Bad stack" << std::endl;
					break;
				default:
					std::cout << "<UNKNOWN>" << std::endl;
			}
			std::cout << std::endl;

			print_cpu(context);
			exit(1);
		}
};

} // namespace cpputil

#endif
