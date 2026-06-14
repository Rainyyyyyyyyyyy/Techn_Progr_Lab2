#include "FieldUnit.h"

#include "CodeGenerationUtils.h"

#include <utility>


FieldUnit::FieldUnit( std::string name, std::string type, TargetLanguage language, Unit::Flags flags, std::string initializer )
    : m_name(name),
      m_type( type ),
      m_language( language ),
      m_flags( flags ),
      m_initializer( std::move( initializer ) )
{ }

std::string FieldUnit::compile( unsigned int level ) const
{
    std::string result = generateShift( level );

    const std::string accessModifier = renderAccessModifier( m_language, m_flags, false );
    if( !accessModifier.empty() ) {
        result += accessModifier + ' ';
    }

    const std::string fieldModifiers = renderFieldModifiers( m_language, m_flags );
    if( !fieldModifiers.empty() ) {
        result += fieldModifiers + ' ';
    }

    result += m_type + ' ' + m_name;
    if( !m_initializer.empty() ) {
        result += " = " + m_initializer;
    }
    result += ";\n";
    return result;
}