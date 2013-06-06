#ifndef CPPUTIL_SRC_BIJECTION_H
#define CPPUTIL_SRC_BIJECTION_H

#include <initializer_list>
#include <map>

#include "src/maputil.h"

namespace cpputil {

template <typename D, typename R, typename DMap = std::map<D, R>, 
				  typename RMap = std::map<R, D>>
class Bijection {
	public:
		typedef D domain_type;
		typedef const D& const_domain_reference;
		typedef typename CppUtilMap<DMap>::const_key_iterator const_domain_iterator;

		typedef R range_type;
		typedef const R& const_range_reference;
		typedef typename CppUtilMap<RMap>::const_key_iterator const_range_iterator;

		typedef typename CppUtilMap<DMap>::map_type::const_iterator const_iterator;
		typedef typename CppUtilMap<DMap>::map_type::value_type value_type;
		typedef const value_type& const_reference;
		typedef typename CppUtilMap<DMap>::map_type::size_type size_type;

		const_iterator begin() const { return d2r_.begin(); }
		const_iterator cbegin() const { return d2r_.cbegin(); }
		const_iterator end() const { return d2r_.end(); }
		const_iterator cend() const { return d2r_.cend(); }

		const_domain_iterator domain_begin() const { return d2r_.key_begin(); }
		const_domain_iterator domain_cbegin() const { return d2r_.key_cbegin(); }
		const_domain_iterator domain_end() const { return d2r_.key_end(); }
		const_domain_iterator domain_cend() const { return d2r_.key_cend(); }

		const_range_iterator range_begin() const { return r2d_.key_begin(); }
		const_range_iterator range_cbegin() const { return r2d_.key_cbegin(); }
		const_range_iterator range_end() const { return r2d_.key_end(); }
		const_range_iterator range_cend() const { return r2d_.key_cend(); }

		bool empty() const { return d2r_.empty(); }

		size_type size() const { return d2r_.size(); }

		void clear() {
			d2r_.clear();
			r2d_.clear();
		}

		std::pair<const_iterator, bool> insert(const value_type& val) {
			if ( find(val) != end() ) {
				return std::make_pair(end(), false);
			} else {
				r2d_.insert(std::make_pair(val.second, val.first));
				return d2r_.insert(val);
			}
		} 
		template <class InputIterator>
	  void insert(InputIterator first, InputIterator last) {
			for ( ; first != last; ++first )
				insert(*first);
		}
		void insert(std::initializer_list<value_type> il) {
			for ( const auto& i : il ) 
				insert(*i);
		}

		const_iterator erase(const_iterator position) {
			r2d_.erase(position->second);
			return d2r_.erase(position);
		}
		size_type erase(const value_type& val) {
			erase(find(val));
		}
		const_iterator erase(const_iterator first, const_iterator last) {
			for ( auto temp = first; temp != last; ++temp )
				r2d_.erase(temp->second);
			return d2r_.erase(first, last);
		}

		const_iterator find(const value_type& val) const {
			const auto itr = d2r_.find(val.first);
			return itr != d2r_.end() && r2d_.find(val.second) != r2d_.end() ? itr : end();
		}
		const_iterator domain_find(const_domain_reference d) const { return d2r_.find(d); }
		const_iterator range_find(const_range_reference r) const { 
			const auto itr = r2d_.find(r);
	 		return itr != r2d_.end() ? d2r_.find(itr->second) : end();
		}

		const_reference domain_at(const_domain_reference d) const { return d2r_.at(d); }
		const_reference range_at(const_range_reference r) const { 
			const auto& val = r2d_.at(r);
			return d2r_.at(val.second); 
		}

		const_reference domain_assert_at(const_domain_reference d) const { return d2r_.assert_at(d); }
		const_reference range_assert_at(const_range_reference r) const { 
			const auto& val = r2d_.assert_at(r);
			return d2r_.assert_at(val.second);
		}

		void swap(Bijection& rhs) {
			d2r_.swap(rhs.d2r_);
			r2d_.swap(rhs.r2d_);
		}

	private:
		CppUtilMap<DMap> d2r_;
		CppUtilMap<RMap> r2d_;
};  

} // namespace cpputil

#endif
