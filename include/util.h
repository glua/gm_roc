#include <stdio.h>

namespace util {
	
	typedef void *(__cdecl *CreateInterfaceFn)(const char *name, int *found);

	template<class t>
	t GetInterface(const char *module, const char *name)
	{
		HMODULE hmodule = GetModuleHandleA(module);
		CreateInterfaceFn create = (CreateInterfaceFn)GetProcAddress(hmodule, "CreateInterface");

		void *ret = 0;

		char temp_name[256]; // up this if it causes problems
		for (unsigned short i = 0; i < 1000; i++)
		{
			sprintf_s(temp_name, 256, "%s%03i", name, i);
			ret = create(temp_name, 0);
			if (ret) break;
		}

		return t(ret);
	}


	template<class t>
	t GetInterfaceSingle(const char *module, const char *name)
	{
		auto fn = CreateInterfaceFn(GetProcAddress(GetModuleHandleA(module), "CreateInterface"));
		return fn(name, 0);
	}

	inline char *getvfunc(void *obj, unsigned short which)
	{
		return (*(char ***)obj)[which];
	}
}