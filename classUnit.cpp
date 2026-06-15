#include "ClassUnit.h"

#include "CodeGenerationUtils.h"
#include "Modifiers.h"

#include <array>
#include <utility>


ClassUnit::ClassUnit( std::string name, TargetLanguage language, Unit::Flags flags )
    : m_name( std::move( name ) ), m_language( language ), m_flags( flags ) { }

void ClassUnit::add( const std::shared_ptr< Unit >& unit)
{
    //hasForbiddenFlags()
    m_members.push_back( unit );
}
#include <iostream>
std::string ClassUnit::compile( unsigned int level ) const
{
    std::string result = generateShift( level );

    const std::string classAccess = renderAccessModifier( m_language, m_flags, true );
    if( !classAccess.empty() ) {
        result += classAccess + ' ';
    }

    const std::string classModifiers = renderClassModifiers( m_language, m_flags );
    if( !classModifiers.empty() ) {
        result += classModifiers + ' ';
    }

    result += "class " + m_name + " {\n";

    for( const auto& member : m_members ) {
            result += member->compile( level + 1 );
    }

    result += generateShift( level ) + "}\n";
    return result;
}

