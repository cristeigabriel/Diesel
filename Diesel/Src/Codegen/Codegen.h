#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <filesystem>

// Universal datatype for codebuf ids
using File_t = unsigned int;

#include "Interface.h"

class ICodegen
{
	public:
	virtual ~ICodegen( )
	{
	}

	/// <summary>
	/// Declare a container generically
	/// </summary>
	/// <param name="name"></param>
	/// <param name="ptrDiff"></param>
	/// <param name="base"></param>
	virtual CInterface &openInterface( std::string &&name, std::ptrdiff_t ptrDiff, std::uintptr_t base = 0 )
	{
		return m_interfaces[ name ] = std::move( CInterface( std::move( name ), base, ptrDiff ) );
	}

	void writeInterface( std::string const &name, CInterface &&interf )
	{
		m_interfaces[ name ] = std::move( interf );
	}

	/// <summary>
	/// Save a Diesel module to target language generically
	/// </summary>
	/// <param name="moduleName"></param>
	/// <param name="to"></param>
	virtual void saveFiles( std::string &&moduleName, std::filesystem::path const &to ) = 0;

	protected:
	std::unordered_map<File_t, std::stringstream> m_codeBuf{ };
	std::map<std::string, CInterface> m_interfaces{ };
};