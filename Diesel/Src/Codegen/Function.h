#pragma once

#include <string>
#include <vector>

#include "../Shared/Typesys.h"

class IFunction
{
	public:
	IFunction( ) = default;
	virtual ~IFunction( )
	{
	}

	/// <summary>
	/// Get the function body, empty if none (user defined function)
	/// </summary>
	/// <returns></returns>
	virtual std::string get( ) = 0;

	public:
	EType m_returnType{ kVoid };
	std::vector<EType> m_arguments{ };
};

class IUserDefinedFunction : public IFunction
{
	public:
	IUserDefinedFunction( ) = default;
	IUserDefinedFunction( EType type, std::vector<EType> &&arguments );
};

class IGetterFunction : public IFunction
{
	public:
	IGetterFunction( ) = default;
	IGetterFunction( EType type, std::vector<EType> &&arguments, std::ptrdiff_t ptrDiff );

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
	IVirtualTableFunction( EType type, std::vector<EType> &&arguments, ECallingConvention callingConvention, std::uint32_t index );

	protected:
	std::uint32_t m_index{ };
	ECallingConvention m_callingConvention{ };
};