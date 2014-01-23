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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_COMMAND_LINE_CONFIG_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_COMMAND_LINE_CONFIG_H

#include <cstdlib>
#include <fstream>

#include "include/command_line/arg.h"
#include "include/command_line/args.h"
#include "include/command_line/flag_arg.h"
#include "include/command_line/heading.h"
#include "include/command_line/value_arg.h"
#include "include/io/filterstream.h"
#include "include/io/indent.h"

namespace cpputil {

class CommandLineConfig {
 public:
  /** Strict parse with help, config, and debug support */
  static void strict_with_convenience(int argc, char** argv) {
		auto& heading = Heading::create("Help and argument utilities:");
    auto& help = FlagArg::create("h")
      .alternate("help")
      .description("Print this message and quit");
    auto& debug = FlagArg::create("write_args")
      .description("Print program arguments and quit");
    auto& read_config = ValueArg<std::string>::create("read_config")
      .usage("<path/to/file.dat>")
      .default_val("")
      .description("Read program args from a configuration file");
    auto& write_config = ValueArg<std::string>::create("write_config")
      .usage("<path/to/file.dat>")
      .default_val("")
      .description("Print an example configuration file");

		auto alpha = [](Arg* a1, Arg* a2) { return *(a1->alias_begin()) < *(a2->alias_begin()); };
		Args::sort_args(alpha);

    Args::read(argc, argv);

    if (help) {
			std::cout << std::endl;
			std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
			std::cout << std::endl;

      write_help(std::cout);

      exit(0);
    }

    if (read_config.value() != "") {
      std::ifstream ifs(read_config.value());
      if (!ifs.is_open()) {
        std::cerr << "Unable to read config file!" << std::endl;
        exit(1);
      }
      Args::read(ifs);
    }

    if (Args::error() || Args::duplicate() || Args::unrecognized() || Args::anonymous()) {
			std::cerr << std::endl;
			std::cerr << "Errors:" << std::endl;
			std::cerr << std::endl;

			write_errors(std::cerr);
			write_duplicates(std::cerr);
			write_unrecognized(std::cerr);
			write_anonymous(std::cerr);

      exit(1);
    }

    if (debug) {
			std::clog << std::endl;
			std::clog << "Arg Values:" << std::endl;
			std::clog << std::endl;

      write_arg_vals(std::clog);

      exit(0);
    }

    if (write_config.value() != "") {
      std::ofstream ofs(write_config.value());
      if (!ofs.is_open()) {
        std::cerr << "Unable to write config file!" << std::endl;
        exit(1);
      }
      write_config_file(ofs, argv[0]);
    }
  }

 private:
	/** Prints arg aliases and usage */
	static void write_arg(std::ostream& os, Arg* a) {
		for (auto i = a->alias_begin(); i != a->alias_end(); ++i) {
			os << *i << " ";
		}
		a->usage(os);
	}

	/** Prints error args */
	static void write_errors(std::ostream& os) {
		ofilterstream<Indent> ofs(os);
		ofs.filter().indent();

		for (auto a = Args::error_begin(); a != Args::error_end(); ++a) {
			write_arg(ofs, *a);
     	ofs << std::endl;

			ofs.filter().indent(2);
      ofs << "Error reading value: ";
      (*a)->error(ofs);
      ofs << std::endl;
			ofs.filter().unindent(2);
		}
			
		ofs.filter().unindent();
	}

	/** Prints duplicate args */
	static void write_duplicates(std::ostream& os) {
		ofilterstream<Indent> ofs(os);
		ofs.filter().indent();

		for (auto a = Args::duplicate_begin(); a != Args::duplicate_end(); ++a) {
			write_arg(ofs, *a);
     	ofs << std::endl;

			ofs.filter().indent(2);
			ofs << "Ignoring duplicate occurences!" << std::endl;
			ofs.filter().unindent(2);
		}
			
		ofs.filter().unindent();
	}

  /** Prints unrecognized args */
  static void write_unrecognized(std::ostream& os) {
		ofilterstream<Indent> ofs(os);
		ofs.filter().indent();

    for (auto i = Args::unrecognized_begin(); i != Args::unrecognized_end(); ++i) {
      ofs << *i << " " << std::endl;
			ofs.filter().indent(2);
    	ofs << "Ignoring unrecognized argument!" << std::endl;
			ofs.filter().unindent(2);
    }

		ofs.filter().unindent();
  }

	/** Prints anonymous args */
  static void write_anonymous(std::ostream& os) {
		ofilterstream<Indent> ofs(os);
		ofs.filter().indent();

    for (auto i = Args::anonymous_begin(); i != Args::anonymous_end(); ++i) {
			ofs << *i << " " << std::endl;
			ofs.filter().indent(2);
      ofs << "Ignoring dangling value!" << std::endl;
			ofs.filter().unindent(2);
    }

		ofs.filter().unindent();
  }

  /** Prints arg aliases, usages, and descriptions */
  static void write_help(std::ostream& os) {
    ofilterstream<Indent> ofs(os);
    ofs.filter().indent();

		for (auto g = Args::group_begin(); g != Args::group_end(); ++g ) {
			ofs << g->heading << std::endl;
			ofs << std::endl;
			for (auto a = g->arg_begin(); a != g->arg_end(); ++a) {
				write_arg(ofs, *a);
				ofs << std::endl;

				ofs.filter().indent(2);
				(*a)->description(ofs);
				ofs << std::endl;
				ofs.filter().unindent(2);
			}
			ofs << std::endl;
		}

		ofs.filter().unindent();
	}

  /** Prints args and their corresponding values */
  static void write_arg_vals(std::ostream& os) {
    ofilterstream<Indent> ofs(os);
    ofs.filter().indent();

		for (auto g = Args::group_begin(); g != Args::group_end(); ++g ) {
			ofs << g->heading << std::endl;
			ofs << std::endl;
			for (auto a = g->arg_begin(); a != g->arg_end(); ++a) {
				write_arg(ofs, *a);
				ofs << std::endl;

				ofs.filter().indent(2);
				(*a)->description(ofs);
				ofs << std::endl;
				(*a)->debug(ofs);
				ofs << std::endl;
				ofs.filter().unindent(2);
			}
		}

    ofs.filter().unindent();
  }

  /** Prints a config file with descriptions, aliases, and usages */
  static void write_config_file(std::ostream& os, const char* argv0) {
    os << "##### " << argv0 << std::endl;
		os << std::endl;

		for (auto g = Args::group_begin(); g != Args::group_end(); ++g ) {
			os << "##### " << g->heading << std::endl;
			os << std::endl;
			for (auto a = g->arg_begin(); a != g->arg_end(); ++a) {
				os << "# ";
				(*a)->description(os);
				os << std::endl;
				os << "# " << *((*a)->alias_begin()) << " ";
				(*a)->usage(os);
				os << std::endl;
				os << std::endl;
			}
		}
  }
};

} // namespace cpputil

#endif

