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

#ifndef CPPUTIL_SRC_TIMER_H
#define CPPUTIL_SRC_TIMER_H

#include <ctime>

namespace cpputil {

class Timer {
  public:
    typedef long sec_type;
    typedef long nsec_type;

    void start();
    void stop(); 

    sec_type sec() const;
    nsec_type nsec() const;

  private:
    timespec begin_;
    timespec end_;
};

inline void Timer::start() {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_);
}

inline void Timer::stop() {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_);
}

inline Timer::sec_type Timer::sec() const {
  return end_.tv_sec - begin_.tv_sec;
}

inline Timer::nsec_type Timer::nsec() const {
  return 1e9 * sec() + end_.tv_nsec - begin_.tv_nsec;
}

} // namespace cpputil

#endif
