// File automatically generated by mapry. DO NOT EDIT OR APPEND!

#include "jsoncpp.h"
#include "parse.h"
#include "types.h"

#include <cstring>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace scapremai {
namespace mapried {
namespace sampling {

namespace jsoncpp {

/**
 * generates an error message.
 *
 * @param cc char array as the description part of the message
 * @param cc_size size of the char array
 * @param s string as the detail part of the message
 * @return concatenated string
 */
std::string message(const char* cc, size_t cc_size, std::string s) {
  std::string result;
  result.reserve(cc_size + s.size());
  result.append(cc, cc_size);
  result.append(s);
  return result;
}

/**
 * converts a JSON value type to a human-readable string representation.
 *
 * @param value_type to be converted
 * @return string representation of the JSON value type
 */
std::string value_type_to_string(Json::ValueType value_type) {
  switch (value_type) {
    case Json::ValueType::nullValue:
      return "null";
    case Json::ValueType::intValue:
      return "int";
    case Json::ValueType::uintValue:
      return "uint";
    case Json::ValueType::realValue:
      return "real";
    case Json::ValueType::stringValue:
      return "string";
    case Json::ValueType::booleanValue:
      return "bool";
    case Json::ValueType::arrayValue:
      return "array";
    case Json::ValueType::objectValue:
      return "object";
    default:
      std::stringstream ss;
      ss << "Unhandled value type in value_to_string: " << value_type;
      throw std::domain_error(ss.str());
  }
}

void sampling_from(const Json::Value& value, std::string ref, Sampling* target,
                   parse::Errors* errors) {
  if (errors == nullptr) {
    throw std::invalid_argument("Unexpected null errors");
  }

  if (!errors->empty()) {
    throw std::invalid_argument("Unexpected non-empty errors");
  }

  if (!value.isObject()) {
    constexpr auto expected_but_got("Expected an object, but got: ");

    errors->add(ref, message(expected_but_got, strlen(expected_but_got),
                             value_type_to_string(value.type())));
    return;
  }

  ////
  // Pre-allocate inputs
  ////

  std::string inputs_ref;
  inputs_ref.reserve(ref.size() + 7);
  inputs_ref += ref;
  inputs_ref += "/inputs";

  if (value.isMember("inputs")) {
    const Json::Value& obj = value["inputs"];
    if (!obj.isObject()) {
      constexpr auto expected_but_got("Expected an object, but got: ");

      errors->add(inputs_ref,
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(obj.type())));
    } else {
      for (Json::ValueConstIterator it = obj.begin(); it != obj.end(); ++it) {
        auto instance = std::make_unique<Input>();
        instance->id = it.name();
        target->inputs[it.name()] = std::move(instance);
      }
    }
  }

  // Pre-allocating class instances is critical.
  // If the pre-allocation failed, we can not continue to parse the instances.
  if (!errors->empty()) {
    return;
  }

  // Keep the prefix fixed in this buffer so that
  // it is copied as little as possible
  std::string instance_ref;

  ////
  // Parse inputs
  ////

  // clear() does not shrink the reserved memory,
  // see https://en.cppreference.com/w/cpp/string/basic_string/clear
  instance_ref.clear();
  instance_ref += inputs_ref;
  instance_ref += '/';

  if (value.isMember("inputs")) {
    const Json::Value& obj = value["inputs"];

    for (Json::ValueConstIterator it = obj.begin(); it != obj.end(); ++it) {
      instance_ref.reserve(inputs_ref.size() + 1 + it.name().size());
      instance_ref.resize(inputs_ref.size() + 1);
      instance_ref.append(it.name());

      Input* instance(target->inputs.at(it.name()).get());
      input_from(*it, instance_ref, instance, errors);

      if (errors->full()) {
        break;
      }
    }
  }
  if (errors->full()) {
    return;
  }

  ////
  // Parse output
  ////

  if (!value.isMember("output")) {
    errors->add(ref, "Property is missing: output");
  } else {
    const Json::Value& value_0 = value["output"];
    output_from(value_0, std::string(ref).append("/output"), &target->output,
                errors);
  }
  if (errors->full()) {
    return;
  }

  ////
  // Parse bins
  ////

  if (!value.isMember("bins")) {
    errors->add(ref, "Property is missing: bins");
  } else {
    const Json::Value& value_1 = value["bins"];
    if (!value_1.isInt64()) {
      constexpr auto expected_but_got("Expected an int64, but got: ");

      errors->add(std::string(ref).append("/bins"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_1.type())));
    } else {
      const auto cast_1 = value_1.asInt64();
      bool ok_1 = true;

      if (!(cast_1 >= 1)) {
        constexpr auto expected_but_got(
            "Expected "
            ">= 1"
            ", but got: ");

        errors->add(std::string(ref).append("/bins"),
                    message(expected_but_got, strlen(expected_but_got),
                            std::to_string(cast_1)));
        ok_1 = false;
      }

      if (ok_1) {
        target->bins = cast_1;
      }
    }
  }
  if (errors->full()) {
    return;
  }
}

void input_from(const Json::Value& value, std::string ref, Input* target,
                parse::Errors* errors) {
  if (!value.isObject()) {
    constexpr auto expected_but_got("Expected an object, but got: ");

    errors->add(ref, message(expected_but_got, strlen(expected_but_got),
                             value_type_to_string(value.type())));
    return;
  }

  ////
  // Parse identifier
  ////

  if (!value.isMember("identifier")) {
    errors->add(ref, "Property is missing: identifier");
  } else {
    const Json::Value& value_0 = value["identifier"];
    if (!value_0.isString()) {
      constexpr auto expected_but_got("Expected a string, but got: ");

      errors->add(std::string(ref).append("/identifier"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_0.type())));
    } else {
      target->identifier = value_0.asString();
    }
  }
  if (errors->full()) {
    return;
  }

