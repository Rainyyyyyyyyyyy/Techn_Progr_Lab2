#include <iostream>
#include <memory>

#include "CppUnitFactory.h"

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



int main(int argc, char *argv[])
{
    CppUnitFactory factory;
    std::cout << generateProgram( factory ) << std::endl;
    return 0;
}
