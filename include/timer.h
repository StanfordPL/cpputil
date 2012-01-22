#ifndef TIMER_H
#define TIMER_H

namespace cpputil
{

class Timer
{
  public:

    // Member types
    typedef time_t time_type;  

    // Modifiers
    void start() { began_ = time(0); }
    time_type stop() { elapsed_ += time(0) - began_; }
    void wind(time_type timeup) { timeup_ = timeup; }     
    void clear() { elapsed_ = 0; }

    // State functions
    time_type elapsed() const { return elapsed_; }
    bool timeup const { return elapsed_ >= timeup_; }

  private:
    time_type began_;
    time_type elapsed_;
    time_type timeup_;
};

}

#endif
