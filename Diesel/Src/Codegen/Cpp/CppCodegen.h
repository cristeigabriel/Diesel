#pragma once

#include "../Codegen.h"
#include "CppFunction.h"

class CCppCodegen final : public ICodegen
{
	public:
	CCppCodegen( ) = default;
	CCppCodegen( std::filesystem::path const &path, bool headerGuard, bool splitFiles );
	~CCppCodegen( ) override = default;

	enum EFileType : File_t
	{
		// Universal interface
		kHeader,
		// Codegen optional split output
		kCode
	};

	CInterface &openInterface( std::string const &name, std::ptrdiff_t ptrDiff, std::uintptr_t base = 0 ) override;
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