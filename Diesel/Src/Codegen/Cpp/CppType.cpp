#include "CppType.hpp"
#include <sstream>

std::string CCppType::get( )
{
	std::stringstream str;

	// Start with the type itself
	if( auto type = m_type; type != kNone )
		str << kTypeCpp[ type ];
	else
		return std::string{ };

	// If const, then it means it's at the last indirection level
	if( m_indirection > 0 )
	{
		// Only runs if there's more than one indirection
		for( auto i = 0; i < m_indirection - 1; ++i )
			str << '*';

		// Universal
		if( m_const == kConst )
			str << "const*";
		else if( m_const == kAtConst )
			str << "*const";
		else // No const
			str << '*';
	}
	else
	{
		str << " const";
	}

	if( m_reference )
	{
		if( m_const == kAtConst ) // Const and pointer can't be after reference
			return std::string{ };

		str << '&';
	}

	return str.str( );
}
