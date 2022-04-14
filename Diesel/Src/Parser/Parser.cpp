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
			return iswspace( c );
		} ) )
			continue;

		bool error = false;

		cl::reader_string readerString( line );
		cl::dsl_pa parser( readerString );

		// Not inside class
		if( !m_inScope )
		{
		OUTSIDE_SCOPE:
			// Verify if class is being defined
			if( parser.opt_space( ) && parser.fixed( "interface" ) )
			{
				// Attributes
				std::uintptr_t base{ 0 };
				std::ptrdiff_t ptrdiff{ 0 };
				std::string name{ };

				// Flags
				bool should_substr_name = false;

				if( parser.space( ) )
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
								auto str = std::string( view.begin( ), view.end( ) );
								std::cout << str << std::endl;
								// Instantiate a parser on the substring 
								cl::reader_string subReaderString( str );
								cl::dsl_pa subParser( subReaderString );

								if( subParser.opt_space( ) &&
									( ( ( subParser.fixed( "base" ) && subParser.opt_space( ) &&
									subParser.is_get_char( '=' ) && subParser.opt_space( ) && subParser.get_uint( ( unsigned int * )&base ) ) ) ||
									( ( subParser.fixed( "ptrdiff" ) && subParser.opt_space( ) &&
									subParser.is_get_char( '=' ) && subParser.opt_space( ) && subParser.get_int( ( int * )&ptrdiff ) ) ) ) )
								{
									std::cout << "base: " << std::hex << base <<
										' ' << "diff: " << std::hex << ptrdiff << std::endl;
								}
							}
						}
						should_substr_name = true;
					}
				}

				if( parser.opt_space( ) )
				{
					if( parser.get_until( &name, cl::alphabet_char( ':' ) ) )
					{
						// HACK
						size_t off = 0;
						if( should_substr_name )
						{
							off = name.find_first_not_of( ']' );
							if( off == std::string::npos )
								continue; // Error!
						}

						auto iter = name.find_first_not_of( ' ', off );
						if( iter == std::string::npos )
							continue; // Error!

						auto end = name.find_first_of( ' ', iter );
						if( end == std::string::npos )
							end = name.size( );
						else
						{
							auto view = std::string_view{ name.begin( ) + end, name.end( ) };
							if( view.find_first_not_of( ' ' ) != std::string_view::npos || view.find_first_not_of( '\t' ) != std::string_view::npos )
								continue;
						}

						name = name.substr( iter, end );

						std::cout << std::quoted( name ) << std::endl;
						if( std::ranges::any_of( name, [ ]( auto c )
						{
							return iswspace( c );
						} ) )
							continue; // Error!

						m_inScope = true;
						error = false;
					}
				}
			}
		}
		else
		{
			// Broke indent
			if( !parser.space( ) )
			{
				m_inScope = false;
				goto OUTSIDE_SCOPE;
			}
			else
			{

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