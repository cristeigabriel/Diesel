#include "Src/Codegen/Cpp/CppCodegen.h"
#include <iostream>


int main( )
{
	auto diesel = std::make_unique<CCppCodegen>( "E:\\text.txt", true, true );
	auto &interf = diesel->openInterface( "testClass", 3, 3 );
	std::vector<std::shared_ptr<CCppType>> a;
	interf.m_functions[ "func" ] = std::move( std::make_shared<CCppUserDefinedFunction>( std::forward<std::shared_ptr<CCppType>>( std::make_shared<CCppType>( kVoid ) ),
											  std::vector<std::shared_ptr<CCppType>> {} ) );
	//interf.pushFunction<CCppGetterFunction>( "new_func", std::move( std::make_shared<type>( kInt ) ), std::move( b ), 0x0 );/*
	/*interf.pushFunction<CCppGetterFunction>( "hopefully_skipped", std::make_unique<type>( kInt ), args{ std::make_unique<type>( kInt ) }, 0x0 );

	{
		auto &interf = diesel->openInterface( "testClassNew", 24 );
		interf.pushFunction<CCppUserDefinedFunction>( "func", kVoid, args{ kBool, kInt } );
		interf.pushFunction<CCppGetterFunction>( "new_func", kInt, args{ }, 0x0 );
		interf.pushFunction<CCppGetterFunction>( "hopefully_skipped", kInt, args{ kInt }, 0x0 );
		interf.pushFunction<CCppVirtualTableFunction>( "vft_fn", kVoid, args{ }, IVirtualTableFunction::Cdecl, 0 );
		interf.pushFunction<CCppVirtualTableFunction>( "vft_fn_new", kVoid, args{ kInt }, IVirtualTableFunction::Cdecl, 1 );
		interf.pushFunction<CCppVirtualTableFunction>( "vft_fn_new_new", kVoid, args{ kInt, kInt }, IVirtualTableFunction::Thiscall, 1 );
	}*/
	diesel->saveFiles( "Test", std::filesystem::current_path( ) );

	return 0;
}