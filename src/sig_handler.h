#ifndef CPPUTIL_SRC_SIG_HANDLER_H
#define CPPUTIL_SRC_SIG_HANDLER_H

#include <csignal>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sys/ucontext.h>
#include <unistd.h>

namespace cpputil {

class VerboseSegvHandler {
	public:
		static void install();

	private:
		static void handler(int sig, siginfo_t* siginfo, void* arg);
};

class VerboseIllHandler {
	public:
		static void install(std::ostream& os);

	private:
		static void handler(int sig, siginfo_t* siginfo, void* arg);
};

inline void VerboseSegvHandler::install() {
	struct sigaction segv;
	memset (&segv, '\0', sizeof(segv));
	sigfillset(&segv.sa_mask);
	segv.sa_sigaction = &handler;
	segv.sa_flags = SA_ONSTACK;

	if (sigaction(SIGSEGV, &segv, 0) < 0) {
		std::cout << "FATAL ERROR: Unable to register signal handler!" << std::endl;
		exit(1);
	}
}

inline void VerboseSegvHandler::handler(int sig, siginfo_t* siginfo, void* arg) {
	std::cout << "SIGSEGV" << std::endl;
	std::cout << std::endl;

	std::cout << "Address: ";
	std::cout << std::hex << std::showbase << (uint64_t) siginfo->si_addr << std::endl;
	std::cout << "Cause:   ";
	if (siginfo->si_code == SEGV_MAPERR)
		std::cout << "Address not mapped" << std::endl;
	else
		std::cout << "Bad permissions" << std::endl;
	std::cout << std::endl;

	const auto regs = ((ucontext_t*)arg)->uc_mcontext.gregs;
	const auto ip = (unsigned char*)regs[REG_RIP];

	std::cout << "\nRegister Status\n" << std::endl;
	std::cout << "%rip = " << std::showbase << std::hex << (uint64_t)ip << std::endl;
	std::cout << "%rax = " << std::showbase << std::hex << (uint64_t)regs[REG_RAX] << std::endl;
	std::cout << "%rdx = " << std::showbase << std::hex << (uint64_t)regs[REG_RDX] << std::endl;
	std::cout << "%rcx = " << std::showbase << std::hex << (uint64_t)regs[REG_RCX] << std::endl;
	std::cout << "%rbx = " << std::showbase << std::hex << (uint64_t)regs[REG_RBX] << std::endl;
	std::cout << "%rdi = " << std::showbase << std::hex << (uint64_t)regs[REG_RDI] << std::endl;
	std::cout << "%rsi = " << std::showbase << std::hex << (uint64_t)regs[REG_RSI] << std::endl;
	std::cout << "%rbp = " << std::showbase << std::hex << (uint64_t)regs[REG_RBP] << std::endl;
	std::cout << "%rsp = " << std::showbase << std::hex << (uint64_t)regs[REG_RSP] << std::endl;
	std::cout << "%rip = " << std::showbase << std::hex << (uint64_t)regs[REG_RIP] << std::endl;
	std::cout << "%r8  = " << std::showbase << std::hex << (uint64_t)regs[REG_R8] << std::endl;
	std::cout << "%r9  = " << std::showbase << std::hex << (uint64_t)regs[REG_R9] << std::endl;
	std::cout << "%r10 = " << std::showbase << std::hex << (uint64_t)regs[REG_R10] << std::endl;
	std::cout << "%r11 = " << std::showbase << std::hex << (uint64_t)regs[REG_R11] << std::endl;
	std::cout << "%r12 = " << std::showbase << std::hex << (uint64_t)regs[REG_R12] << std::endl;
	std::cout << "%r13 = " << std::showbase << std::hex << (uint64_t)regs[REG_R13] << std::endl;
	std::cout << "%r14 = " << std::showbase << std::hex << (uint64_t)regs[REG_R14] << std::endl;
	std::cout << "%r15 = " << std::showbase << std::hex << (uint64_t)regs[REG_R15] << std::endl;
	std::cout << "%rfl = " << std::showbase << std::hex << (uint64_t)regs[REG_EFL] << std::endl;
	std::cout << std::endl;

	if (ip == 0) {
		std::cout << "Unable to print memory in vicinity of %rip" << std::endl;
		exit(1);
	}

	std::cout << "Preceeding 64 bytes of %rip" << std::endl;
	int count = 0; 

	for ( unsigned char* i = ip - 64; i < ip; ++i ) {
		if (count++ % 8 == 0)
			std::cout << std::endl << std::hex << std::setfill('0') << std::showbase << (uint64_t)i << ": ";
		std::cout << std::hex << std::setw(2) << std::setfill('0') << std::showbase << (uint16_t)*i << " ";
		std::cout.flush();
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Next 128 bytes of %rip" << std::endl;
	std::cout << std::endl;

	for( unsigned char* i = ip; i < ip + 128; ++i ) {
		if (count++ % 8 == 0)
			std::cout << std::endl << std::hex << std::setfill('0') << std::showbase << (uint64_t)i << ": ";
		std::cout << std::hex << std::setw(2) << std::setfill('0') << std::showbase << (uint16_t)*i << " ";
		std::cout.flush();
	}
	std::cout << std::endl;
	std::cout << std::endl;

	exit(1);
}

} // namespace cpputil

#endif
