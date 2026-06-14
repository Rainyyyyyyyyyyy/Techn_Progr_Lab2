#include <iostream>
#include <memory>
#include <string>

#include "CodeGeneration.h"

#include "Modifiers.h"
#include "TargetLanguage.h"

std::string buildProgram( const ICodeFactory& factory )
{
    const TargetLanguage language = factory.language();
    const std::string className = "MyClass";

    Unit::Flags classFlags = 0;
    if( language == TargetLanguage::CSharp ) { classFlags = Modifiers::Access::PRIVATE | Modifiers::Access::PROTECTED; }
    else if( language == TargetLanguage::Java ) { classFlags = Modifiers::Access::PUBLIC | Modifiers::Class::FINAL; }

    auto myClass = factory.createClassUnit( className, classFlags );

    auto field = factory.createFieldUnit("field1", "int", Modifiers::Access::PRIVATE | Modifiers::Field::STATIC | Modifiers::Field::CONST, "42" );
    myClass->add( field );

    myClass->add(factory.createMethodUnit( "testFunc1", "void", Modifiers::Access::PUBLIC ));
    myClass->add(factory.createMethodUnit( "testFunc2", "void", Modifiers::Access::PRIVATE | Modifiers::Method::STATIC ));


    Unit::Flags testFunc3Flags = Modifiers::Access::PUBLIC; // | Modifiers::Method::CONST;   // | Modifiers::Access::PRIVATE;
    if( language == TargetLanguage::Cpp ) { testFunc3Flags |= Modifiers::Method::VIRTUAL | Modifiers::Method::CONST; }
    else if( language == TargetLanguage::CSharp ) { testFunc3Flags |= Modifiers::Method::VIRTUAL; }
    else { testFunc3Flags |= Modifiers::Method::FINAL; }

    myClass->add(factory.createMethodUnit( "testFunc3", "void", testFunc3Flags ));
    auto printMethod = factory.createMethodUnit( "testFunc4", "void", Modifiers::Access::PUBLIC | Modifiers::Method::STATIC );
    printMethod->add( factory.createPrintOperatorUnit( "Hello, world!\\n" ) );
    myClass->add( printMethod);

    if( language == TargetLanguage::CSharp ) {
        auto mainMethod = factory.createMethodUnit( "Main", "void", Modifiers::Access::PUBLIC | Modifiers::Method::STATIC,  "string[] args" );
        mainMethod->add( factory.createStatementUnit( "testFunc4();" ) );
        myClass->add( mainMethod );
        return std::string( "using System;\n\n" ) + myClass->compile();
    }

    if( language == TargetLanguage::Java ) {
        auto mainMethod = factory.createMethodUnit( "main", "void", Modifiers::Access::PUBLIC | Modifiers::Method::STATIC,  "String[] args" );
        mainMethod->add( factory.createStatementUnit( "testFunc4();" ) );
        myClass->add( mainMethod);
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



int main(int argc, char *argv[])
{
    try {
        TargetLanguage language = TargetLanguage::CSharp;

        const std::unique_ptr< ICodeFactory > factory = createFactory( language );
        std::cout << buildProgram( *factory ) << std::endl;
    } catch( const std::exception& error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }


    return 0;
}
