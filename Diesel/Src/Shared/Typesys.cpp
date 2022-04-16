#include "Typesys.h"

IType::IType( EType type, int indirection, bool reference, EConst constness )
	: m_type( type ), m_indirection( indirection ), m_reference( reference ), m_const( constness )
{
}
