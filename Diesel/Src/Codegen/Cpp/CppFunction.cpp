#include "CppFunction.h"
#include <format>
#include <sstream>

constexpr static char const *kCallingConvention[ ] =
{
	"__thiscall",
	"__cdecl"
};

CCppUserDefinedFunction::CCppUserDefinedFunction( EType type, std::vector<EType> &&arguments )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
}

std::string CCppUserDefinedFunction::get( )
{
	return std::string{ };
}

CCppGetterFunction::CCppGetterFunction( EType type, std::vector<EType> &&arguments, std::ptrdiff_t ptrDiff )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
	m_ptrDiff = ptrDiff;
}

std::string CCppGetterFunction::get( )
{
	// Arithmetic from base plus offset (may be positive or negative)
	return std::format( "return (((std::uintptr_t)this) + {});", m_ptrDiff );
}

CCppVirtualTableFunction::CCppVirtualTableFunction( EType type, std::vector<EType> &&arguments, ECallingConvention callingConvention, std::uint32_t index )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
	m_callingConvention = callingConvention;
	m_index = index;
}

std::string CCppVirtualTableFunction::get( )
{
	enum EWhat
	{
		kArgs,
		kTypes
	};

	auto compile = [ this ]( EWhat what )
	{
		std::stringstream str{};
		for( auto i = 0; i < m_arguments.size( ); ++i )
		{
			if( what == kArgs )
				str << "arg" << i << ( ( i != ( m_arguments.size( ) - 1 ) ) ? ", " : "" );
			else if( what == kTypes )
				str << kTypeCpp[ m_arguments[ i ] ] << ( ( i != ( m_arguments.size( ) - 1 ) ) ? ", " : "" );
		}
		return str.str( );
	};

	if( m_arguments.empty( ) )
		return std::format( "return reinterpret_cast<{}({}*)(void*)>(((*(std::uintptr_t**)(this)))[{}])(this);",
							kTypeCpp[ m_returnType ], kCallingConvention[ m_callingConvention ], m_index );
	else
		return std::format( "return reinterpret_cast<{}({}*)(void*, {})>(((*(std::uintptr_t**)(this)))[{}])(this, {});",
							kTypeCpp[ m_returnType ], kCallingConvention[ m_callingConvention ], compile( kTypes ), m_index,
							compile( kArgs ) );
}
