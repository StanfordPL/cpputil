#include <functional>
#include <tuple>
#include <utility>

#include "include/meta/indices.h"

namespace cpputil {

template <typename Fxn, typename... Args>
class Thunk {
 public:
  typedef typename std::result_of<Fxn(Args...)>::type value_type;

  Thunk(Fxn&& fxn, Args&& ... args) :
    fxn_ {std::move(fxn)}, args_ {std::move(args)...} { }

  operator value_type() {
    return evaluate(MakeIndices<sizeof...(Args)>());
  }

 private:
  Fxn fxn_;
  std::tuple<Args...> args_;

  template <size_t... Is>
  value_type evaluate(Indices<Is...>) {
    return fxn_(std::get<Is>(args_)...);
  }
};

template <typename Fxn, typename... Args>
Thunk<Fxn, Args...> make_thunk(Fxn&& fxn, Args&& ... args) {
  return {fxn, std::forward<Args>(args)...};
}

} // namespace cpputil
