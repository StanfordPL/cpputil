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
#include <iostream>
#include <stdint.h>
#include <string>
#include <sys/ucontext.h>
#include <unistd.h>

#include "include/serialize/hex_writer.h"

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
    memset(&sa, '\0', sizeof(sa));
    sigfillset(&sa.sa_mask);
    sa.sa_sigaction = h;
    sa.sa_flags = SA_ONSTACK;

    assert(sigaction(signum, &sa, 0) >= 0);
  }

  static void write_reg(std::ostream& os, const std::string& reg, uint64_t val) {
    os << reg << " = ";
    HexWriter<uint64_t>()(os, val);
    os << std::endl;
  }

  static void write_mem(std::ostream& os, unsigned char* addr) {
    auto p = (uint64_t*)addr;

    HexWriter<uint64_t, 8>()(os, (uint64_t)p);
    os << ": ";

    HexWriter<uint64_t>()(os, *p);
    os << std::endl;
  }

  static void write_cpu(std::ostream& os, void* context) {
    os << "Register Contents:" << std::endl;
    os << std::endl;

    const auto regs = ((ucontext_t*)context)->uc_mcontext.gregs;

    write_reg(os, "%rip", regs[REG_RIP]);
    write_reg(os, "%rfl", regs[REG_EFL]);
    os << std::endl;

    write_reg(os, "%rax", regs[REG_RAX]);
    write_reg(os, "%rdx", regs[REG_RDX]);
    write_reg(os, "%rcx", regs[REG_RCX]);
    write_reg(os, "%rbx", regs[REG_RBX]);
    write_reg(os, "%rdi", regs[REG_RDI]);
    write_reg(os, "%rsi", regs[REG_RSI]);
    write_reg(os, "%rbp", regs[REG_RBP]);
    write_reg(os, "%rsp", regs[REG_RSP]);
    write_reg(os, "%r8 ", regs[REG_R8]);
    write_reg(os, "%r9 ", regs[REG_R9]);
    write_reg(os, "%r10", regs[REG_R10]);
    write_reg(os, "%r11", regs[REG_R11]);
    write_reg(os, "%r12", regs[REG_R12]);
    write_reg(os, "%r13", regs[REG_R13]);
    write_reg(os, "%r14", regs[REG_R14]);
    write_reg(os, "%r15", regs[REG_R15]);
    os << std::endl;

    const auto ip = (unsigned char*)regs[REG_RIP];
    if (ip == 0) {
      os << "Unable to print memory in vicinity of %rip" << std::endl;
      exit(1);
    }

    os << "Preceeding 64 bytes of %rip" << std::endl;
    os << std::endl;

    for (unsigned char* i = ip - 64; i < ip; i += 8) {
      write_mem(os, i);
    }
    os << std::endl;

    os << "Next 128 bytes of %rip" << std::endl;
    os << std::endl;

    for (unsigned char* i = ip; i < ip + 128; i += 8) {
      write_mem(os, i);
    }
    os << std::endl;
  }

  static void sigsegv(int sig, siginfo_t* siginfo, void* context) {
    std::cerr << "SIGNAL: SIGSEGV" << std::endl;
    std::cerr << std::endl;

    std::cerr << "Address: ";
    HexWriter<uint64_t, 8>()(std::cerr, (uint64_t) siginfo->si_addr);
    std::cerr << std::endl;

    std::cerr << "Cause: ";
    if (siginfo->si_code == SEGV_MAPERR) {
      std::cerr << "Address not mapped" << std::endl;
    } else {
      std::cerr << "Bad permissions" << std::endl;
    }
    std::cerr << std::endl;

    write_cpu(std::cerr, context);
    exit(1);
  }

  static void sigill(int sig, siginfo_t* siginfo, void* context) {
    std::cerr << "SIGNAL: SIGILL" << std::endl;
    std::cerr << std::endl;

    std::cerr << "Caused by: ";
    switch (siginfo->si_code) {
      case ILL_ILLOPC:
        std::cerr << "Illegal opcode" << std::endl;
        break;
      case ILL_ILLOPN:
        std::cerr << "Illegal operand" << std::endl;
        break;
      case ILL_ILLADR:
        std::cerr << "Illegal addressing mode" << std::endl;
        break;
      case ILL_PRVOPC:
        std::cerr << "Privileged opcode" << std::endl;
        break;
      case ILL_PRVREG:
        std::cerr << "Privileged register" << std::endl;
        break;
      case ILL_COPROC:
        std::cerr << "Coprocessor error" << std::endl;
        break;
      case ILL_BADSTK:
        std::cerr << "Bad stack" << std::endl;
        break;
      default:
        std::cerr << "<UNKNOWN>" << std::endl;
    }
    std::cerr << std::endl;

    write_cpu(std::cerr, context);
    exit(1);
  }
};

} // namespace cpputil

#endif
