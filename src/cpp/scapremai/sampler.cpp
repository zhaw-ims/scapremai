/**
 * Sample the data points from a given physical model.
 */

#include "scapremai/mapried/sampling/jsoncpp.h"
#include "scapremai/mapried/sampling/parse.h"
#include "scapremai/mapried/sampling/types.h"

#include <fmt/format.h>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <iostream>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

struct Args {
  fs::path model_path;
  fs::path sampling_path;
  fs::path outdir;
  bool dont_unwind_stack = false;
};

int main_impl(const Args& a) {
  std::ifstream sampling_ifs(a.sampling_path.string());
  Json::Value sampling_root;

  try {
    sampling_ifs >> sampling_root;
  } catch (const std::exception& e) {
    spdlog::critical("Failed to read sampling specification from %s: %s",
                     a.sampling_path.string(), e.what());
    return 1;
  }

  scapremai::mapried::sampling::Sampling sampling;
  scapremai::mapried::sampling::parse::Errors errors(1024);
  scapremai::mapried::sampling::jsoncpp::sampling_from(
      sampling_root, a.sampling_path.string(), &sampling, &errors);

  if (not errors.empty()) {
    std::vector<std::string> lines;
    lines.reserve(1 + errors.get().size());
    lines.push_back(
        fmt::format("Failed to parse sampling specification from %s:",
                    a.sampling_path.string()));

    for (const auto& e : errors.get()) {
      lines.push_back(fmt::format("%s:%s", e.ref, e.message));
    }

    spdlog::critical(boost::algorithm::join(lines, "\n"));
  }

  return 0;
}

int main(int argc, char* argv[]) {
  Args args;

  po::options_description desc(
      "Sample the data points from a given physical model");

  auto opts = desc.add_options();
  opts("model_path", po::value(&args.model_path)->required(),
       "path to the physical model");

  opts("sampling_path", po::value(&args.sampling_path)->required(),
       "path to the sampling specification");

  opts("outdir", po::value(&args.outdir)->required(),
       "path to the output directory");

  opts("dont_unwind_stack",
       "if specified, the stack will not be unwound. "
       "Use this only when you need to debug and have to trace the stack!");
  opts("help,h", "Shows usage");

  po::variables_map varmap;
  po::store(po::parse_command_line(argc, argv, desc), varmap);

  if (varmap.count("help") != 0) {
    std::cout << desc << std::endl;
    return 0;
  }

  args.dont_unwind_stack = varmap.count("dont_unwind_stack") > 0;

  try {
    po::notify(varmap);
  } catch (po::error& err) {
    std::cerr << err.what() << "\n\n" << desc << std::endl;
    return 1;
  }

  if (args.dont_unwind_stack) {
    main_impl(args);
  } else {
    // force stack unwinding
    try {
      return main_impl(args);
    } catch (...) {
      spdlog::critical("An exception occurred.");
      throw;
    }
  }
}
