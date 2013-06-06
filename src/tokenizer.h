#ifndef CPPUTIL_SRC_TOKENIZER_H
#define CPPUTIL_SRC_TOKENIZER_H

#include <cassert>
#include <stdint.h>
#include <unordered_map>

#include "src/maputil.h"

namespace cpputil {

template <typename T, typename Token = uint64_t, 
				  typename Map = std::unordered_map<Token, T>>
class Tokenizer {
	public:
    typedef T value_type;
    typedef const T& const_reference; 
		typedef Token token_type;
    typedef typename CppUtilMap<Map>::size_type size_type;
    typedef typename CppUtilMap<Map>::const_value_iterator const_iterator;

		token_type tokenize(const_reference t);
		const_iterator untokenize(token_type token) const;

		const_iterator begin() const;
		const_iterator cbegin() const;
		const_iterator end() const;
		const_iterator cend() const;

		bool empty() const;
		size_type size() const;

		void clear();
		void swap(Tokenizer& rhs);

	private:
		CppUtilMap<Map> contents_;
		Token next_token_;
};

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::token_type 
Tokenizer<T, Token, Map>::tokenize(const_reference t) {
	if ( contents_.find(t) == contents_.end() ) {
		return contents_.insert(next_token_++, t).first->first;
	} else {
		return contents_.at(t);
	}
}

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::const_iterator 
Tokenizer<T, Token, Map>::untokenize(token_type token) const { 
	return contents_.find(token); 
}

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::const_iterator 
Tokenizer<T, Token, Map>::begin() const { 
	return contents_.vbegin(); 
}

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::const_iterator 
Tokenizer<T, Token, Map>::cbegin() const { 
	return contents_.cvbegin(); 
}

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::const_iterator 
Tokenizer<T, Token, Map>::end() const { 
	return contents_.vend(); 
}

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::const_iterator 
Tokenizer<T, Token, Map>::cend() const { 
	return contents_.cvend(); 
}

template <typename T, typename Token, typename Map>
inline bool Tokenizer<T, Token, Map>::empty() const { 
	return contents_.empty(); 
}

template <typename T, typename Token, typename Map>
inline typename Tokenizer<T, Token, Map>::size_type 
Tokenizer<T, Token, Map>::size() const { 
	return contents_.size(); 
}

template <typename T, typename Token, typename Map>
inline void Tokenizer<T, Token, Map>::clear() { 
	contents_.clear(); 
}

template <typename T, typename Token, typename Map>
inline void Tokenizer<T, Token, Map>::swap(Tokenizer& rhs) { 
	contents_.swap(rhs.contents_); 
}

} // namespace cpputil

#endif
