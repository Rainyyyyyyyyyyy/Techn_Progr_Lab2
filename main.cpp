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
int main(int argc, char *argv[])
{
    try {
        generator::TargetLanguage language = generator::TargetLanguage::CSharp;

        const auto factory = generator::createFactory( language );
        std::cout << generator::buildProgram( *factory ) << std::endl;
    } catch( const std::exception& error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }


    //CppUnitFactory factory;
    //std::cout << generateProgram( factory ) << std::endl;
    return 0;
}
