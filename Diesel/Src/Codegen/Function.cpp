#include "Function.h"

IUserDefinedFunction::IUserDefinedFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments )
{
	m_returnType = std::move( type );
	m_arguments = std::move( arguments );
}

IGetterFunction::IGetterFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments, std::ptrdiff_t ptrDiff )
{
	m_returnType = std::move( type );
	m_arguments = std::move( arguments );
	m_ptrDiff = ptrDiff;
}

IVirtualTableFunction::IVirtualTableFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments, ECallingConvention callingConvention, std::uint32_t index )
{
	m_returnType = std::move( type );
	m_arguments = std::move( arguments );
	m_callingConvention = callingConvention;
	m_index = index;
}