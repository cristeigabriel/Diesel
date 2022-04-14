#include "Interface.h"

CInterface::CInterface( std::string const &name, std::uintptr_t base, std::ptrdiff_t ptrDiff )
	: m_name( std::move( name ) ), m_base( base ), m_ptrDiff( ptrDiff )
{
}
