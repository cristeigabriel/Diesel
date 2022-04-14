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

class CUserDefinedFunction final : public IFunction
{
	public:
	CUserDefinedFunction( ) = default;
	CUserDefinedFunction( EType type, std::vector<EType> &&arguments );
	~CUserDefinedFunction( ) override = default;

	std::string get( ) override;
};

class CGetterFunction final : public IFunction
{
	public:
	CGetterFunction( ) = default;
	CGetterFunction( EType type, std::vector<EType> &&arguments, std::ptrdiff_t ptrDiff );
	~CGetterFunction( ) override = default;

	std::string get( ) override;

	private:
	std::ptrdiff_t m_ptrDiff;
};