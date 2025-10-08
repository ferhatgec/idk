// idk libraries
// -------------
// disclaimer: don't forget that, idk libraries are not focused on replacing
// standard library. (for some standard classes are directly being replaced by
// compiler, like initializer_list will need compiler dependent codes)
// so, this is not *directly* an alternative to stl, some class- and functions
// may have different naming different outputs or attributes etc.
//
// MIT License
//
// Copyright (c) 2023-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "../containers/vector.hpp"
#include "../types/predefined.hpp"
#include "../types/stringview.hpp"
#include "../utilities/pair.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
// key value storage
class Argument {
  Pair<StringViewChar, StringViewChar> arg;

  StringViewChar init;

public:
  Argument(const StringChar &key, const StringChar &value) noexcept {
    this->arg = MakePair<StringViewChar, StringViewChar>(key, value);
  }

  Argument() noexcept {
    this->arg =
        MakePair<StringViewChar, StringViewChar>(this->init, this->init);
  }

  Argument(const StringViewChar &key) noexcept {
    this->arg = MakePair<StringViewChar, StringViewChar>(key, this->init);
  }

  ~Argument() = default;

  [[nodiscard]]
  bool has_key() const noexcept {
    return !this->arg.first_immutable().is_empty();
  }

  [[nodiscard]]
  bool has_value() const noexcept {
    return !this->arg.second_immutable().is_empty();
  }

  [[nodiscard]]
  StringViewChar &key() noexcept {
    return this->arg.first();
  }

  [[nodiscard]]
  StringViewChar &value() noexcept {
    return this->arg.second();
  }

  [[nodiscard]]
  const StringViewChar &key_immutable() const noexcept {
    return this->arg.first_immutable();
  }

  [[nodiscard]]
  const StringViewChar &value_immutable() const noexcept {
    return this->arg.second_immutable();
  }

  friend std::ostream &operator<<(std::ostream &ostr, const Argument &arg) {
    if (arg.has_value())
      ostr << '[' << arg.key_immutable() << ", " << arg.value_immutable()
           << ']';
    else
      ostr << arg.key_immutable();

    return ostr;
  }
};

class Arguments {
  usize _argc;
  Vec<Argument> _args;

public:
  enum class Error { Out_Of_Range };

  explicit Arguments(int argc, char **argv) noexcept : _argc(argc) {
    for (usize n = 0; n < argc; ++n) {
      this->_args.push_back(parse(StringViewChar(argv[n])));
    }
  }

  explicit Arguments(char **argv) noexcept {
    char **ptr = argv;

    while (*ptr != nullptr) {
      this->_args.push_back(parse(StringViewChar(*ptr)));
      ++ptr;
      ++this->_argc;
    }
  }

  explicit Arguments(Vec<StringViewChar> &argv) noexcept {
    for (auto &arg : argv) {
      this->_args.push_back(parse(StringViewChar(arg)));
      ++this->_argc;
    }
  }

  Arguments() = default;
  ~Arguments() = default;

  [[nodiscard]]
  static Argument parse(const StringViewChar &arg) noexcept {
    if (arg.is_empty())
      return Argument(arg);

    for (usize i = 0; i < arg.length(); ++i)
      if ((arg[i].try_get_value() == '=') || arg[i].try_get_value() == ':')
        return Argument(arg.substr(0, i),
                        arg.substr(i + 1, arg.length() - i - 1));

    return Argument(arg);
  }

  // finds key
  [[nodiscard]]
  bool find(const StringChar &arg) noexcept {
    for (auto &val : this->_args)
      if (val.key() == arg)
        return true;

    return false;
  }

  // finds key
  [[nodiscard]]
  bool find(const Vec<StringViewChar> &args) const noexcept {
    for (auto &val : this->_args) {
      if (!val.has_key())
        continue;

      for (const auto &arg : args) {
        if (arg.is_empty())
          continue;

        // first, we are comparing the last characters; -just because commonly
        // '-' and '--' used for passing flags, so first character would same-
        // if not same, skipping it. both have constant time operations.
        if ((val.key_immutable().length() == arg.length()) &&
            val.key_immutable().back_immutable() == arg.back_immutable())
          if (val.key_immutable() == arg)
            return true;
      }
    }

    return false;
  }

  [[nodiscard]]
  Argument *begin() noexcept {
    return this->_args.begin();
  }

  [[nodiscard]]
  Argument *end() noexcept {
    return this->_args.end();
  }

  ValueOr<Argument, Error> operator[](usize n) noexcept { return this->at(n); }

  ValueOr<Argument, Error> at(usize n) noexcept {
    if (n >= this->_args.size())
      return Unexpected<Error>(Error::Out_Of_Range);

    return Expected<Argument>(this->_args.at_without_check(n));
  }
};
} // namespace idk