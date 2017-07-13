/**
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 *
 *  Copyright (C) 2017 Fabian Thuering
 *
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 *
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 **/

#pragma once

#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace dycore {

using Real = double;
using Byte = signed char;

/// @brief Known types
enum class type_id { Invalid = 0, Bool, Int, Real, String };

/// @brief Global dycore configuration
class configuration {
public:
  /// @brief Initialize option with default values
  configuration();

  /// @brief Configuration is non-copyable/moveable
  configuration(const configuration&) = delete;
  configuration(configuration&&) = delete;

// Getter & Setter
#define DYCORE_OPT(Type, Name, DefaultValue, NeedsUpdate)                                          \
  const Type& get_##Name() const noexcept { return this->m_##Name; }                               \
  void set_##Name(const Type& value) noexcept { this->m_##Name = value; }
#include "Configuration.inc"
#undef DYCORE_OPT

  /// @brief Get option `name` by string
  /// @throws std::runtime_error if option `name` does not exist
  template <class T>
  const T& get(const std::string& name) const;

  /// @brief Set option `name` by string
  /// @throws std::runtime_error if option `name` does not exist
  template <class T>
  void set(const std::string& name, const T& value);

  /// @brief Convert the options to string
  void print() const;

private:
#define DYCORE_OPT(Type, Name, DefaultValue, NeedsUpdate) Type m_##Name = DefaultValue;
#include "Configuration.inc"
#undef DYCORE_OPT

  struct accessor {
    std::ptrdiff_t m_offset; ///< Byte offset from `this`
    type_id m_type_id;       ///< Type of the accessor
  };

  /// Runtime accessor information
  std::unordered_map<std::string, accessor> m_acessor_map;

  /// Variables which need update
  std::unordered_set<std::string> m_needs_update_set;
};

inline std::string str_concat(const std::string& s) { return s; }

template <class... Args>
inline std::string str_concat(const std::string& s, Args&&... args) {
  return s + str_concat(args...);
}

//
// Type traits
//
namespace internal {

template <type_id TypeID>
struct invalid_type_id {
  using type = void;
};

template <class T>
struct invalid_type {
  static constexpr type_id value = type_id::Invalid;
};

} // namespace internal

template <type_id TypeID>
struct type_id_to_type {
  using type = typename internal::invalid_type_id<TypeID>::type;
  static_assert(!std::is_same<type, void>::value, "unsupported type-id");
};

template <typename T>
struct type_to_type_id {
  static constexpr type_id value = internal::invalid_type<T>::value;
  static_assert(value != type_id::Invalid, "unsupported type");
};

#define DYCORE_TYPE_TRAITS_IMPL(Type, TypeID)                                                      \
  template <>                                                                                      \
  struct type_id_to_type<TypeID> {                                                                 \
    using type = Type;                                                                             \
  };                                                                                               \
  template <>                                                                                      \
  struct type_to_type_id<Type> {                                                                   \
    static constexpr type_id value = TypeID;                                                       \
  };

DYCORE_TYPE_TRAITS_IMPL(bool, type_id::Bool)
DYCORE_TYPE_TRAITS_IMPL(int, type_id::Int)
DYCORE_TYPE_TRAITS_IMPL(Real, type_id::Real)
DYCORE_TYPE_TRAITS_IMPL(std::string, type_id::String)

#undef DYCORE_TYPE_TRAITS_IMPL

//
// Set & Get by string implementations
//
template <class T>
const T& configuration::get(const std::string& name) const {
  auto it = m_acessor_map.find(name);
  if(it == m_acessor_map.end())
    throw std::runtime_error(str_concat("error: option \"", name, "\" does not exists"));

  const accessor& acc = it->second;
  if(acc.m_type_id != type_to_type_id<T>::value)
    throw std::runtime_error(str_concat("error: invalid type of option \"", name, "\""));

  return *reinterpret_cast<T*>(reinterpret_cast<Byte*>(const_cast<configuration*>(this)) +
                               acc.m_offset);
}

template <class T>
void configuration::set(const std::string& name, const T& value) {
  auto it = m_acessor_map.find(name);
  if(it == m_acessor_map.end())
    throw std::runtime_error(str_concat("error: option \"", name, "\" does not exists"));

  const accessor& acc = it->second;
  if(acc.m_type_id != type_to_type_id<T>::value)
    throw std::runtime_error(str_concat("error: invalid type of option \"", name, "\""));

  *reinterpret_cast<T*>(reinterpret_cast<Byte*>(this) + acc.m_offset) = value;
}

} // namespace dycore
