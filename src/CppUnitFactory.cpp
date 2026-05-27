#include "CppUnitFactory.h"

#include <memory>

std::shared_ptr< ClassUnit > CppUnitFactory::createClassUnit( const std::string& name ) const {
    return std::make_shared< ClassUnit >( name );
}

std::shared_ptr< MethodUnit > CppUnitFactory::createMethodUnit( const std::string& name, const std::string& returnType, Unit::Flags flags ) const {
    return std::make_shared< MethodUnit >( name, returnType, flags );
}

std::shared_ptr< PrintOperatorUnit > CppUnitFactory::createPrintOperatorUnit( const std::string& text ) const {
    return std::make_shared< PrintOperatorUnit >( text );
}
