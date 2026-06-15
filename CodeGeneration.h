#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H


#include "Modifiers.h"
#include "TargetLanguage.h"
#include "Unit.h"

#include <memory>
#include <string>


class ICodeFactory {
public:
    // деструктор
    virtual ~ICodeFactory() = default;

    // геттер языка (геттер из enum'a)
    virtual TargetLanguage language() const = 0;

    // создать фабрику класса
    virtual std::shared_ptr< Unit > createClassUnit( const std::string& name, Unit::Flags flags = 0 ) const = 0;

    // создать фабрику метода класса
    virtual std::shared_ptr< Unit > createMethodUnit( const std::string& name, const std::string& returnType, Unit::Flags flags = 0, const std::string& parameters = std::string() ) const = 0;

    // создать фабрику поля класса
    virtual std::shared_ptr< Unit > createFieldUnit( const std::string& name, const std::string& fieldType, Unit::Flags flags = 0, const std::string& initializer = std::string() ) const = 0;

    // создать фабрику для оператора вывода
    virtual std::shared_ptr< Unit > createPrintOperatorUnit( const std::string& text ) const = 0;

    // создать фабрику для выражения (вспомогательная, для готовой строки кода)
    virtual std::shared_ptr< Unit > createStatementUnit( const std::string& text ) const = 0;
};


std::string buildProgram( const ICodeFactory& factory );
std::unique_ptr< ICodeFactory > createFactory( TargetLanguage language );
TargetLanguage parseLanguage( const std::string& languageName );



#endif // CODE_GENERATION_H
