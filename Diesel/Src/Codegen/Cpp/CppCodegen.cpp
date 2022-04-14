#include "../Codegen.h"

#include <optional>

namespace detail
{
	constexpr static char const *kCodeExtension = ".cpp";
	constexpr static char const *kHeaderExtension = ".h";
	constexpr static char const *kType[ kMax ] ={
		"void",
		"bool",
		"int"
	};
}

CCppCodegen::CCppCodegen( std::ifstream &&fileHandle, bool headerGuard, bool splitFiles )
	: m_fileHandle( std::move( fileHandle ) ), m_headerGuard( headerGuard ), m_splitFiles( splitFiles )
{
	m_codeBuf.emplace( kHeader, std::stringstream{} );

	if( m_splitFiles )
		m_codeBuf.emplace( kCode, std::stringstream{} );
}

CInterface &CCppCodegen::openInterface( std::string const &name )
{
	return ICodegen::openInterface( name );
}

void CCppCodegen::saveFiles( std::string const &moduleName, std::filesystem::path const &to )
{
	// Prepare code buffers
	processData( );

	auto headerName = moduleName + detail::kHeaderExtension;
	std::ofstream header( to / headerName, std::ofstream::out );

	// Standard header guard notation...
	auto guardName = moduleName + "_H";
	std::ranges::for_each( guardName, [ ]( auto &c )
	{
		c = std::toupper( c );
	} );

	// Declare the start of the header
	if( m_headerGuard )
		header << "#ifndef " << guardName << std::endl
		<< "#define " << guardName << std::endl;
	else
		header << "#pragma once" << std::endl;

	// Include some relevancies
	header << "#include <cstdint>" << std::endl
		// Write relevant interfaces and prototypes
		<< std::endl << m_codeBuf[ kHeader ].str( ) << std::endl;

	// Write code in header if single file
	// (1) NOTE: omits user-defined constructs, you have to take care of that
	if( !m_splitFiles )
		header << m_codeBuf[ kCode ].str( ) << std::endl;

	// Close statement...
	if( m_headerGuard )
		header << "#endif // " << guardName;

	header.close( );

	// (1) Ditto
	if( m_splitFiles )
	{
		std::ofstream code( to / ( moduleName + detail::kCodeExtension ), std::ofstream::out );
		code << "#include " << std::quoted( headerName ) << std::endl
			<< std::endl << m_codeBuf[ kCode ].str( );
		code.close( );
	}
}

void CCppCodegen::processData( )
{
	auto &header = m_codeBuf[ kHeader ];
	auto &code = m_codeBuf[ kCode ];

	auto writePrototype = [ ]( std::stringstream &stream, std::string const &functionName, std::unique_ptr<IFunction> const &fn, std::optional<std::string> className = std::nullopt )
	{
		stream <<
			// Declare prototype
			detail::kType[ fn->m_returnType ] << ' ' << ( className ? ( className.value( ) + "::" ) : "" ) << functionName << '(';

		// NOTE: ugly... wow...
		for( auto i = 0; i < fn->m_arguments.size( ); ++i )
		{
			// If className => code stream
			if( className )
				// Write arg. list and name arguments
				stream << detail::kType[ fn->m_arguments[ i ] ] << "arg" << i << ( ( i != ( fn->m_arguments.size( ) - 1 ) ) ? ", " : "" );
			else
				// Write arg. list and don't name arguments
				stream << detail::kType[ fn->m_arguments[ i ] ] << ( ( i != ( fn->m_arguments.size( ) - 1 ) ) ? ", " : "" );
		}

		stream << ')';
	};

	for( auto const &[className, interf] : m_interfaces )
	{
		// Open class
		header << "class " << className << " {" << std::endl
			<< "public:" << std::endl;

		for( auto const &[fnName, fn] : interf.m_functions )
		{
			bool skip = false;
			skip = skip || ( dynamic_cast< CGetterFunction * >( fn.get( ) ) // verify if class is CGetterFunction by RTTI
							 // yes = dynamic_cast works, nay = returns nullptr => short circuit
							 && ( fn->m_arguments.size( ) > 0 || fn->m_returnType == kVoid ) );

			if( skip )
			{
				// TODO: some warning?
				continue;
			}

			header << '\t';
			writePrototype( header, fnName, fn );
			header << ';' << std::endl;

			// If not user defined function
			if( auto const &string = fn->get( ); !string.empty( ) )
			{
				writePrototype( code, fnName, fn, className );
				code << " {" << std::endl
					<< '\t' << string << std::endl
					<< '}';
			}
		}

		// Close class
		header << "};";
	}
}