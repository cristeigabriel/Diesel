#pragma once

#include "../Function.h"
#include "CppType.hpp"

class CCppUserDefinedFunction : public IUserDefinedFunction
{
	public:
	//using IUserDefinedFunction::IUserDefinedFunction;
	CCppUserDefinedFunction( std::shared_ptr<IType> &&type, std::vector<std::shared_ptr<IType>> &&arguments );

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