template <class _interface>
inline _interface GetInterface(const char* module_name, const char* interface_name)
{
	typedef void* (*CreateInterfaceFn)(const char* pszInterface, int pReturnCode);
	HMODULE module_ = GetModuleHandle(module_name);
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(module_, "CreateInterface");
	void* ret = CreateInterface(interface_name, 0);
	return (_interface)ret;
};