#include "Test.h"

int& ::new_func() {
	return *(int*)(((std::uintptr_t)this) + 0);
}
void ::vft_fn() {
	return reinterpret_cast<void(__cdecl*)(void*)>(((*(std::uintptr_t**)(this)))[0])(this);
}
void ::vft_fn_new(int arg0) {
	return reinterpret_cast<void(__cdecl*)(void*, int)>(((*(std::uintptr_t**)(this)))[1])(this, arg0);
}
void ::vft_fn_new_new(int arg0, int arg1) {
	return reinterpret_cast<void(__thiscall*)(void*, int, int)>(((*(std::uintptr_t**)(this)))[1])(this, arg0, arg1);
}
