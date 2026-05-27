#ifndef CLASS_UNIT_H
#define CLASS_UNIT_H


#include "TargetLanguage.h"
#include "Unit.h"

#include <memory>
#include <string>
#include <vector>

namespace generator {

class ClassUnit : public Unit {
public:
    explicit ClassUnit( std::string name, TargetLanguage language, Unit::Flags flags = 0 );

    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override;
    std::string compile( unsigned int level = 0 ) const override;

private:
    // вспомогательные структура для член-данных и член-функций через Unit
    struct Member {
        std::shared_ptr< Unit > unit;
        Flags accessFlags;
    };

    std::string m_name; // название
    TargetLanguage m_language;  // язык
    Unit::Flags m_flags;    // флаги
    std::vector< Member > m_members;    // член-данные и член-функции
};
// по-сути будет построено дерево из вложенных друг в друга сущностей
// classUnit
//  + MethodUnit
//  +   + StatementUnit
//  + MethodUnit
//  +   + StatementUnit
//  ...
}


#endif // CLASS_UNIT_H