  ////
  // Parse range_begin
  ////

  if (!value.isMember("range_begin")) {
    errors->add(ref, "Property is missing: range_begin");
  } else {
    const Json::Value& value_1 = value["range_begin"];
    if (!value_1.isDouble()) {
      constexpr auto expected_but_got("Expected a double, but got: ");

      errors->add(std::string(ref).append("/range_begin"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_1.type())));
    } else {
      target->range_begin = value_1.asDouble();
    }
  }
  if (errors->full()) {
    return;
  }

  ////
  // Parse range_end
  ////

  if (!value.isMember("range_end")) {
    errors->add(ref, "Property is missing: range_end");
  } else {
    const Json::Value& value_2 = value["range_end"];
    if (!value_2.isDouble()) {
      constexpr auto expected_but_got("Expected a double, but got: ");

      errors->add(std::string(ref).append("/range_end"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_2.type())));
    } else {
      target->range_end = value_2.asDouble();
    }
  }
  if (errors->full()) {
    return;
  }
}

void output_from(const Json::Value& value, std::string ref, Output* target,
                 parse::Errors* errors) {
  if (!value.isObject()) {
    constexpr auto expected_but_got("Expected an object, but got: ");

    errors->add(ref, message(expected_but_got, strlen(expected_but_got),
                             value_type_to_string(value.type())));
    return;
  }

  ////
  // Parse identifier
  ////

  if (!value.isMember("identifier")) {
    errors->add(ref, "Property is missing: identifier");
  } else {
    const Json::Value& value_0 = value["identifier"];
    if (!value_0.isString()) {
      constexpr auto expected_but_got("Expected a string, but got: ");

      errors->add(std::string(ref).append("/identifier"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_0.type())));
    } else {
      target->identifier = value_0.asString();
    }
  }
  if (errors->full()) {
    return;
  }

  ////
  // Parse range_begin
  ////

  if (!value.isMember("range_begin")) {
    errors->add(ref, "Property is missing: range_begin");
  } else {
    const Json::Value& value_1 = value["range_begin"];
    if (!value_1.isDouble()) {
      constexpr auto expected_but_got("Expected a double, but got: ");

      errors->add(std::string(ref).append("/range_begin"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_1.type())));
    } else {
      target->range_begin = value_1.asDouble();
    }
  }
  if (errors->full()) {
    return;
  }

  ////
  // Parse range_end
  ////

  if (!value.isMember("range_end")) {
    errors->add(ref, "Property is missing: range_end");
  } else {
    const Json::Value& value_2 = value["range_end"];
    if (!value_2.isDouble()) {
      constexpr auto expected_but_got("Expected a double, but got: ");

      errors->add(std::string(ref).append("/range_end"),
                  message(expected_but_got, strlen(expected_but_got),
                          value_type_to_string(value_2.type())));
    } else {
      target->range_end = value_2.asDouble();
    }
  }
  if (errors->full()) {
    return;
  }
}

Json::Value serialize_input(const Input& input) {
  Json::Value input_as_value;

  input_as_value["identifier"] = input.identifier;

  input_as_value["range_begin"] = input.range_begin;

  input_as_value["range_end"] = input.range_end;

  return input_as_value;
}

Json::Value serialize_output(const Output& output) {
  Json::Value output_as_value;

  output_as_value["identifier"] = output.identifier;

  output_as_value["range_begin"] = output.range_begin;

  output_as_value["range_end"] = output.range_end;

  return output_as_value;
}

Json::Value serialize_sampling(const Sampling& sampling) {
  Json::Value sampling_as_value;

  sampling_as_value["output"] = serialize_output(sampling.output);

  sampling_as_value["bins"] = sampling.bins;

  if (!sampling.inputs.empty()) {
    Json::Value inputs_as_value;
    for (const auto& kv : sampling.inputs) {
      const std::string& id = kv.first;
      const Input* instance = kv.second.get();

      if (id != instance->id) {
        constexpr auto expected(
            "Expected the class instance of "
            "Input"
            "to have the ID ");
        constexpr auto but_got(", but got: ");

        std::string msg;
        msg.reserve(strlen(expected) + id.size() + strlen(but_got) +
                    instance->id.size());
        msg += expected;
        msg += id;
        msg += but_got;
        msg += instance->id;

        throw std::invalid_argument(msg);
      }

      inputs_as_value[instance->id] = serialize_input(*instance);
    }
    sampling_as_value["inputs"] = inputs_as_value;
  }

  return sampling_as_value;
}

}  // namespace jsoncpp

}  // namespace sampling
}  // namespace mapried
}  // namespace scapremai

// File automatically generated by mapry. DO NOT EDIT OR APPEND!
