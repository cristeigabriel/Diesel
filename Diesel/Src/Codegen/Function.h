#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../Shared/Typesys.h"

class IFunction
{
	public:
	IFunction( ) = default;
	virtual ~IFunction( ) = 0;

	/// <summary>
	/// Get the function body, empty if none (user defined function)
	/// </summary>
	/// <returns></returns>
	virtual std::string get( ) = 0;

	public:
	std::shared_ptr<IType> m_returnType;
	std::vector<std::shared_ptr<IType>> m_arguments{ };
};

class IUserDefinedFunction : public IFunction
{
	public:
	IUserDefinedFunction( ) = default;
	IUserDefinedFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments );
};

class IGetterFunction : public IFunction
{
	public:
	IGetterFunction( ) = default;
	IGetterFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments, std::ptrdiff_t ptrDiff );

	protected:
	std::ptrdiff_t m_ptrDiff{ };
};

class IVirtualTableFunction : public IFunction
{
	public:
	enum ECallingConvention
	{
		Thiscall,
		Cdecl
	};

	IVirtualTableFunction( ) = default;
	IVirtualTableFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments, ECallingConvention callingConvention, std::uint32_t index );

	protected:
	std::uint32_t m_index{ };
	ECallingConvention m_callingConvention{ };
};