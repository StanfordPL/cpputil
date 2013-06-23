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

#ifndef CPPUTIL_SRC_ARGS_H
#define CPPUTIL_SRC_ARGS_H

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "include/singleton.h"

namespace cpputil {

class Arg;

class Args {
	friend class Singleton<Args>;
	friend class Arg;

	public:
		typedef std::vector<Arg*>::iterator error_iterator;
		typedef std::vector<std::string>::const_iterator unrecognized_iterator;
		typedef std::vector<std::string>::const_iterator anonymous_iterator;

		static void read(int argc, char** argv);

		static std::string debug();
		static std::string usage(size_t indent = 0);

		static bool error();
		static error_iterator error_begin();
		static error_iterator error_end();

		static bool unrecognized();
		static unrecognized_iterator unrecognized_begin();
		static unrecognized_iterator unrecognized_end();

		static bool anonymous();
		static anonymous_iterator anonymous_begin();
		static anonymous_iterator anonymous_end();

		static bool good();
		static bool fail();

	private:
		std::vector<Arg*> args_;
		std::vector<Arg*> errors_;
		std::vector<std::string> unrecognized_;
		std::vector<std::string> anonymous_;

		static void read_from_file(const char* path);
		static bool exists(const std::string& s);
};

class Arg {
	friend class Args;

	public:
		virtual ~Arg() = 0;

		virtual std::pair<int,int> read(int argc, char** argv) = 0;

		virtual std::string debug() const = 0;
		std::string usage(size_t indent = 0) const;

		bool error() const;
		const std::string& reason() const;

		template <typename T>
		class Reader {
			public:
				void operator()(std::istream& is, T& t);
		};

		template <typename T>
		class Writer {
			public:
				void operator()(std::ostream& os, const T& t) const;
		};

	protected:
		std::vector<int> appearances_;
		std::set<std::string> opts_;

		Arg(const std::string& opt);

		Arg& alternate(const std::string& a);
		Arg& usage(const std::string& u);
		Arg& description(const std::string& d);

		std::vector<int>& get_appearances(int argc, char** argv);

		void survivable_error(const std::string& error);
		void fatal_error(const std::string& error) const;

	private:
		std::string usage_;
		std::string description_;
		std::string error_;
};

class FlagArg : public Arg {
	public:
		virtual ~FlagArg();

		static FlagArg& create(const std::string& opt);

		virtual std::pair<int,int> read(int argc, char** argv);

		virtual std::string debug() const;

		operator bool();
		bool value();

		FlagArg& alternate(const std::string& a);
		FlagArg& usage(const std::string& u);
		FlagArg& description(const std::string& d);

	private:
		bool val_;

		FlagArg(const std::string& opt); 
};

template <typename T, typename R = Arg::Reader<T>, typename W = Arg::Writer<T>>
class ValueArg : public Arg {
	public:
		virtual ~ValueArg();

		static ValueArg& create(const std::string& opt);

		virtual std::pair<int,int> read(int argc, char** argv);

		virtual std::string debug() const;

		operator T&();
		T& value();

		ValueArg& alternate(const std::string& a);
		ValueArg& usage(const std::string& u);
		ValueArg& description(const std::string& d);

		ValueArg& default_val(const T& t);
		ValueArg& parse_error(const std::string& pe);

	private:
		R reader_;
		W writer_;
		T val_;
		std::string parse_error_;	

		ValueArg(const std::string& opt);
};

template <typename T, typename R = Arg::Reader<T>, typename W = Arg::Writer<T>>
class FileArg : public Arg {
	public:
		virtual ~FileArg();

		static FileArg& create(const std::string& opt);

		virtual std::pair<int,int> read(int argc, char** argv);

		virtual std::string debug() const;

		operator T&();
		T& value();

		FileArg& alternate(const std::string& a);
		FileArg& usage(const std::string& u);
		FileArg& description(const std::string& d);

		FileArg& default_path(const std::string& p);
		FileArg& default_val(const T& t);
		FileArg& parse_error(const std::string& pe);
		FileArg& file_error(const std::string& fe);

