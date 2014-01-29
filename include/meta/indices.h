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

#ifndef CPPUTIL_INCLUDE_META_INDICES_H
#define CPPUTIL_INCLUDE_META_INDICES_H

namespace cpputil {

template<size_t... Is> 
struct Indices {
  enum { size = sizeof...(Is) };
};

template<size_t N, size_t... Is>
struct MakeIndices : MakeIndices < N - 1, N - 1, Is... > { };

template<size_t... Is>
struct MakeIndices<0, Is...> : Indices<Is...> { };

} // namespace cpputil

#endif
