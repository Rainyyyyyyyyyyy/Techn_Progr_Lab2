#include "CodeGenerationUtils.h"

#include "Modifiers.h"

#include <string>
#include <vector>


bool hasForbiddenFlags(Unit::Flags flags){
    switch(flags){
    case Modifiers::Access::PUBLIC: return false;
    case Modifiers::Access::PRIVATE: return false;
    case Modifiers::Access::PROTECTED: return false;


    case Modifiers::Method::STATIC: return false;
    case Modifiers::Method::CONST: return false;
    case Modifiers::Method::VIRTUAL: return false;
    case Modifiers::Method::FINAL: return false;
    case Modifiers::Method::ABSTRACT: return false;

    case Modifiers::Class::FINAL: return false;
    case Modifiers::Class::ABSTRACT: return false;
    case Modifiers::Class::ABSTRACT_FINAL: return false;

    default: return true;
    }
}
bool hasForbiddenAccessFlags(Unit::Flags flags, TargetLanguage language){
    if(language == TargetLanguage::Cpp || language == TargetLanguage::Java){
        switch(flags & 7){
            case Modifiers::Access::PUBLIC: return false;
            case Modifiers::Access::PRIVATE: return false;
            case Modifiers::Access::PROTECTED: return false;

            default: return true;
        }
    }
    if(language == TargetLanguage::CSharp){
        switch(flags & 7){
            case Modifiers::Access::PUBLIC: return false;
            case Modifiers::Access::PRIVATE: return false;
            case Modifiers::Access::PRIVATE | Modifiers::Access::PROTECTED: return false;
            case Modifiers::Access::PROTECTED: return false;
            case Modifiers::Access::PROTECTED | Modifiers::Access::INTERNAL: return false;
            case Modifiers::Access::INTERNAL: return false;

            default: return true;
        }
    }

}


class jopa {

};


bool hasForbiddenMethodFlags(Unit::Flags flags, TargetLanguage language){
    if(language == TargetLanguage::Cpp){
        switch(flags & ((((unsigned int)(~0))>>3)<<3)){
            case 0: return false;
            case Modifiers::Method::STATIC: return false;
            case Modifiers::Method::VIRTUAL: return false;
            case Modifiers::Method::CONST: return false;
            case Modifiers::Method::CONST | Modifiers::Method::VIRTUAL: return false;
            case Modifiers::Method::CONST | Modifiers::Method::VIRTUAL | Modifiers::Method::FINAL: return false;

            default: return true;
        }
    }
    if(language == TargetLanguage::Java){
        switch(flags & ((((unsigned int)(~0))>>3)<<3)){
            case 0: return false;
            case Modifiers::Method::STATIC: return false;
            case Modifiers::Method::FINAL: return false;
            case Modifiers::Method::ABSTRACT: return false;
            case Modifiers::Method::STATIC | Modifiers::Method::FINAL: return false;

            default: return true;
        }
    }
    if(language == TargetLanguage::CSharp){
        switch(flags & ((((unsigned int)(~0))>>3)<<3)){
            case 0: return false;
            case Modifiers::Method::STATIC: return false;
            case Modifiers::Method::VIRTUAL: return false;
            case Modifiers::Method::ABSTRACT: return false;
            case Modifiers::Method::VIRTUAL | Modifiers::Method::ABSTRACT: return false;

            default: return true;
        }
    }
}


bool hasSuffixFlags(Unit::Flags flags, TargetLanguage language){
    if(language == TargetLanguage::Cpp){
        switch(flags & ((((unsigned int)(~0))>>3)<<3)){
            case Modifiers::Method::CONST: return true;
            case Modifiers::Method::FINAL: return true;
            case Modifiers::Method::CONST | Modifiers::Method::FINAL: return true;

            default: return false;
        }
    }
    if(language == TargetLanguage::Java){
        switch(flags & ((((unsigned int)(~0))>>3)<<3)){
            case Modifiers::Method::FINAL: return true;

            default: return false;
        }
    }

    return false;
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
    case TargetLanguage::Cpp: return std::string();
    case TargetLanguage::CSharp:
        if( hasFlag( flags, Modifiers::Access::PUBLIC ) ) {
            return "public";
        }
        if( hasFlag( flags, Modifiers::Access::PROTECTED ) ) {
            return "protected";
        }
        if( hasFlag( flags, Modifiers::Access::INTERNAL ) ) {
            return "internal";
        }
        return classLevel ? "internal" : "private";
    case TargetLanguage::Java:
        if( hasFlag( flags, Modifiers::Access::PUBLIC ) ) {
            return "public";
        }
        if( hasFlag( flags, Modifiers::Access::PROTECTED ) ) {
            return "protected";
        }
        if( hasFlag( flags, Modifiers::Access::PRIVATE ) ) {
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
        if( hasFlag( flags, Modifiers::Method::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        if( hasFlag( flags, Modifiers::Method::STATIC ) ) {
            modifiers.push_back( "static" );
        }
        break;
    case TargetLanguage::Java:
        if( hasFlag( flags, Modifiers::Method::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        if( hasFlag( flags, Modifiers::Method::FINAL ) ) {
            modifiers.push_back( "final" );
        }
        break;
    }
    return joinModifiers( modifiers );
}

std::string renderMethodModifiers( TargetLanguage language, Unit::Flags flags )
{
    std::vector< std::string > modifiers;
    if( hasFlag( flags, Modifiers::Method::STATIC ) ) {
        modifiers.push_back( "static" );
    }
    switch( language ) {
    case TargetLanguage::Cpp:
        if( hasFlag( flags, Modifiers::Method::VIRTUAL ) ) {
            modifiers.push_back( "virtual" );
        }
        break;
    case TargetLanguage::CSharp:
        if( hasFlag( flags, Modifiers::Method::VIRTUAL ) ) {
            modifiers.push_back( "virtual" );
        }
        if( hasFlag( flags, Modifiers::Method::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        break;
    case TargetLanguage::Java:
        if( hasFlag( flags, Modifiers::Method::FINAL ) ) {
            modifiers.push_back( "final" );
        }
        if( hasFlag( flags, Modifiers::Method::ABSTRACT ) ) {
            modifiers.push_back( "abstract" );
        }
        break;
    }
    return joinModifiers( modifiers );
}

std::string renderFieldModifiers( TargetLanguage language, Unit::Flags flags )
{
    std::vector< std::string > modifiers;
    if( hasFlag( flags, Modifiers::Field::STATIC ) ) {
        modifiers.push_back( "static" );
    }
    // принцип const\readonly\final схож, но разные служебные слова
    if( hasFlag( flags, Modifiers::Field::CONST ) ) {
        switch( language ) {
        case TargetLanguage::Cpp:
            modifiers.push_back( "const" );
            break;
        case TargetLanguage::CSharp:
            modifiers.push_back( "readonly" );
            break;
        case TargetLanguage::Java:
            modifiers.push_back( "final" );
            break;
        }
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

