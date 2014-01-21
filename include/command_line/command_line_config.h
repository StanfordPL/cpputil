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
#include <set>

#include "include/command_line/arg.h"
#include "include/command_line/args.h"
#include "include/command_line/flag_arg.h"
#include "include/command_line/value_arg.h"

namespace cpputil {

class CommandLineConfig {
 public:
  /** Strict parse with help, config, and debug support */
  static void strict_with_convenience(int argc, char** argv) {
    auto& help = FlagArg::create("h")
      .alternate("help")
      .description("Print this message and quit");

    auto& debug = FlagArg::create("debug_args")
      .description("Print program arguments and quit");

    auto& read_config = ValueArg<std::string>::create("read_config")
      .usage("<path/to/file.dat>")
      .default_val("")
      .description("Read program args from a configuration file");

    auto& example_config = ValueArg<std::string>::create("example_config")
      .usage("<path/to/file.dat>")
      .default_val("")
      .description("Print an example configuration file");

    Args::read(argc, argv);

    if (help) {
      write_help(std::cout, argv[0]);
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

    if (write_any_errors(std::cerr)) {
      exit(1);
    }

    if (debug) {
      write_arg_vals(std::clog);
      exit(0);
    }

    if (example_config.value() != "") {
      std::ofstream ofs(example_config.value());
      if (!ofs.is_open()) {
        std::cerr << "Unable to write config file!" << std::endl;
        exit(1);
      }
      write_config_file(ofs, argv[0]);
    }
  }

 private:
  /** Prints out any errors; returns true if anything is printed */
  static bool write_any_errors(std::ostream& os) {
    auto error = false;

    for (auto i = Args::arg_begin(); i != Args::arg_end(); ++i) {
      const auto dup = (*i)->duplicated();
      const auto err = !(*i)->good();

      if (dup || err) {
        for (auto j = (*i)->alias_begin(); j != (*i)->alias_end(); ++j) {
          os << *j << " ";
        }
        os << std::endl;
      }
      if (dup) {
        os << std::endl;
        os << "Ignoring duplicate occurrences!" << std::endl;
        error = true;
      }
      if (err) {
        os << "Error reading value: ";
        (*i)->error(os);
        os << std::endl;
        error = true;
      }
    }

    std::set<std::string> unrecs;
    for (auto i = Args::unrecognized_begin(); i != Args::unrecognized_end(); ++i) {
      unrecs.insert(*i);
      error = true;
    }
    if (!unrecs.empty()) {
      for (const auto& unrec : unrecs) {
        os << unrec << " ";
      }
      os << std::endl;
      os << "Ignoring unrecognized arguments!" << std::endl;
    }

    std::set<std::string> anons;
    for (auto i = Args::anonymous_begin(); i != Args::anonymous_end(); ++i) {
      anons.insert(*i);
      error = true;
    }
    if (!anons.empty()) {
      for (const auto& anon : anons) {
        os << anon << " ";
      }
      os << std::endl;
      os << "Ignoring dangling values!" << std::endl;
    }

    return error;
  }

  /** Prints arg aliases, usages, and descriptions */
  static void write_help(std::ostream& os, const char* argv0) {
    os << "Usage: " << argv0 << " [options]" << std::endl;
    os << "Options:" << std::endl;

    for (auto a = Args::arg_begin(); a != Args::arg_end(); ++a) {
      for (auto i = (*a)->alias_begin(); i != (*a)->alias_end(); ++i) {
        os << *i << " ";
      }
      (*a)->usage(os);
      os << std::endl;
      (*a)->description(os);
      os << std::endl;
    }
  }

  /** Prints args and their corresponding values */
  static void write_arg_vals(std::ostream& os) {
    for (auto i = Args::arg_begin(); i != Args::arg_end(); ++i) {
      for (auto j = (*i)->alias_begin(); j != (*i)->alias_end(); ++j) {
        os << *j << " ";
      }
      os << std::endl;
      (*i)->debug(os);
      os << std::endl;
    }
  }

  /** Prints a config file with descriptions, aliases, and usages */
  static void write_config_file(std::ostream& os, const char* argv0) {
    os << "# " << argv0 << std::endl;
    for (auto a = Args::arg_begin(); a != Args::arg_end(); ++a) {
      os << "# ";
      (*a)->description(os);
      os << std::endl;
      os << "# " << *((*a)->alias_begin()) << " ";
      (*a)->usage(os);
      os << std::endl;
    }
  }
};

} // namespace cpputil

#endif

