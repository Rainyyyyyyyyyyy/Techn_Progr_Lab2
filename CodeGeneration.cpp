#include "CodeGeneration.h"

#include "ClassUnit.h"
#include "CodeGenerationUtils.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"
#include "StatementUnit.h"

#include <memory>
#include <stdexcept>
#include <string>

namespace generator {
namespace {

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

} // namespace

std::string buildProgram( const ICodeFactory& factory )
{
    using namespace Modifiers;

    const TargetLanguage language = factory.language();
    const std::string className = "MyClass";

    Unit::Flags classFlags = 0;
    if( language == TargetLanguage::CSharp ) {
        classFlags = PUBLIC | PARTIAL;
    } else if( language == TargetLanguage::Java ) {
        classFlags = PUBLIC | FINAL;
    }

    auto myClass = factory.createClassUnit( className, classFlags );

    myClass->add(
        factory.createMethodUnit( "testFunc1", "void", PUBLIC ),
        PUBLIC
        );

    myClass->add(
        factory.createMethodUnit( "testFunc2", "void", PRIVATE | STATIC ),
        PRIVATE
        );

    Unit::Flags testFunc3Flags = PUBLIC;
    if( language == TargetLanguage::Cpp ) {
        testFunc3Flags |= VIRTUAL | CONST;
    } else if( language == TargetLanguage::CSharp ) {
        testFunc3Flags |= VIRTUAL;
    } else {
        testFunc3Flags |= FINAL;
    }

    myClass->add(
        factory.createMethodUnit( "testFunc3", "void", testFunc3Flags ),
        PUBLIC
        );

    auto printMethod = factory.createMethodUnit( "testFunc4", "void", PUBLIC | STATIC );
    printMethod->add( factory.createPrintOperatorUnit( R"(Hello, world!\n)" ) );
    myClass->add( printMethod, PUBLIC );

    if( language == TargetLanguage::CSharp ) {
        auto mainMethod = factory.createMethodUnit( "Main",
                                                    "void",
                                                    PUBLIC | STATIC,
                                                    "string[] args" );
        mainMethod->add( factory.createStatementUnit( "testFunc4();" ) );
        myClass->add( mainMethod, PUBLIC );
        return std::string( "using System;\n\n" ) + myClass->compile();
    }

    if( language == TargetLanguage::Java ) {
        auto mainMethod = factory.createMethodUnit( "main",
                                                    "void",
                                                    PUBLIC | STATIC,
                                                    "String[] args" );
        mainMethod->add( factory.createStatementUnit( "testFunc4();" ) );
        myClass->add( mainMethod, PUBLIC );
        return myClass->compile();
    }

    std::string result = "#include <cstdio>\n\n";
    result += myClass->compile();
    result += "\nint main() {\n";
    result += factory.createStatementUnit( "MyClass::testFunc4();" )->compile( 1 );
    result += factory.createStatementUnit( "return 0;" )->compile( 1 );
    result += "}\n";
    return result;
}

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

} // namespace generator
