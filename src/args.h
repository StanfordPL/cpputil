#ifndef CPPUTIL_SRC_ARGS_H
#define CPPUTIL_SRC_ARGS_H

#include <algorithm>
#include <cstdio>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "src/singleton.h"

namespace cpputil {

class Arg;

class Args {
	friend class Singleton<Args>;
	friend class Arg;

	public:
		typedef std::vector<std::string>::const_iterator unrecognized_iterator;
		typedef std::vector<std::string>::const_iterator anonymous_iterator;

		static bool read(int argc, char** argv);
		static std::string usage();

		static bool errors();

		static bool unrecognized();
		static unrecognized_iterator unrecognized_begin();
		static unrecognized_iterator unrecognized_end();

		static anonymous_iterator anonymous_begin();
		static anonymous_iterator anonymous_end();

		static bool good();
		static bool fail();

	private:
		std::vector<Arg*> args_;
		std::vector<Arg*> errors_;
		std::vector<std::string> unrecognized_;
		std::vector<std::string> anonymous_;

		Args() = default;
};

class Arg {
	friend class Args;

	public:
		virtual ~Arg() = 0;

	protected:
		Arg(char opt);

		Arg& description(const std::string& desc);
		Arg& alternate(const std::string& alt);

		virtual bool read(int argc, char** argv) = 0;
		virtual std::string usage() const = 0;

		char opt_;
		std::string alt_;

	private:
		std::string desc_;

		size_t width() const;
};

class FlagArg : public Arg {
	public:
		virtual ~FlagArg();

		static FlagArg& create(char opt);

		operator bool() const;

		FlagArg& description(const std::string& desc);
		FlagArg& alternate(const std::string& alt);

	protected:
		virtual bool read(int argc, char** argv);
		virtual std::string usage() const;

	private:
		bool val_;

		FlagArg(char opt); 
};

template <typename T>
class ValueArg : public Arg {
	public:
		virtual ~ValueArg();

		static ValueArg& create(char opt);

		operator T() const;

		ValueArg& description(const std::string& desc);
		ValueArg& alternate(const std::string& alt);

		ValueArg& default_val(const T& t);
		ValueArg& parse_error(const std::string parse);

	protected:
		T val_;

		virtual bool read(int argc, char** argv);
		virtual std::string usage() const;

		ValueArg(char opt);

	private:	
		std::string parse_;	
};

template <typename T>
class RangeArg : public ValueArg<T> {
	public:
		virtual ~RangeArg();

		static RangeArg& create(char opt);

		RangeArg& description(const std::string& desc);
		RangeArg& alternate(const std::string& alt);
		RangeArg& default_val(const T& def);
		RangeArg& parse_error(const std::string parse);

		RangeArg& range(const T& l, const T& u);
		RangeArg& range_error(const std::string range);

	protected:
		virtual bool read(int argc, char** argv);
		virtual std::string usage() const;

	private:
		T lower_;
		T upper_;
		std::string range_;	

