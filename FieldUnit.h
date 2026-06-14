#ifndef FIELD_UNIT_H
#define FIELD_UNIT_H


#include "TargetLanguage.h"
#include "Unit.h"

#include <memory>
#include <string>


class FieldUnit : public Unit {
public:
    FieldUnit( std::string name, std::string type, TargetLanguage language, Unit::Flags flags, std::string initializer = std::string() );

    std::string compile( unsigned int level = 0 ) const override;

private:
    std::string m_name;
    std::string m_type;
    TargetLanguage m_language;
    Unit::Flags m_flags;
    std::string m_initializer;
};


#endif // FIELD_UNIT_H