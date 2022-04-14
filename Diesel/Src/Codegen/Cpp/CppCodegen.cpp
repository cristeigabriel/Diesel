#include "CppCodegen.h"

#include <optional>

namespace detail
{
	constexpr static char const *kCodeExtension = ".cpp";
	constexpr static char const *kHeaderExtension = ".h";
}

CCppCodegen::CCppCodegen( std::ifstream &&fileHandle, bool headerGuard, bool splitFiles )
	: m_fileHandle( std::move( fileHandle ) ), m_headerGuard( headerGuard ), m_splitFiles( splitFiles )
{
	m_codeBuf.emplace( kHeader, std::stringstream{} );
	m_codeBuf.emplace( kCode, std::stringstream{} );
}

CInterface &CCppCodegen::openInterface( std::string &&name, std::ptrdiff_t ptrDiff, std::uintptr_t base )
{
	return ICodegen::openInterface( std::move( name ), ptrDiff, base );
}

void CCppCodegen::saveFiles( std::string &&moduleName, std::filesystem::path const &to )
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
		bool ref = ( ( dynamic_cast< CCppGetterFunction * >( fn.get( ) ) ) != nullptr );
		stream <<
			// Declare prototype
			kTypeCpp[ fn->m_returnType ] << ( ref ? "& " : " " ) << ( className ? ( className.value( ) + "::" ) : "" ) << functionName << '(';

		// NOTE: ugly... wow...
		for( auto i = 0; i < fn->m_arguments.size( ); ++i )
		{
			// If className => code stream
			if( className )
				// Write arg. list and name arguments
				stream << kTypeCpp[ fn->m_arguments[ i ] ] << " arg" << i << ( ( i != ( fn->m_arguments.size( ) - 1 ) ) ? ", " : "" );
			else
				// Write arg. list and don't name arguments
				stream << kTypeCpp[ fn->m_arguments[ i ] ] << ( ( i != ( fn->m_arguments.size( ) - 1 ) ) ? ", " : "" );
		}

		stream << ')';
	};

	for( auto const &[className, interf] : m_interfaces )
	{
		// Open class
		header << "class " << className << " {" << std::endl
			<< "public:" << std::endl;

		// Declare getter
		bool hasGetter = interf.m_ptrDiff != 0;
		if( hasGetter )
		{
			header << '\t';

			bool requiresArg = interf.m_base == 0;
			if( requiresArg )
			{
				header << "inline static " << className << "* get(std::uintptr_t base) { " << std::endl
					<< "\t\treturn (" << className << "*)(base + (" << interf.m_ptrDiff << "));" << std::endl
					<< "\t}" << std::endl;
			}
			else
			{
				header << "inline static " << className << "* get() {" << std::endl
					<< "\t\treturn (" << className << "*)(" << interf.m_ptrDiff + interf.m_base << ");" << std::endl
					<< "\t}" << std::endl;
			}
		}

		for( auto const &[fnName, fn] : interf.m_functions )
		{
			bool skip = false;
			skip = skip || std::ranges::any_of( fn->m_arguments, [ ]( auto const &v )
			{
				return v == kVoid; // we can't have void arguments for obvious reason....
			} );
			skip = skip || ( dynamic_cast< IGetterFunction * >( fn.get( ) ) // verify if class is IGetterFunction by RTTI
							 // yes = dynamic_cast works, nay = returns nullptr => short circuit
							 && fn->m_arguments.size( ) > 0 /* getters don't need arguments */ );

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
					<< '}' << std::endl;
			}
		}

		// Close class
		header << "};" << std::endl;
	}
}