#ifndef METHOD_UNIT_H
#define METHOD_UNIT_H


#include "TargetLanguage.h"
#include "Unit.h"

#include <memory>
#include <string>
#include <vector>


// сущность для конструкции - метод класса
class MethodUnit : public Unit {
public:

    // конструктор
    MethodUnit( std::string name,
                std::string returnType,
                TargetLanguage language,
                Unit::Flags flags,
                std::string parameters = std::string() );

    // добавить конструкцию (функциональную единицу)
    void add( const std::shared_ptr< Unit >& unit, Flags flags = 0 ) override;

    // геттер кода в виде std::string
    std::string compile( unsigned int level = 0 ) const override;

private:
    std::string m_name;     // название
    std::string m_returnType;   // возвращаемый тип
    TargetLanguage m_language;  // язык
    Unit::Flags m_flags;    // флаги (модификаторы)
    std::string m_parameters; // строка аргументов функции
    std::vector< std::shared_ptr< Unit > > m_body; // тело с конструкциями (например, оператор вывода)
};



#endif // METHOD_UNIT_H
