#include "CodeGenerationUtils.h"

#include "Modifiers.h"

#include <string>
#include <vector>

namespace generator {

bool hasFlag( Unit::Flags flags, Unit::Flags flag )
{
    return ( flags & flag ) != 0;
}

std::string escapeStringLiteral( const std::string& text )
{
    std::string result;
    result.reserve( text.size() );
    for( const char symbol : text ) {
        if( symbol == '"' ) {
            result += "\\\"";
        } else {
            result += symbol;
        }
    }
    return result;
}

std::string joinModifiers( const std::vector< std::string >& modifiers )
{
    std::string result;
    for( const auto& modifier : modifiers ) {
        if( modifier.empty() ) {
            continue;
        }
        if( !result.empty() ) {
            result += ' ';
        }
        result += modifier;
    }
    return result;
}

std::string renderAccessModifier( TargetLanguage language, Unit::Flags flags, bool classLevel )
{
    switch( language ) {
    case TargetLanguage::Cpp:
        return std::string();
    case TargetLanguage::CSharp:
        if( hasFlag( flags, Modifiers::PUBLIC ) ) {
            return "public";
        }
        if( hasFlag( flags, Modifiers::PRIVATE_PROTECTED ) ) {
            return "private protected";
        }
        if( hasFlag( flags, Modifiers::PROTECTED_INTERNAL ) ) {
            return "protected internal";
        }
        if( hasFlag( flags, Modifiers::PROTECTED ) ) {
            return "protected";
        }
        if( hasFlag( flags, Modifiers::INTERNAL ) ) {
            return "internal";
        }
        return classLevel ? "internal" : "private";
    case TargetLanguage::Java:
        if( hasFlag( flags, Modifiers::PUBLIC ) ) {
            return "public";
        }
        if( hasFlag( flags, Modifiers::PROTECTED ) ) {
            return "protected";
        }
        if( hasFlag( flags, Modifiers::PRIVATE ) ) {
            return "private";
        }
        return std::string();
    }
    return std::string();
}

std::string renderClassModifiers( TargetLanguage language, Unit::Flags flags )
{
    std::vector< std::string > modifiers;
    switch( language ) {
    case TargetLanguage::Cpp:
        break;
    case TargetLanguage::CSharp:
        if( hasFlag( flags, Modifiers::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        if( hasFlag( flags, Modifiers::SEALED ) ) {
            modifiers.push_back( "sealed" );
        }
        if( hasFlag( flags, Modifiers::STATIC ) ) {
            modifiers.push_back( "static" );
        }
        if( hasFlag( flags, Modifiers::PARTIAL ) ) {
            modifiers.push_back( "partial" );
        }
        break;
    case TargetLanguage::Java:
        if( hasFlag( flags, Modifiers::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        if( hasFlag( flags, Modifiers::FINAL ) ) {
            modifiers.push_back( "final" );
        }
        break;
    }
    return joinModifiers( modifiers );
}

std::string renderMethodModifiers( TargetLanguage language, Unit::Flags flags )
{
    std::vector< std::string > modifiers;
    if( hasFlag( flags, Modifiers::STATIC ) ) {
        modifiers.push_back( "static" );
    }

    switch( language ) {
    case TargetLanguage::Cpp:
        if( hasFlag( flags, Modifiers::VIRTUAL ) ) {
            modifiers.push_back( "virtual" );
        }
        break;
    case TargetLanguage::CSharp:
        if( hasFlag( flags, Modifiers::VIRTUAL ) ) {
            modifiers.push_back( "virtual" );
        }
        if( hasFlag( flags, Modifiers::OVERRIDE ) ) {
            modifiers.push_back( "override" );
        }
        if( hasFlag( flags, Modifiers::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        if( hasFlag( flags, Modifiers::SEALED ) ) {
            modifiers.push_back( "sealed" );
        }
        break;
    case TargetLanguage::Java:
        if( hasFlag( flags, Modifiers::FINAL ) ) {
            modifiers.push_back( "final" );
        }
        if( hasFlag( flags, Modifiers::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        //if( hasFlag( flags, Modifiers::SYNCHRONIZED ) ) {
        //    modifiers.push_back( "synchronized" );
        //}
        break;
    }
    return joinModifiers( modifiers );
}

std::string renderPrintStatement( TargetLanguage language, const std::string& text )
{
    const auto escapedText = escapeStringLiteral( text );
    switch( language ) {
    case TargetLanguage::Cpp:
        return "printf( \"" + escapedText + "\" );";
    case TargetLanguage::CSharp:
        return "Console.WriteLine( \"" + escapedText + "\" );";
    case TargetLanguage::Java:
        return "System.out.println( \"" + escapedText + "\" );";
    }
    return std::string();
}

} // namespace generator
