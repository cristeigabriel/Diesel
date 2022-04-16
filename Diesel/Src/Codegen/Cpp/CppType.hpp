#pragma once

#include "../../Shared/Typesys.h"

constexpr static char const *kTypeCpp[ kMax ] ={
	"void",
	"bool",
	"int"
};

class CCppType final : public IType
{
	public:
	using IType::IType;

	std::string get( ) override;
};