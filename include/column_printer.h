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

#ifndef CPPUTIL_SRC_COLUMN_PRINTER_H
#define CPPUTIL_SRC_COLUMN_PRINTER_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

namespace cpputil {

class ColumnPrinter {
	public:
		ColumnPrinter(std::ostream& os);

		ColumnPrinter& set_vspace(size_t vspace);

		template <typename... Ts>
		ColumnPrinter& operator<<(const std::tuple<Ts...>& ts);
		ColumnPrinter& operator<<(ColumnPrinter& (*fxn)(ColumnPrinter&));
		ColumnPrinter& flush();

	private:
		typedef std::vector<std::string> col_type;

		template<class Tuple, size_t N>
		struct VerticalPrinter {
			static void print(std::ostream& os, const Tuple& t);
		};

		template<class Tuple>
		struct VerticalPrinter<Tuple, 1>{
			static void print(std::ostream& os, const Tuple& t);
		};

		template<class... Args>
		void print(std::ostream& os, const std::tuple<Args...>& t);

		std::ostream& os_;
		std::vector<col_type> cols_;
		size_t vspace_;
};

ColumnPrinter& endline(ColumnPrinter& hp);

template <typename... Ts>
std::tuple<Ts&&...> col(Ts&&... ts);

inline ColumnPrinter::ColumnPrinter(std::ostream& os) :
		os_(os) {
	set_vspace(1);
}

inline ColumnPrinter& ColumnPrinter::set_vspace(size_t vspace) {
	vspace_ = vspace;
	return *this;
}

template <typename... Ts>
inline ColumnPrinter& ColumnPrinter::operator<<(const std::tuple<Ts...>& ts) {
	std::ostringstream oss;
	print(oss, ts);

	std::istringstream iss(oss.str());
	std::string s;

	col_type col;
	while ( getline(iss, s) )
		col.push_back(s);
	cols_.push_back(col);

	return *this;
}

inline ColumnPrinter& ColumnPrinter::operator<<(ColumnPrinter& (*fxn)(ColumnPrinter&)) {
	return fxn(*this);
}

inline ColumnPrinter& ColumnPrinter::flush() {
	if ( cols_.empty() ) {
		os_ << std::endl;
		return *this;
	}

	std::vector<size_t> col_widths;
	for ( const auto& col : cols_ ) {
		auto comp = [](const std::string& s1, const std::string& s2) { 
			return s1.length() < s2.length();
		};
		const auto itr = std::max_element(col.begin(), col.end(), comp);
		col_widths.push_back(itr->length());
	}

	auto comp = [](const col_type& col1, const col_type& col2) {
	 	return col1.size() < col2.size();
	};
	const auto itr = std::max_element(cols_.begin(), cols_.end(), comp);
	const auto max_height = itr->size();

	for ( size_t i = 0, ie = cols_.size(); i < ie; ++i ) {
		auto& col = cols_[i];
		std::string blank = "";
		for ( size_t j = 0, je = col_widths[i]; j < je; ++j )
			blank += " ";

		size_t j = 0;
		for ( size_t je = col.size(); j < je; ++j ) 
			while ( col[j].length() < col_widths[i] )
				col[j] += " ";
		for ( ; j < max_height; ++j )
			col.push_back(blank);
	}

	for ( size_t i = 0; i < max_height; ++i ) {
		for ( size_t j = 0, je = cols_.size(); j < je; ++j ) {
			os_ << cols_[j][i];
			for ( size_t k = 0; k < vspace_; ++k )
				os_ << " ";
		}
		os_ << std::endl;
	}

	cols_.clear();

	return *this;
}

template<class Tuple, size_t N>
inline void ColumnPrinter::VerticalPrinter<Tuple, N>::print(std::ostream& os, const Tuple& t) {
	VerticalPrinter<Tuple, N-1>::print(os, t);
	os << std::endl;
	os << std::get<N-1>(t);
}

template<class Tuple>
inline void ColumnPrinter::VerticalPrinter<Tuple, 1>::print(std::ostream& os, const Tuple& t) {
	os << std::get<0>(t);
}

template<class... Args>
inline void ColumnPrinter::print(std::ostream& os, const std::tuple<Args...>& t) {
	VerticalPrinter<decltype(t), sizeof...(Args)>::print(os, t);
}

inline ColumnPrinter& endline(ColumnPrinter& hp) {
	return hp.flush();
}

template <typename... Ts>
std::tuple<Ts&&...> col(Ts&&... ts) {
	return std::forward_as_tuple(ts...);
}

} // namespace cpputil

#endif
