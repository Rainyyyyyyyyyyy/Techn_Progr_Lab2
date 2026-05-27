#include "PrintOperatorUnit.h"

#include "CodeGenerationUtils.h"

#include <utility>

namespace generator {

PrintOperatorUnit::PrintOperatorUnit( std::string text, TargetLanguage language )
    : m_text( std::move( text ) ), m_language( language ) { }

std::string PrintOperatorUnit::compile( unsigned int level ) const
{
    return generateShift( level ) + renderPrintStatement( m_language, m_text ) + "\n";
}

} // namespace generator
