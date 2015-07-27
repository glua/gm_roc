#include "interface.h"

#include "proc.h"
#include "conv.h"

#include <stdio.h>

#ifdef _WIN32
#define snprintf _snprintf
#endif

typedef void *(__cdecl *CreateInterfaceFn)(const char *name, int *ret);

void *GetInterface_Internal(const char *module_name, const char *interface_name, libsym_return *code)
{
	CreateInterfaceFn CreateInterface = 0;
	char temp[512];
	void *retval = 0;

	snprintf(temp, 512, "%s" PROC_EXT, module_name);

	if(code) *code = LIBSYM_SUCCESS;

	libsym_return codes = libsym_intrnl_(&CreateInterface, temp, "CreateInterface");
	if(codes != LIBSYM_SUCCESS)
	{
		if(code) *code = codes;
		return retval;
	}

	retval = CreateInterface(interface_name, 0);

	return retval;

}
