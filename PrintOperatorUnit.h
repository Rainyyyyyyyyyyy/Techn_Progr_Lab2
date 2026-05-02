#ifndef PRINT_OPERATOR_UNIT_H
#define PRINT_OPERATOR_UNIT_H


#include "Unit.h"

#include <string>

class PrintOperatorUnit : public Unit {
public:
    explicit PrintOperatorUnit( const std::string& text );
    std::string compile( unsigned int level = 0 ) const override;

private:
    std::string m_text;
};


#endif // PRINT_OPERATOR_UNIT_H