	private:
		R reader_;
		W writer_;
		T val_;
		std::string path_;
		std::string parse_error_;
		std::string file_error_;

		FileArg(const std::string& opt);
};

inline void Args::read(int argc, char** argv) {
	if ( argc == 3 && std::string(argv[1]) == ":" ) {
		read_from_file(argv[2]);
		return;
	}

	auto& args = Singleton<Args>::get();

	std::vector<bool> used;
	for ( auto i = 0; i < argc; ++i )
		used.push_back(false);

	for ( auto a : args.args_ ) {
		const auto res = a->read(argc, argv);
		if ( a->error() )
			args.errors_.push_back(a);
		used[res.first] = used[res.second] = true;
	}	

	for ( int i = 1; i < argc; ++i )
		if ( !used[i] ) {
			if ( argv[i][0] == '-' )
				args.unrecognized_.push_back(argv[i]);
			else
				args.anonymous_.push_back(argv[i]);
		}
}

inline std::string Args::debug() {
	std::ostringstream oss;
	
	auto& args = Singleton<Args>::get();
	for ( size_t i = 0, ie = args.args_.size(); i < ie; ++i ) {
		oss << args.args_[i]->debug();
		if ( i+1 != ie )
			oss << std::endl << std::endl;
	}

	return oss.str();
}

inline std::string Args::usage(size_t indent) {
	std::vector<std::string> usages;
	for ( auto a : Singleton<Args>::get().args_ ) {
		std::ostringstream oss;
		for ( const auto& opt : a->opts_ )
			oss << opt << " ";
		oss << a->usage_;
	 	if ( a->usage_ != "" )
			oss	<< " ";
		usages.push_back(oss.str());
	}

	size_t max_len = 0;
	for ( const auto& u : usages )
		max_len = std::max(max_len, u.length());

	std::ostringstream result;
	for ( size_t i = 0, ie = usages.size(); i < ie; ++i ) {
		for ( size_t j = 0; j < indent; ++j )
			result << " ";
		result << usages[i];
		for ( size_t j = usages[i].length(); j < max_len; ++j )
			result << ".";
		result << "... ";
		result << Singleton<Args>::get().args_[i]->description_;
		if ( i+1 != ie )
			result << std::endl;
	}

	return result.str();
}

inline bool Args::error() {
	return !Singleton<Args>::get().errors_.empty();
}

inline Args::error_iterator Args::error_begin() {
	return Singleton<Args>::get().errors_.begin();
}

inline Args::error_iterator Args::error_end() {
	return Singleton<Args>::get().errors_.end();
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

inline bool Args::anonymous() {
	return !Singleton<Args>::get().anonymous_.empty();
}

inline Args::anonymous_iterator Args::anonymous_begin() {
	return Singleton<Args>::get().anonymous_.begin();
}

inline Args::anonymous_iterator Args::anonymous_end() {
	return Singleton<Args>::get().anonymous_.end();
}

inline bool Args::good() {
	return !error() && !unrecognized();
}

inline bool Args::fail() {
	return !good();
}

inline void Args::read_from_file(const char* path) {
	std::ifstream ifs(path);
	if ( !ifs.is_open() )
		return;

	std::vector<char*> argv;
	argv.push_back(strdup("<ignore>"));

	while ( true ) {
		std::string s;
		ifs >> s;
		if ( ifs.eof() )
			break;
		argv.push_back(strdup(s.c_str()));
	}

	read(argv.size(), argv.data());
	
	for ( auto s : argv )
		free(s);
}

inline bool Args::exists(const std::string& opt) {
	for ( auto a : Singleton<Args>::get().args_ ) {
		if ( a->opts_.find(opt) != a->opts_.end() ) {
			return true;
		}
	}
	return false;
}

inline Arg::~Arg() {
}

inline std::string Arg::usage(size_t indent) const {
	std::ostringstream oss;

	for ( size_t i = 0; i < indent; ++i )
		oss << " ";

	for ( const auto& o : opts_ )
		oss << o << " ";
	oss << usage_;
	if ( usage_ != "" )
		oss << " ";
	oss << "... ";
	oss << description_;

	return oss.str();
}

inline bool Arg::error() const {
	return reason() != "";
}

inline const std::string& Arg::reason() const {
	return error_;
}

template <typename T>
inline void Arg::Reader<T>::operator()(std::istream& is, T& t) {
	is >> t;
}

template <typename T>
inline void Arg::Writer<T>::operator()(std::ostream& os, const T& t) const {
	os << t;
}

inline Arg::Arg(const std::string& opt) {
	alternate(opt);
	usage("");
	description("");
	survivable_error("");

	Singleton<Args>::get().args_.push_back(this);
}

inline Arg& Arg::alternate(const std::string& a) {
	std::string alt = "";

	if ( a.length() == 0 ) {
		fatal_error("Unable to register an arg name \"\"!");
	} else if ( a.length() == 1 ) {
		if ( a[0] == '-' ) {
			fatal_error("Unable to register an arg named \"-\"!");
		} else {
			alt = std::string("-") + a;
		}
	} else if ( a.length() == 2 && a == "--" ) {
		fatal_error("Unable to register an arg named \"--\"!");
	} else {
		alt = std::string("--") + a;
	}

	if ( Singleton<Args>::get().exists(alt) ) {
		std::ostringstream oss;
		oss << "Unable to register duplicate arg name \"" << alt << "\"!";
		fatal_error(oss.str());
	}

	opts_.insert(alt);
	return *this;
}

inline Arg& Arg::usage(const std::string& u) {
	usage_ = u;
	return *this;
}

inline Arg& Arg::description(const std::string& d) {
	description_ = d;
	return *this;
}

inline std::vector<int>& Arg::get_appearances(int argc, char** argv) {
	appearances_.clear();
	for ( auto i = 1; i < argc; ++i ) {
		for ( const auto& o : opts_ ) {
			if ( o == argv[i] ) {
				appearances_.push_back(i);
			}
		}
	}
	return appearances_;
}

inline void Arg::survivable_error(const std::string& error) {
	error_ = error;
}

inline void Arg::fatal_error(const std::string& error) const {
	std::cout << "FATAL ERROR (cpputil/args.h)" << std::endl;
	std::cout << error << std::endl;
	exit(1);
}

inline FlagArg::~FlagArg() {
}

inline FlagArg& FlagArg::create(const std::string& opt) {
	return *(new FlagArg{opt});
}

inline std::pair<int,int> FlagArg::read(int argc, char** argv) {
	if ( !get_appearances(argc, argv).empty() ) {
		val_ = true;
		return std::make_pair(appearances_[0], appearances_[0]);
	}

	return std::make_pair(0,0);
}

inline std::string FlagArg::debug() const {
	std::ostringstream oss;
	oss << "Flag Arg (" << *(opts_.begin()) << "):" << std::endl;
	oss << (val_ ? "true" : "false");

	return oss.str();
}

inline FlagArg::operator bool() {
	return val_;
}

inline bool FlagArg::value() {
	return val_;
}

inline FlagArg& FlagArg::alternate(const std::string& a) {
	Arg::alternate(a);
	return *this;
}

inline FlagArg& FlagArg::usage(const std::string& u) {
	Arg::usage(u);
	return *this;
}

inline FlagArg& FlagArg::description(const std::string& d) {
	Arg::description(d);
	return *this;
}

inline FlagArg::FlagArg(const std::string& opt) :
		Arg{opt},
		val_{false} {
	usage("");
	description("Flag Arg");
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>::~ValueArg() {
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>& ValueArg<T,R,W>::create(const std::string& opt) {
	return *(new ValueArg{opt});
}

template <typename T, typename R, typename W>
inline std::pair<int, int> ValueArg<T,R,W>::read(int argc, char** argv) {
	for ( const auto i : get_appearances(argc, argv) ) {
		if ( i == (argc-1) || argv[i+1][0] == '-' ) {
			survivable_error(parse_error_);
			return std::make_pair(i,i);
		} 

		std::istringstream iss(argv[i+1]);
		T temp = T();
		reader_(iss, temp);

		if ( iss.fail() ) {
			survivable_error(parse_error_);
		} else {
			val_ = temp;
		}
		return std::make_pair(i,i+1);
	}

	return std::make_pair(0,0);
}

template <typename T, typename R, typename W>
inline std::string ValueArg<T,R,W>::debug() const {
	std::ostringstream oss;
	oss << "Value Arg (" << *(opts_.begin()) << "):" << std::endl;
	writer_(oss, val_);

	return oss.str();
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>::operator T&() {
	return val_;
}

template <typename T, typename R, typename W>
inline T& ValueArg<T,R,W>::value() {
	return val_;
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>& ValueArg<T,R,W>::alternate(const std::string& a) {
	Arg::alternate(a);
	return *this;
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>& ValueArg<T,R,W>::usage(const std::string& u) {
	Arg::usage(u);
	return *this;
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>& ValueArg<T,R,W>::description(const std::string& d) {
	Arg::description(d);
	return *this;
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>& ValueArg<T,R,W>::default_val(const T& t) {
	val_ = t;
	return *this;
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>& ValueArg<T,R,W>::parse_error(const std::string& pe) {
	parse_error_ = pe;
	return *this;
}

template <typename T, typename R, typename W>
inline ValueArg<T,R,W>::ValueArg(const std::string& opt) :
		Arg{opt} {
	std::ostringstream oss;
	oss << "Error (" << *(opts_.begin()) << ") Unable to parse argument!";

	usage("<arg>");
	description("Value Arg");
	parse_error(oss.str());
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>::~FileArg() {
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::create(const std::string& opt) {
	return *(new FileArg{opt});
}

template <typename T, typename R, typename W>
inline std::pair<int, int> FileArg<T,R,W>::read(int argc, char** argv) {
	auto res = std::make_pair(0,0);
	for ( const auto i : get_appearances(argc, argv) ) {
		if ( i == (argc-1) || argv[i+1][0] == '-' ) {
			survivable_error(file_error_);
			return std::make_pair(i,i);
		} else {
			res = std::make_pair(i,i+1);
			path_ = argv[i+1];
			break;
		}
	}
		
	std::ifstream ifs(path_);
	if ( !ifs.is_open() ) {
		survivable_error(file_error_);
		return res;
	}

	T temp;
	reader_(ifs, temp);

	if ( ifs.fail() ) {
		survivable_error(file_error_);
	} else {
		val_ = temp;
	}

	return res;;
}

template <typename T, typename R, typename W>
inline std::string FileArg<T,R,W>::debug() const {
	std::ostringstream oss;
	oss << "File Arg (" << *(opts_.begin()) << ", \"" << path_ << "\"):";
	oss << std::endl;
	writer_(oss, val_);

	return oss.str();
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>::operator T&() {
	return val_;
}

template <typename T, typename R, typename W>
inline T& FileArg<T,R,W>::value() {
	return val_;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::alternate(const std::string& a) {
	Arg::alternate(a);
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::usage(const std::string& u) {
	Arg::usage(u);
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::description(const std::string& d) {
	Arg::description(d);
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::default_path(const std::string& p) {
	path_ = p;
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::default_val(const T& t) {
	val_ = t;
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::parse_error(const std::string& pe) {
	parse_error_ = pe;
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>& FileArg<T,R,W>::file_error(const std::string& fe) {
	file_error_ = fe;
	return *this;
}

template <typename T, typename R, typename W>
inline FileArg<T,R,W>::FileArg(const std::string& opt) :
		Arg{opt} {
	std::ostringstream oss1;
	oss1 << "Error (" << *(opts_.begin()) << ") Unable to parse input!";
	std::ostringstream oss2;
	oss2 << "Error (" << *(opts_.begin()) << ") Unable to read input file!";
	
	usage("<path>");
	description("File Arg");
	parse_error(oss1.str());
	file_error(oss2.str());
}

} // namespace cpputil

#endif
