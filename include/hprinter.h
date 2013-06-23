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

#ifndef CPPUTIL_SRC_HPRINTER_H
#define CPPUTIL_SRC_HPRINTER_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <vector>

namespace cpputil {

class HPrinter {
	public:
		HPrinter(std::ostream& os);

		HPrinter& set_vspace(size_t vspace);

		template <typename T>
		HPrinter& operator<<(const T& t);
		HPrinter& operator<<(HPrinter& (*fxn)(HPrinter&));
		HPrinter& flush();

	private:
		typedef std::vector<std::string> col_type;

		std::ostream& os_;
		std::vector<col_type> cols_;
		size_t vspace_;
};

HPrinter& endline(HPrinter& hp);

inline HPrinter::HPrinter(std::ostream& os) :
		os_(os) {
	set_vspace(1);
}

inline HPrinter& HPrinter::set_vspace(size_t vspace) {
	vspace_ = vspace;
}

template <typename T>
inline HPrinter& HPrinter::operator<<(const T& t) {
	std::ostringstream oss;
	oss << t;

	std::istringstream iss(oss.str());
	std::string s;

	col_type col;
	while ( getline(iss, s) )
		col.push_back(s);
	cols_.push_back(col);

	return *this;
}

inline HPrinter& HPrinter::operator<<(HPrinter& (*fxn)(HPrinter&)) {
	return fxn(*this);
}

inline HPrinter& HPrinter::flush() {
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

inline HPrinter& endline(HPrinter& hp) {
	return hp.flush();
}

} // namespace cpputil

#endif
