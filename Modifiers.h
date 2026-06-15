#ifndef MODIFIERS_H
#define MODIFIERS_H


#include "Unit.h"

#include <type_traits>


namespace Modifiers {

namespace Access {
    constexpr Unit::Flags PUBLIC = 1 << 0;     ///< Публичный модификатор доступа.
    constexpr Unit::Flags PROTECTED = 1 << 1;  ///< Защищённый модификатор доступа.
    constexpr Unit::Flags PRIVATE = 1 << 2;    ///< Приватный модификатор доступа.
    constexpr Unit::Flags INTERNAL = 1 << 3;              ///< Доступ из текущей сборки (C#).
};

namespace Method {
    constexpr Unit::Flags STATIC = 1 << 4;                                    // Статический метод
    constexpr Unit::Flags CONST = 1 << 5;                                     // Const метод
    constexpr Unit::Flags VIRTUAL = 1 << 6;                                   // Виртуальный метод
    constexpr Unit::Flags FINAL = 1 << 7;                                     //  Final метод в Java / C#
    constexpr Unit::Flags ABSTRACT= 1 << 8;                                   // Abstract метод в Java / C#
};



namespace Class {
    constexpr Unit::Flags  FINAL = 1 << 9;                                   // Final класс в Java / C#
    constexpr Unit::Flags  ABSTRACT = 1 << 10;                                // Abstract класс в Java/C#
    constexpr Unit::Flags  ABSTRACT_FINAL = ABSTRACT | FINAL;  // Комбинация abstract + final.
};


namespace Field {
    constexpr Unit::Flags STATIC = 1 << 11;                                   // Статическое поле
    constexpr Unit::Flags CONST = 1 << 12;                                    // Const(с++)/readonly(С#)/final поле
};
} // namespace Modifiers






#endif // MODIFIERS_H
