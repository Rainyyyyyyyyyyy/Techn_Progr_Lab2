#include "StatementUnit.h"

#include <utility>



StatementUnit::StatementUnit( std::string text ) : m_text( std::move( text ) ) { }

std::string StatementUnit::compile( unsigned int level ) const
{
    return generateShift( level ) + m_text + "\n";
}

