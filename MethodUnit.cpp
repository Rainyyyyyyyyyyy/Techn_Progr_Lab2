#include "MethodUnit.h"

#include "CodeGenerationUtils.h"
#include "Modifiers.h"

#include <utility>

namespace generator {

MethodUnit::MethodUnit( std::string name,
                        std::string returnType,
                        TargetLanguage language,
                        Unit::Flags flags,
                        std::string parameters )
    : m_name( std::move( name ) ),
      m_returnType( std::move( returnType ) ),
      m_language( language ),
      m_flags( flags ),
      m_parameters( std::move( parameters ) )
{ }

void MethodUnit::add( const std::shared_ptr< Unit >& unit, Flags /* flags */ )
{
    m_body.push_back( unit );
}

std::string MethodUnit::compile( unsigned int level ) const
{
    std::string result = generateShift( level );

    const std::string accessModifier = renderAccessModifier( m_language, m_flags, false );
    if( !accessModifier.empty() ) {
        result += accessModifier + ' ';
    }

    const std::string methodModifiers = renderMethodModifiers( m_language, m_flags );
    if( !methodModifiers.empty() ) {
        result += methodModifiers + ' ';
    }

    result += m_returnType + ' ' + m_name + '(' + m_parameters + ')';

    if( m_language == TargetLanguage::Cpp && hasFlag( m_flags, Modifiers::CONST ) ) {
        result += " const";
    }

    const bool isAbstract = hasFlag( m_flags, Modifiers::ABSTRACT ) && m_language != TargetLanguage::Cpp;
    if( isAbstract ) {
        result += ";\n";
        return result;
    }

    result += " {\n";
    for( const auto& bodyUnit : m_body ) {
        result += bodyUnit->compile( level + 1 );
    }
    result += generateShift( level ) + "}\n";
    return result;
}

} // namespace generator
