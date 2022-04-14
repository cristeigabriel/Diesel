#include "Src/Codegen/Codegen.h"

int main( )
{
	auto diesel = std::make_unique<CCppCodegen>( std::ifstream( ), true, false );

	auto &interf = diesel->openInterface( "testClass" );
	using args = std::vector<EType>;
	interf.pushFunction<CUserDefinedFunction>( "func", kVoid, args{ kBool, kInt } );
	interf.pushFunction<CGetterFunction>( "new_func", kInt, args{ }, 0x0 );
	interf.pushFunction<CGetterFunction>( "hopefully_skipped", kInt, args{ kInt }, 0x0 );
	diesel->saveFiles( "Test", std::filesystem::current_path( ) );

	return 0;
}