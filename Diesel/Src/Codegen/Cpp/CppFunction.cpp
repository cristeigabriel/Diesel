#include "CppFunction.h"
#include <format>
#include <sstream>

constexpr static char const *kCallingConvention[ ] =
{
	"__thiscall",
	"__cdecl"
};

CCppUserDefinedFunction::CCppUserDefinedFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments )
{
	m_returnType = std::move( type );
	m_arguments = std::move( arguments );
}

std::string CCppUserDefinedFunction::get( )
{
	return std::string{ };
}

std::string CCppGetterFunction::get( )
{
	// Arithmetic from base plus offset (may be positive or negative)
	return std::format( "return *({}*)(((std::uintptr_t)this) + {});", m_returnType->get( ), m_ptrDiff );
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
				str << m_arguments[ i ]->get( ) << ( ( i != ( m_arguments.size( ) - 1 ) ) ? ", " : "" );
		}
		return str.str( );
	};

	if( m_arguments.empty( ) )
		return std::format( "return reinterpret_cast<{}({}*)(void*)>(((*(std::uintptr_t**)(this)))[{}])(this);",
							m_returnType->get( ), kCallingConvention[ m_callingConvention ], m_index );
	else
		return std::format( "return reinterpret_cast<{}({}*)(void*, {})>(((*(std::uintptr_t**)(this)))[{}])(this, {});",
							m_returnType->get( ), kCallingConvention[ m_callingConvention ], compile( kTypes ), m_index,
							compile( kArgs ) );
}
