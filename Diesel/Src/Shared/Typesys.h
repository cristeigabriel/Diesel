#pragma once

#include <variant>
#include <string>

enum EType
{
	kNone = -1,
	kVoid,
	kBool,
	kInt,
	kMax
};

enum EConst
{
	kNotConst,
	kConst,
	kAtConst
};

// This would've been safer if array designators weren't deprecated in C++...
constexpr static char const *kTypeDiesel[ kMax ] =
{
	"void",
	"bool",
	"int"
};

class IType
{
	public:
	IType( ) = default;
	IType( EType type, int indirection = 0, bool reference = false, EConst constness = kNotConst );
	virtual ~IType( ) = 0;

	virtual std::string get( )
	{
		return std::string{ };
	}

	public:
	EType m_type{ kNone };
	int m_indirection{ 0 };
	bool m_reference{ false };
	EConst m_const{ kNotConst };
};