#pragma once

#include <variant>

enum EType
{
	kVoid,
	kBool,
	kInt,
	kMax
};

// This would've been safer if array designators weren't deprecated in C++...
constexpr static char const *kTypeDiesel[ kMax ] =
{
	"void",
	"bool",
	"int"
};