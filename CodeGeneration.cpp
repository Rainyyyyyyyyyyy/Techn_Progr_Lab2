#include "CodeGeneration.h"

#include "ClassUnit.h"
#include "CodeGenerationUtils.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"
#include "StatementUnit.h"

#include <memory>
#include <stdexcept>
#include <string>



class CppCodeFactory : public ICodeFactory {
public:
    TargetLanguage language() const override
    {
        return TargetLanguage::Cpp;
    }

    std::shared_ptr< Unit > createClassUnit( const std::string& name, Unit::Flags flags = 0 ) const override
    {
        return std::make_shared< ClassUnit >( name, TargetLanguage::Cpp, flags );
    }

    std::shared_ptr< Unit > createMethodUnit( const std::string& name,
                                              const std::string& returnType,
                                              Unit::Flags flags = 0,
                                              const std::string& parameters = std::string() ) const override
    {
        return std::make_shared< MethodUnit >( name, returnType, TargetLanguage::Cpp, flags, parameters );
    }

    std::shared_ptr< Unit > createPrintOperatorUnit( const std::string& text ) const override
    {
        return std::make_shared< PrintOperatorUnit >( text, TargetLanguage::Cpp );
    }

    std::shared_ptr< Unit > createStatementUnit( const std::string& text ) const override
    {
        return std::make_shared< StatementUnit >( text );
    }
};

class CSharpCodeFactory : public ICodeFactory {
public:
    TargetLanguage language() const override
    {
        return TargetLanguage::CSharp;
    }

    std::shared_ptr< Unit > createClassUnit( const std::string& name, Unit::Flags flags = 0 ) const override
    {
        return std::make_shared< ClassUnit >( name, TargetLanguage::CSharp, flags );
    }

    std::shared_ptr< Unit > createMethodUnit( const std::string& name,
                                              const std::string& returnType,
                                              Unit::Flags flags = 0,
                                              const std::string& parameters = std::string() ) const override
    {
        return std::make_shared< MethodUnit >( name, returnType, TargetLanguage::CSharp, flags, parameters );
    }

    std::shared_ptr< Unit > createPrintOperatorUnit( const std::string& text ) const override
    {
        return std::make_shared< PrintOperatorUnit >( text, TargetLanguage::CSharp );
    }

    std::shared_ptr< Unit > createStatementUnit( const std::string& text ) const override
    {
        return std::make_shared< StatementUnit >( text );
    }
};

class JavaCodeFactory : public ICodeFactory {
public:
    TargetLanguage language() const override
    {
        return TargetLanguage::Java;
    }

    std::shared_ptr< Unit > createClassUnit( const std::string& name, Unit::Flags flags = 0 ) const override
    {
        return std::make_shared< ClassUnit >( name, TargetLanguage::Java, flags );
    }

    std::shared_ptr< Unit > createMethodUnit( const std::string& name,
                                              const std::string& returnType,
                                              Unit::Flags flags = 0,
                                              const std::string& parameters = std::string() ) const override
    {
        return std::make_shared< MethodUnit >( name, returnType, TargetLanguage::Java, flags, parameters );
    }

    std::shared_ptr< Unit > createPrintOperatorUnit( const std::string& text ) const override
    {
        return std::make_shared< PrintOperatorUnit >( text, TargetLanguage::Java );
    }

    std::shared_ptr< Unit > createStatementUnit( const std::string& text ) const override
    {
        return std::make_shared< StatementUnit >( text );
    }
};


std::unique_ptr< ICodeFactory > createFactory( TargetLanguage language )
{
    switch( language ) {
    case TargetLanguage::Cpp:
        return std::make_unique< CppCodeFactory >();
    case TargetLanguage::CSharp:
        return std::make_unique< CSharpCodeFactory >();
    case TargetLanguage::Java:
        return std::make_unique< JavaCodeFactory >();
    }
    return std::make_unique< CppCodeFactory >();
}

TargetLanguage parseLanguage( const std::string& languageName )
{
    if( languageName == "cpp" || languageName == "c++" ) {
        return TargetLanguage::Cpp;
    }
    if( languageName == "csharp" || languageName == "cs" || languageName == "c#" ) {
        return TargetLanguage::CSharp;
    }
    if( languageName == "java" ) {
        return TargetLanguage::Java;
    }
    throw std::invalid_argument( "Unknown target language: " + languageName );
}


