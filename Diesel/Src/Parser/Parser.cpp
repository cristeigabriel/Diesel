#include "Parser.h"
#include <iostream>
#include <ranges>
#include "../../Vendor/dsl-pa/include/dsl-pa/dsl-pa.h"

#include "../Codegen/Codegen.h"

CParser::CParser( ICodegen const *self, std::ifstream &stream )
{
	std::string line;
	std::stringstream str;
	str << stream.rdbuf( );
	while( !m_error && std::getline( str, line ) )
	{
		if( line.empty( ) || !std::ranges::any_of( line, [ ]( auto c )
		{
			return( c == ' ' ) || ( c == '\t' );
		} ) )
			continue;

		bool error = false;

		cl::reader_string readerString( line );
		cl::dsl_pa parser( readerString );

		// Not inside class
		if( !m_inScope )
		{
			// Verify if class is being defined
			if( parser.opt_wsp( ) && parser.fixed( "interface" ) )
			{
				// Attributes
				std::uintptr_t base{ 0 };
				std::ptrdiff_t ptrdiff{ 0 };
				std::string name{ };

				if( parser.opt_wsp( ) )
				{
					// If the interface insists to declare attributes
					if( parser.is_get_char( '[' ) )
					{
						// Advance parser and read until closed
						std::string sub;
						if( parser.get_until( &sub, cl::alphabet_char( ']' ) ) )
						{
							for( auto const view : std::views::all( sub ) | std::views::split( std::string{ "," } ) )
							{
								// Instantiate a parser on the substring 
								cl::reader_string subReaderString( std::string( view.begin( ), view.end( ) ) );
								cl::dsl_pa subParser( subReaderString );

								if( subParser.opt_wsp( ) &&
									( ( ( subParser.fixed( "base" ) && subParser.opt_wsp( ) &&
									subParser.is_get_char( '=' ) && subParser.opt_wsp( ) && subParser.get_uint( ( unsigned int * )&base ) ) ) ||
									( ( subParser.fixed( "ptrdiff" ) && subParser.opt_wsp( ) &&
									subParser.is_get_char( '=' ) && subParser.opt_wsp( ) && subParser.get_int( ( int * )&ptrdiff ) ) ) ) )
								{
									std::cout << "base: " << std::hex << base << std::endl;
									std::cout << "diff: " << std::hex << ptrdiff << std::endl;
								}
							}
						}
					}
				}

				if( parser.opt_wsp( ) )
				{
					if( parser.get_fixed( &name, ":" ) )
					{
						std::cout << name << std::endl;
						error = false;
					}
				}
			}
		}

		m_error = error;
	}
}


void CParser::writeTo( ICodegen *self )
{
	if( !m_error )
		for( auto &&[name, fn] : m_interfaces )
			self->writeInterface( name, std::move( fn ) );
}