		RangeArg(char opt);
};

inline bool Args::read(int argc, char** argv) {
	auto args = Singleton<Args>::get();
	for ( const auto& arg : args.args_ )
		if ( !arg->read(argc, argv) )
			args.errors_.push_back(arg);
}

inline std::string Args::usage() {
	auto args = Singleton<Args>::get();

	size_t max_width = 0;
	for ( const auto arg : args.args_ )
		max_width = std::max(max_width, arg->width());

	std::ostringstream oss;
	for ( size_t i = 0, ie = args.args_.size(); i < ie; ++i ) {
		const auto arg = args.args_[i];

		oss << "  -" << arg->opt_ << " ";
		if ( arg->alt_ != "" )
			oss << "--" << arg->alt_ << " ";
		oss << arg->usage() << " ";
	
		for ( size_t j = arg->width(); j < max_width; ++j )
			oss << ".";

		oss << "... ";
		oss << arg->desc_;

		if ( i+1 != ie )
			oss << std::endl;
	}

	return oss.str();
}

inline bool Args::errors() {
	return !Singleton<Args>::get().errors_.empty();
}

inline bool Args::unrecognized() {
	return !Singleton<Args>::get().unrecognized_.empty();
}

inline Args::unrecognized_iterator Args::unrecognized_begin() {
	return Singleton<Args>::get().unrecognized_.begin();
}

inline Args::unrecognized_iterator Args::unrecognized_end() {
	return Singleton<Args>::get().unrecognized_.end();
}

inline Args::anonymous_iterator Args::anonymous_begin() {
	return Singleton<Args>::get().anonymous_.begin();
}

inline Args::anonymous_iterator Args::anonymous_end() {
	return Singleton<Args>::get().anonymous_end();
}

inline bool Args::good() {
	return !errors() && !unrecognized();
}

inline bool Args::fail() {
	return !good();
}

inline Arg::~Arg() {
}

inline Arg::Arg(char opt) 
		: opt_{opt}, alt_{""}, desc_{"???"} { 
	Singleton<Args>::get().args_.push_back(this);
}

inline Arg& Arg::description(const std::string& desc) { 
	desc_ = desc; 
	return *this; 
}

inline Arg& Arg::alternate(const std::string& alt) { 
	alt_ = alt; 
	return *this; 
}

inline size_t Arg::width() const {
	// "  -c "
	size_t w = 5; 
	// "--alt "
	if ( alt_ != "" )
		w += (2+alt_.length()+1);
	// "usage "
	w += (usage().length()+1);

	return w;
}

inline FlagArg::~FlagArg() { 
}

inline FlagArg& FlagArg::create(char opt) {
	return *(new FlagArg{opt});
}

inline FlagArg::operator bool() const { 
	return val_; 
}

inline FlagArg& FlagArg::description(const std::string& desc) { 
	Arg::description(desc); 
	return *this; 
}

inline FlagArg& FlagArg::alternate(const std::string& alt) { 
	Arg::alternate(alt); 
	return *this; 
}

inline bool FlagArg::read(int argc, char** argv) { 
	option longopts[] =	{option{0,0,0,0}, option{0,0,0,0}};
	if ( alt_ != "" )
		longopts[0] = option{alt_.c_str(), no_argument, 0, opt_};
	const auto os = std::string("") + opt_;

	auto c = 0;

	freopen("/dev/null", "w", stderr);
	optind = 1;
	while ( (c = getopt_long(argc, argv, os.c_str(), longopts, 0)) != -1 ) {
		if ( c == opt_ ) {
			val_ = true;
			break;
		}
	}
	freopen("/dev/tty", "w", stderr);

	return true; 
}

inline std::string FlagArg::usage() const { 
	return ""; 
}

inline FlagArg::FlagArg(char opt) 
		: Arg{opt}, val_{false} { 
}

template <typename T>
inline ValueArg<T>::~ValueArg() { 
}

template <typename T>
inline ValueArg<T>& ValueArg<T>::create(char opt) {
	return *(new ValueArg{opt});
}

template <typename T>
inline ValueArg<T>::operator T() const { 
	return val_; 
}

template <typename T>
inline ValueArg<T>& ValueArg<T>::description(const std::string& desc) { 
	Arg::description(desc); 
	return *this; 
}

template <typename T>
inline ValueArg<T>& ValueArg<T>::alternate(const std::string& alt) { 
	Arg::alternate(alt); 
	return *this; 
}

template <typename T>
inline ValueArg<T>& ValueArg<T>::default_val(const T& t) { 
	val_ = t; 
	return *this; 
}

template <typename T>
inline ValueArg<T>& ValueArg<T>::parse_error(const std::string parse) { 
	parse_ = parse; 
	return *this; 
}

template <typename T>
inline bool ValueArg<T>::read(int argc, char** argv) { 
	option longopts[] =	{option{0,0,0,0}, option{0,0,0,0}};
	if ( alt_ != "" )
		longopts[0] = option{alt_.c_str(), required_argument, 0, opt_};
	const auto os = std::string("") + opt_ + std::string(":");

	auto c = 0;
	char* res = 0;

	freopen("/dev/null", "w", stderr);
	optind = 1;
	while ( (c = getopt_long(argc, argv, os.c_str(), longopts, 0)) != -1 ) {
		if ( c == opt_ ) {
			res = optarg;
			break;
		}
	}
	freopen("/dev/tty", "w", stderr);

	if ( res == 0 )
		return true;

	std::istringstream iss(res);
	iss >> val_;
	if ( iss.fail() )
		std::cout << "Error (-" << opt_ << "): " << parse_ << std::endl;

	return !iss.fail();
}

template <typename T>
inline std::string ValueArg<T>::usage() const { 
	return "<arg>";
}

template <typename T>
inline ValueArg<T>::ValueArg(char opt) 
		: Arg{opt}, parse_{"Unable to parse input argument!"} { 
}

template <typename T>
inline RangeArg<T>::~RangeArg() { 
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::create(char opt) {
	return *(new RangeArg{opt});
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::description(const std::string& desc) { 
	ValueArg<T>::description(desc); 
	return *this; 
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::alternate(const std::string& alt) { 
	ValueArg<T>::alternate(alt); 
	return *this; 
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::default_val(const T& def) { 
	ValueArg<T>::default_val(def); 
	return *this; 
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::parse_error(const std::string parse) { 
	ValueArg<T>::parse_error(parse); 
	return *this; 
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::range(const T& l, const T& u) { 
	lower_ = l; 
	upper_ = u; 
	return *this; 
}

template <typename T>
inline RangeArg<T>& RangeArg<T>::range_error(const std::string range) { 
	range_ = range; 
	return *this; 
}

template <typename T>
inline bool RangeArg<T>::read(int argc, char** argv) { 
	if ( !ValueArg<T>::read(argc, argv) )
		return false;
	if ( ValueArg<T>::val_ < lower_ || ValueArg<T>::val_ > upper_ ) {
		std::cout << "Error (-" << ValueArg<T>::opt_ << "): " << range_ << std::endl;
		return false;
	}
	return true;
}

template <typename T>
inline std::string RangeArg<T>::usage() const { 
	std::ostringstream oss;
	oss << "<" << lower_ << " - " << upper_ << ">";
	return oss.str();
}

template <typename T>
inline RangeArg<T>::RangeArg(char opt) 
		: ValueArg<T>{opt}, range_{"Input argument out of range!"} { 
}

} // namespace cpputil

#endif
