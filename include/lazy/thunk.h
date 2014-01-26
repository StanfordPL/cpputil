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
