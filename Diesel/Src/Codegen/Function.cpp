#include "Function.h"
#include <format>

CUserDefinedFunction::CUserDefinedFunction( EType type, std::vector<EType> &&arguments )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
}

std::string CUserDefinedFunction::get( )
{
	return std::string{ };
}

CGetterFunction::CGetterFunction( EType type, std::vector<EType> &&arguments, std::ptrdiff_t ptrDiff ) : m_ptrDiff( ptrDiff )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
}

std::string CGetterFunction::get( )
{
	// Arithmetic from base plus offset (may be positive or negative)
	return std::format( "return (((uintptr_t)this) + {});", m_ptrDiff );
}