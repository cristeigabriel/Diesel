#pragma once

#include <fstream>
#include <map> 

#include "../Codegen/Interface.h"

namespace cl
{
	class dsl_pa;
}

class ICodegen;

class CParser
{
	public:
	CParser( ) = default;
	CParser( ICodegen const *self, std::ifstream &stream );
	~CParser( ) = default;

	void writeTo( ICodegen *self );

	private:
	bool m_error{ false };
	bool m_inScope{ false };
	std::map<std::string, CInterface> m_interfaces{ };
};