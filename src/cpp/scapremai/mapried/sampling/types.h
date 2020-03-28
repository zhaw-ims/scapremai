#pragma once

// File automatically generated by mapry. DO NOT EDIT OR APPEND!

#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace scapremai {
namespace mapried {
namespace sampling {

struct Sampling;

class Input;

struct Output;

// defines the outcome (remaining useful life, RUL).
struct Output {
  // identifies the outcome in the model.
  std::string identifier;

  // indicates the begining of the value range.
  double range_begin = 0.0;

  // indicates the end of the value range.
  double range_end = 0.0;
};

// defines an input to the model.
class Input {
 public:
  // identifies the instance.
  std::string id;

  // identifies the input in the model.
  std::string identifier;

  // indicates the begining of the value range.
  double range_begin = 0.0;

  // indicates the end of the value range.
  double range_end = 0.0;
};

// specifies the sampling of the physical model.
struct Sampling {
  // specifies the outcome variable (remaining useful life, RUL).
  Output output;

  // specifies the number of sampling bins.
  int64_t bins = 0;

  // registers Input instances.
  std::map<std::string, std::unique_ptr<Input>> inputs;
};

}  // namespace sampling
}  // namespace mapried
}  // namespace scapremai

// File automatically generated by mapry. DO NOT EDIT OR APPEND!
