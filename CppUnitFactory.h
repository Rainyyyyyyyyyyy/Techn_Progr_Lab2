#ifndef CPP_UNIT_FACTORY_H
#define CPP_UNIT_FACTORY_H


#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

#include <IUnitFactory.h>
#include <memory>


/*
class IUnitFactory {
public:
    virtual ~IUnitFactory() = default;
    virtual std::shared_ptr< ClassUnit > createClassUnit( const std::string& name ) const = 0;
    virtual std::shared_ptr< MethodUnit > createMethodUnit( const std::string& name, const std::string& returnType, Unit::Flags flags ) const = 0;
    virtual std::shared_ptr< PrintOperatorUnit > createPrintOperatorUnit( const std::string& text ) const = 0;
};
*/

// конкретная фабрика для создания С++ кода
// методы для создания переопределяют интерфейсные (override)
class CppUnitFactory : public IUnitFactory {
public:
    std::shared_ptr< ClassUnit > createClassUnit( const std::string& name ) const override;
    std::shared_ptr< MethodUnit > createMethodUnit( const std::string& name, const std::string& returnType, Unit::Flags flags ) const override;
    std::shared_ptr< PrintOperatorUnit > createPrintOperatorUnit( const std::string& text ) const override;
};


#endif // CPP_UNIT_FACTORY_H
