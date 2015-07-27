#ifndef GM_STRINGTABLE_INTERFACE_H
#define GM_STRINGTABLE_INTERFACE_H

#include "proc.h"

void *GetInterface_Internal(const char *module_name, const char *interface_name, libsym_return *code = 0);

template<class TYPE>
TYPE GetInterface(const char *module_name, const char *interface_name, libsym_return *code = 0) {
	return reinterpret_cast<TYPE>(GetInterface_Internal(module_name, interface_name, code));
}


#endif
