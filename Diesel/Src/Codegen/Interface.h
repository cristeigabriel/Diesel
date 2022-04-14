#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <map>

#include "Function.h"

class CInterface final
{
	public:
	CInterface( ) = default;
	CInterface( std::string const &name, std::uintptr_t base, std::ptrdiff_t ptrDiff );
	~CInterface( ) = default;

	template <typename T, typename... Args>
	void pushFunction( std::string const &name, Args&&... args );

	public:
	std::string m_name{ };
	/// <summary>
	/// If missing, getters will expect an address to module base...
	/// </summary>
	std::uintptr_t m_base{ };
	/// <summary>
	/// If missing, base is expected to be missing too, so there's no getter...
	/// </summary>
	std::ptrdiff_t m_ptrDiff{ };

	std::map<std::string, std::shared_ptr<IFunction>> m_functions{ };
};

#include "Interface.inl"