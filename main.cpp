#include <iostream>
#include <memory>
#include <string>

#include "CodeGeneration.h"


/*
std::string generateProgram( const IUnitFactory& factory )
{
    auto myClass = factory.createClassUnit( "MyClass" );
    myClass->add(factory.createMethodUnit( "testFunc1", "void", 0 ), ClassUnit::PUBLIC);
    myClass->add(factory.createMethodUnit( "testFunc2", "void", MethodUnit::STATIC ), ClassUnit::PRIVATE);
    myClass->add(factory.createMethodUnit( "testFunc3", "void", MethodUnit::VIRTUAL | MethodUnit::CONST ), ClassUnit::PUBLIC);


    auto method = factory.createMethodUnit( "testFunc4", "void", MethodUnit::STATIC );
    method->add( factory.createPrintOperatorUnit( R"(Hello, world!\n)" ) );
    myClass->add( method, ClassUnit::PROTECTED );
    return myClass->compile();
}


*/
#include "Modifiers.h"
#include "TargetLanguage.h"

std::string buildProgram( const ICodeFactory& factory )
{
    using namespace Modifiers;

    const TargetLanguage language = factory.language();
    const std::string className = "MyClass";

    Unit::Flags classFlags = 0;
    if( language == TargetLanguage::CSharp ) { classFlags = PUBLIC | PARTIAL; }
    else if( language == TargetLanguage::Java ) { classFlags = PUBLIC | FINAL; }

    auto myClass = factory.createClassUnit( className, classFlags );
    myClass->add(factory.createMethodUnit( "testFunc1", "void", PUBLIC ), PUBLIC);
    myClass->add(factory.createMethodUnit( "testFunc2", "void", PRIVATE | STATIC ), PRIVATE );

    Unit::Flags testFunc3Flags = PUBLIC;
    if( language == TargetLanguage::Cpp ) { testFunc3Flags |= VIRTUAL | CONST; }
    else if( language == TargetLanguage::CSharp ) { testFunc3Flags |= VIRTUAL; }
    else { testFunc3Flags |= FINAL; }

    myClass->add(factory.createMethodUnit( "testFunc3", "void", testFunc3Flags ), PUBLIC );

    auto printMethod = factory.createMethodUnit( "testFunc4", "void", PUBLIC | STATIC );
    printMethod->add( factory.createPrintOperatorUnit( "Hello, world!\\n" ) );
    myClass->add( printMethod, PUBLIC );

    if( language == TargetLanguage::CSharp ) {
        auto mainMethod = factory.createMethodUnit( "Main", "void", PUBLIC | STATIC,  "string[] args" );
        mainMethod->add( factory.createStatementUnit( "testFunc4();" ) );
        myClass->add( mainMethod, PUBLIC );
        return std::string( "using System;\n\n" ) + myClass->compile();
    }

    if( language == TargetLanguage::Java ) {
        auto mainMethod = factory.createMethodUnit( "main", "void", PUBLIC | STATIC,  "String[] args" );
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




int main(int argc, char *argv[])
{
    try {
        TargetLanguage language = TargetLanguage::Java;

        const std::unique_ptr< ICodeFactory > factory = createFactory( language );
        std::cout << buildProgram( *factory ) << std::endl;
    } catch( const std::exception& error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }


    //CppUnitFactory factory;
    //std::cout << generateProgram( factory ) << std::endl;
    return 0;
}
