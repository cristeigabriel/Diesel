#pragma once

#include <string>
#include <vector>

#include "../Shared/Typesys.h"

class IFunction
{
	public:
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

class IGetterFunction : public IFunction
{
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

	protected:
	std::uint32_t m_index{ };
	ECallingConvention m_callingConvention{ };
};