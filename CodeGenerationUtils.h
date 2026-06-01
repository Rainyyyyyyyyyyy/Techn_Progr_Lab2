#ifndef CODE_GENERATION_UTILS_H
#define CODE_GENERATION_UTILS_H


#include "TargetLanguage.h"
#include "Unit.h"

#include <string>
#include <vector>


// проверить флаги
bool hasFlag( Unit::Flags flags, Unit::Flags flag );

// экранирование кавычек
std::string escapeStringLiteral( const std::string& text );

// склеиваем modifiers через пробел ({"public", "static"} -> "public static")
std::string joinModifiers( const std::vector< std::string >& modifiers );

//получить модификатор доступа из языка language
std::string renderAccessModifier( TargetLanguage language, Unit::Flags flags, bool classLevel );

// получить модификатор класса из языка language
std::string renderClassModifiers( TargetLanguage language, Unit::Flags flags );

// получить модификатор метода из языка language
std::string renderMethodModifiers( TargetLanguage language, Unit::Flags flags );

// получить оператор вывода из языка language
std::string renderPrintStatement( TargetLanguage language, const std::string& text );



#endif // CODE_GENERATION_UTILS_H
