#ifndef PRINT_OPERATOR_UNIT_H
#define PRINT_OPERATOR_UNIT_H


#include "TargetLanguage.h"
#include "Unit.h"

#include <string>


class PrintOperatorUnit : public Unit {
public:
    // конструктор
    PrintOperatorUnit( std::string text, TargetLanguage language );
    // геттер кода
    std::string compile( unsigned int level = 0 ) const override;

private:
    std::string m_text; // сообщение
    TargetLanguage m_language; // язык
};



#endif // PRINT_OPERATOR_UNIT_H
