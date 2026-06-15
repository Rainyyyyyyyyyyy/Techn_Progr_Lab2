#ifndef STATEMENT_UNIT_H
#define STATEMENT_UNIT_H


#include "Unit.h"

#include <string>


class StatementUnit : public Unit {
public:
    explicit StatementUnit( std::string text );

    std::string compile( unsigned int level = 0 ) const override;

private:
    std::string m_text;
};



#endif // STATEMENT_UNIT_H
