#pragma once

#include "../Function.h"

constexpr static char const *kTypeCpp[ kMax ] ={
	"void",
	"bool",
	"int"
};

class CCppUserDefinedFunction : public IUserDefinedFunction
{
	public:
	using IUserDefinedFunction::IUserDefinedFunction;
	~CCppUserDefinedFunction( ) override = default;

	std::string get( ) override;
};

class CCppGetterFunction : public IGetterFunction
{
	public:
	using IGetterFunction::IGetterFunction;
	~CCppGetterFunction( ) override = default;

	std::string get( ) override;
};

class CCppVirtualTableFunction : public IVirtualTableFunction
{
	public:
	using IVirtualTableFunction::IVirtualTableFunction;
	~CCppVirtualTableFunction( ) override = default;

	std::string get( ) override;
};