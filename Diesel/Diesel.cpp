#include "Src/Codegen/Codegen.h"

int main( )
{
	auto diesel = std::make_unique<CCppCodegen>( std::ifstream( ), true, true );

	using args = std::vector<EType>;
	auto &interf = diesel->openInterface( "testClass" );
	interf.pushFunction<CUserDefinedFunction>( "func", kVoid, args{ kBool, kInt } );
	interf.pushFunction<CGetterFunction>( "new_func", kInt, args{ }, 0x0 );
	interf.pushFunction<CGetterFunction>( "hopefully_skipped", kInt, args{ kInt }, 0x0 );

	{
		auto &interf = diesel->openInterface( "testClassNew" );
		interf.pushFunction<CUserDefinedFunction>( "func", kVoid, args{ kBool, kInt } );
		interf.pushFunction<CGetterFunction>( "new_func", kInt, args{ }, 0x0 );
		interf.pushFunction<CGetterFunction>( "hopefully_skipped", kInt, args{ kInt }, 0x0 );
	}
	diesel->saveFiles( "Test", std::filesystem::current_path( ) );

	return 0;
}