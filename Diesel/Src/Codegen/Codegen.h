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
	virtual CInterface &openInterface( std::string const &name )
	{
		return m_interfaces[ name ];
	}

	/// <summary>
	/// Save a Diesel module to target language generically
	/// </summary>
	/// <param name="moduleName"></param>
	/// <param name="to"></param>
	virtual void saveFiles( std::string const &moduleName, std::filesystem::path const &to ) = 0;

	protected:
	std::unordered_map<File_t, std::stringstream> m_codeBuf{ };
	std::map<std::string, CInterface> m_interfaces{ };
};