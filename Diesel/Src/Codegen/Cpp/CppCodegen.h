#pragma once

#include "../Codegen.h"
#include "CppFunction.h"

class CCppCodegen final : public ICodegen
{
	public:
	CCppCodegen( ) = default;
	CCppCodegen( std::ifstream &&fileHandle, bool headerGuard, bool splitFiles );
	~CCppCodegen( ) override = default;

	enum EFileType : File_t
	{
		// Universal interface
		kHeader,
		// Codegen optional split output
		kCode
	};

	CInterface &openInterface( std::string const &name ) override;
	void saveFiles( std::string const &moduleName, std::filesystem::path const &to ) override;

	private:
	/// <summary>
	/// Generate C++ content from Diesel content
	/// </summary>
	void processData( );

	std::ifstream m_fileHandle;
	bool m_headerGuard{ false };
	bool m_splitFiles{ false };
};