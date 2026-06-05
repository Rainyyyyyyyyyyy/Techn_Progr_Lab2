#ifndef IUNITFACTORY_H
#define IUNITFACTORY_H


#include <memory>


#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"


class IUnitFactory {
public:
    virtual ~IUnitFactory() = default;
    // фабрика для создания класса
    virtual std::shared_ptr< generator::ClassUnit > createClassUnit( const std::string& name ) const = 0;
    // фабрика для создания метода
    virtual std::shared_ptr< generator::MethodUnit > createMethodUnit( const std::string& name, const std::string& returnType, Unit::Flags flags ) const = 0;
    // фабрика для создания метода-вывода
    virtual std::shared_ptr< generator::PrintOperatorUnit > createPrintOperatorUnit( const std::string& text ) const = 0;
};


#endif // IUNITFACTORY_H
