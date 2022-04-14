#include "Function.h"

IUserDefinedFunction::IUserDefinedFunction( EType type, std::vector<EType> &&arguments )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
}

IGetterFunction::IGetterFunction( EType type, std::vector<EType> &&arguments, std::ptrdiff_t ptrDiff )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
	m_ptrDiff = ptrDiff;
}

IVirtualTableFunction::IVirtualTableFunction( EType type, std::vector<EType> &&arguments, ECallingConvention callingConvention, std::uint32_t index )
{
	m_returnType = type;
	m_arguments = std::move( arguments );
	m_callingConvention = callingConvention;
	m_index = index;
}