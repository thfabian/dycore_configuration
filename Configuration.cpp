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

#include "Configuration.hpp"
#include <cstdlib>

namespace dycore {

namespace internal {

template <class T>
std::string to_string_impl(const T& value) {
  return std::to_string(value);
}

template <>
std::string to_string_impl(const std::string& value) {
  return value;
}

} // namespace internal

configuration::configuration() {

// Compute runtime accessor information
#define DYCORE_OPT(Type, Name, DefaultValue, NeedsUpdate)                                          \
  m_acessor_map.emplace(#Name,                                                                     \
                        accessor{static_cast<std::ptrdiff_t>(                                      \
                                     reinterpret_cast<Byte*>(std::addressof(this->m_##Name)) -     \
                                     reinterpret_cast<Byte*>(this)),                               \
                                 type_to_type_id<Type>::value});                                   \
  if(NeedsUpdate)                                                                                  \
    m_needs_update_set.emplace(#Name);
#include "Configuration.inc"
#undef DYCORE_OPT
}

void configuration::print() const {
#define DYCORE_OPT(Type, Name, DefaultValue, NeedsUpdate)                                          \
  std::printf("%-20s : %s\n", #Name, internal::to_string_impl(this->m_##Name).c_str());
#include "Configuration.inc"
#undef DYCORE_OPT
}

} // namespace dycore
