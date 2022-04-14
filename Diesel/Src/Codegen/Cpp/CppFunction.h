#pragma once

#include "../Function.h"

constexpr static char const *kTypeCpp[ kMax ] ={
	"void",
	"bool",
	"int"
};

class CCppUserDefinedFunction : public IFunction
{
	public:
	CCppUserDefinedFunction( ) = default;
	CCppUserDefinedFunction( EType type, std::vector<EType> &&arguments );
	~CCppUserDefinedFunction( ) override = default;

	std::string get( ) override;
};

class CCppGetterFunction : public IGetterFunction
{
	public:
	CCppGetterFunction( ) = default;
	CCppGetterFunction( EType type, std::vector<EType> &&arguments, std::ptrdiff_t ptrDiff );
	~CCppGetterFunction( ) override = default;

	std::string get( ) override;
};

class CCppVirtualTableFunction : public IVirtualTableFunction
{
	public:
	CCppVirtualTableFunction( ) = default;
	CCppVirtualTableFunction( EType type, std::vector<EType> &&arguments, ECallingConvention callingConvention, std::uint32_t index );
	~CCppVirtualTableFunction( ) override = default;

	std::string get( ) override;
};