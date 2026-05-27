#ifndef MODIFIERS_H
#define MODIFIERS_H


#include "Unit.h"

namespace generator {
namespace Modifiers {
constexpr Unit::Flags PUBLIC = 1u << 0;
constexpr Unit::Flags PROTECTED = 1u << 1;
constexpr Unit::Flags PRIVATE = 1u << 2;
constexpr Unit::Flags INTERNAL = 1u << 3;
constexpr Unit::Flags PRIVATE_PROTECTED = 1u << 4;
constexpr Unit::Flags PROTECTED_INTERNAL = 1u << 5;
constexpr Unit::Flags ABSTRACT = 1u << 6;
constexpr Unit::Flags SEALED = 1u << 7;
constexpr Unit::Flags STATIC = 1u << 8;
constexpr Unit::Flags FINAL = 1u << 9;
constexpr Unit::Flags VIRTUAL = 1u << 10;
constexpr Unit::Flags OVERRIDE = 1u << 11;
constexpr Unit::Flags CONST = 1u << 12;
constexpr Unit::Flags PARTIAL = 1u << 13;
}
}


#endif // MODIFIERS_H
