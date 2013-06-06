#ifndef MAP_UTIL_H
#define MAP_UTIL_H

#include <cassert>

namespace cpputil {

template <typename Map>
class CppUtilMap : public Map {
	public:
		typedef Map map_type;

		class const_key_iterator {
			public:
				const_key_iterator() = delete;
				const_key_iterator(const typename map_type::const_iterator& itr);

				const_key_iterator& operator++();
				const typename map_type::key_type& operator*() const;

				bool operator==(const const_key_iterator& rhs) const;
				bool operator!=(const const_key_iterator& rhs) const;

			private:
				typename map_type::const_iterator itr_; 
		};

		class value_iterator {
			public:
				value_iterator() = delete;
				value_iterator(const typename map_type::iterator& itr);

				value_iterator& operator++();
				typename map_type::mapped_type& operator*() const; 

				bool operator==(const value_iterator& rhs) const; 
				bool operator!=(const value_iterator& rhs) const; 

			private:
				typename map_type::iterator itr_; 
		};

		class const_value_iterator {
			public:
				const_value_iterator() = delete;
				const_value_iterator(const typename map_type::const_iterator& itr);

				const_value_iterator& operator++();
				const typename map_type::mapped_type& operator*() const;

				bool operator==(const const_value_iterator& rhs) const;
				bool operator!=(const const_value_iterator& rhs) const;

			private:
				typename map_type::const_iterator itr_; 
		};

		const_key_iterator key_begin() const;
		const_key_iterator key_cbegin() const;

		const_key_iterator key_end() const;
		const_key_iterator key_cend() const;

		value_iterator value_begin();
		const_value_iterator value_begin() const;
		const_value_iterator value_cbegin() const;

		value_iterator value_end();
		const_value_iterator value_end() const;
		const_value_iterator value_cend() const;

    typename map_type::mapped_type& assert_at(const typename map_type::key_type& k);
		const typename map_type::mapped_type& assert_at(const typename map_type::key_type& k) const;		
		
		typename map_type::size_type assert_erase(const typename map_type::key_type& k);
};

template <typename Map>
inline CppUtilMap<Map>::value_iterator::value_iterator(
		const typename map_type::iterator& itr) 
		: itr_{itr} { 
}

template <typename Map>
inline typename CppUtilMap<Map>::value_iterator& 
CppUtilMap<Map>::value_iterator::operator++() {
	itr_++;
	return *this;
}

template <typename Map>
inline typename CppUtilMap<Map>::map_type::mapped_type& 
CppUtilMap<Map>::value_iterator::operator*() const {
	return itr_->second;
}

template <typename Map>
inline bool CppUtilMap<Map>::value_iterator::operator==(
		const value_iterator& rhs) const {
	return itr_ == rhs.itr_;
}

template <typename Map>
inline bool CppUtilMap<Map>::value_iterator::operator!=(
		const value_iterator& rhs) const {
	return itr_ != rhs.itr_;
}

template <typename Map>
inline CppUtilMap<Map>::const_key_iterator::const_key_iterator(
		const typename map_type::const_iterator& itr) 
		: itr_{itr} { 
}

template <typename Map>
inline typename CppUtilMap<Map>::const_key_iterator& 
CppUtilMap<Map>::const_key_iterator::operator++() {
	itr_++;
	return *this;
}

template <typename Map>
inline const typename CppUtilMap<Map>::map_type::key_type& 
CppUtilMap<Map>::const_key_iterator::operator*() const {
	return itr_->first;
}

template <typename Map>
inline bool CppUtilMap<Map>::const_key_iterator::operator==(
		const const_key_iterator& rhs) const {
	return itr_ == rhs.itr_;
}

template <typename Map>
inline bool CppUtilMap<Map>::const_key_iterator::operator!=(
		const const_key_iterator& rhs) const {
	return itr_ != rhs.itr_;
}

template <typename Map>
inline CppUtilMap<Map>::const_value_iterator::const_value_iterator(
		const typename map_type::const_iterator& itr) 
		: itr_{itr} { 
}

template <typename Map>
inline typename CppUtilMap<Map>::const_value_iterator& 
CppUtilMap<Map>::const_value_iterator::operator++() {
	itr_++;
	return *this;
}

template <typename Map>
inline const typename CppUtilMap<Map>::map_type::mapped_type& 
CppUtilMap<Map>::const_value_iterator::operator*() const {
	return itr_->second;
}

template <typename Map>
inline bool CppUtilMap<Map>::const_value_iterator::operator==(
		const const_value_iterator& rhs) const {
	return itr_ == rhs.itr_;
}

template <typename Map>
inline bool CppUtilMap<Map>::const_value_iterator::operator!=(
		const const_value_iterator& rhs) const {
	return itr_ != rhs.itr_;
}

template <typename Map>
inline typename CppUtilMap<Map>::const_key_iterator 
CppUtilMap<Map>::key_begin() const {
	return const_key_iterator(Map::begin());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_key_iterator 
CppUtilMap<Map>::key_cbegin() const {
	return const_key_iterator(Map::cbegin());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_key_iterator 
CppUtilMap<Map>::key_end() const {
	return const_key_iterator(Map::end());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_key_iterator 
CppUtilMap<Map>::key_cend() const {
	return const_key_iterator(Map::cend());
}

template <typename Map>
inline typename CppUtilMap<Map>::value_iterator CppUtilMap<Map>::value_begin() {
	return value_iterator(Map::begin());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_value_iterator 
CppUtilMap<Map>::value_begin() const {
	return const_value_iterator(Map::begin());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_value_iterator 
CppUtilMap<Map>::value_cbegin() const {
	return const_value_iterator(Map::cbegin());
}

template <typename Map>
inline typename CppUtilMap<Map>::value_iterator CppUtilMap<Map>::value_end() {
	return value_iterator(Map::end());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_value_iterator 
CppUtilMap<Map>::value_end() const {
	return const_value_iterator(Map::end());
}

template <typename Map>
inline typename CppUtilMap<Map>::const_value_iterator 
CppUtilMap<Map>::value_cend() const {
	return const_value_iterator(Map::cend());
}

template <typename Map>
inline typename CppUtilMap<Map>::map_type::mapped_type& 
CppUtilMap<Map>::assert_at(const typename map_type::key_type& k) {
	assert(Map::find(k) != Map::end() && "Unrecognized key!");
	return Map::at(k);
}

template <typename Map>
inline const typename CppUtilMap<Map>::map_type::mapped_type& 
CppUtilMap<Map>::assert_at(const typename map_type::key_type& k) const {
	assert(Map::find(k) != Map::end() && "Unrecognized key!");
	return Map::at(k);
}

template <typename Map>
inline typename CppUtilMap<Map>::map_type::size_type
CppUtilMap<Map>::assert_erase(const typename map_type::key_type& k) {
	assert(Map::find(k) != Map::end() && "Unrecognized key!");
	return Map::erase(k);
}

} // namespace cpputil

#endif
