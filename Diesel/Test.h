#ifndef TEST_H
#define TEST_H
#include <cstdint>

class testClass {
public:
	inline static testClass* get() {
		return (testClass*)(6);
	}
	void func(bool, int);
	int& new_func();
};
class testClassNew {
public:
	inline static testClassNew* get(std::uintptr_t base) { 
		return (testClassNew*)(base + (24));
	}
	void func(bool, int);
	int& new_func();
	void vft_fn();
	void vft_fn_new(int);
	void vft_fn_new_new(int, int);
};

#endif // TEST_H