#include "ClassUnit.h"

#include "CodeGenerationUtils.h"
#include "Modifiers.h"

#include <array>
#include <utility>

namespace generator {

ClassUnit::ClassUnit( std::string name, TargetLanguage language, Unit::Flags flags )
    : m_name( std::move( name ) ), m_language( language ), m_flags( flags ) { }

void ClassUnit::add( const std::shared_ptr< Unit >& unit, Flags flags )
{
    m_members.push_back( { unit, flags } );
}

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

    if( m_language == TargetLanguage::Cpp ) {
        static const std::array< std::pair< Flags, const char* >, 3 > ACCESS_ORDER = {{
            { Modifiers::PUBLIC, "public" },
            { Modifiers::PROTECTED, "protected" },
            { Modifiers::PRIVATE, "private" }
        }};

        for( const auto& access : ACCESS_ORDER ) {
            bool hasMembers = false;
            for( const auto& member : m_members ) {
                if( member.accessFlags == access.first ) {
                    hasMembers = true;
                    break;
                }
            }
            if( !hasMembers ) {
                continue;
            }

            result += generateShift( level + 1 ) + access.second + ":\n";
            for( const auto& member : m_members ) {
                if( member.accessFlags == access.first ) {
                    result += member.unit->compile( level + 2 );
                }
            }
            result += "\n";
        }
    } else {
        for( const auto& member : m_members ) {
            result += member.unit->compile( level + 1 );
        }
    }

    result += generateShift( level ) + "}\n";
    return result;
}

} // namespace generator
