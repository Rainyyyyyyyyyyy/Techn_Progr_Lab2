#include "MethodUnit.h"

#include "CodeGenerationUtils.h"
#include "Modifiers.h"

#include <utility>


MethodUnit::MethodUnit( std::string name, std::string returnType, TargetLanguage language, Unit::Flags flags, std::string parameters )
    : m_name( std::move( name ) ),
      m_returnType( std::move( returnType ) ),
      m_language( language ),
      m_flags( flags ),
      m_parameters( std::move( parameters ) )
{ }

void MethodUnit::add( const std::shared_ptr< Unit >& unit) {
    m_body.push_back( unit );
}

#include <iostream>
std::string MethodUnit::compile( unsigned int level ) const
{


    std::string result = generateShift( level );

    if(hasForbiddenAccessFlags(m_flags, m_language)){
        throw std::invalid_argument("has forbidden AccessFlags("+m_name+"): "+std::to_string(m_flags));
    }
    const std::string accessModifier = renderAccessModifier( m_language, m_flags, false );
    if( !accessModifier.empty() ) {
        result += accessModifier + ' ';
    }


    if(hasForbiddenMethodFlags(m_flags, m_language)){
        throw std::invalid_argument("has forbidden MethodFlags("+m_name+"): "+std::to_string(m_flags));
    }
    const std::string methodModifiers = renderMethodModifiers( m_language, m_flags );
    if( !methodModifiers.empty() ) {
        result += methodModifiers + ' ';
    }


    result += m_returnType + ' ' + m_name + '(' + m_parameters + ')';



    const bool isAbstract = hasFlag( m_flags, Modifiers::Method::ABSTRACT ) && m_language != TargetLanguage::Cpp;
    if( isAbstract ) {
        result += ";\n";
        return result;
    }

    if( m_language == TargetLanguage::Cpp && hasFlag( m_flags, Modifiers::Method::CONST ) ) {
        result += " const ";
    }

    if(hasFlag(m_flags, Modifiers::Method::FINAL)){
        if(m_language == TargetLanguage::Cpp){
            result += " final ";
        }
         if(m_language == TargetLanguage::Java){
            result =  " final " + result;
        }
    }
    result += " {\n";
    for( const auto& bodyUnit : m_body ) {
        result += bodyUnit->compile( level + 1 );
    }
    result += generateShift( level ) + "}\n";
    return result;
}


