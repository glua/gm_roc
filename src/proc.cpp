#include "proc.h"


#ifdef _WIN32

#include <Windows.h>

#define lib_open(name) ((void *)GetModuleHandleA(name))
#define lib_sym(lib, symname) ((void *)GetProcAddress((HMODULE)lib, symname))

#elif defined(__linux__)

#include <dlfcn.h>
#include <link.h>
#include <string.h>


// the following define won't work 100% of the time, maybe i should fix that? oh well
//#define lib_open(name) dlopen(name, RTLD_LAZY | RTLD_NOLOAD)

typedef struct
{
  const char *name;
  void *lib;
} lib_open_stru;

int lib_open_callback(struct dl_phdr_info *info, size_t size, void *data)
{
  lib_open_stru *stru = (lib_open_stru *)data;

  size_t len = strlen(info->dlpi_name);
  if(len < strlen(stru->name)) return 0;

  if(strcmp(info->dlpi_name + len - strlen(stru->name), stru->name) == 0)
    stru->lib = dlopen(info->dlpi_name, RTLD_LAZY);

  return 0;

}

void *lib_open(const char *name)
{
  lib_open_stru data;
  data.name = name;
  data.lib = 0;

  dl_iterate_phdr(&lib_open_callback, &data);

  return data.lib;
}

#define lib_sym dlsym

#else
#error "unsupported OS"
#endif

libsym_return libsym_intrnl(void **symbol, const char *libname, const char *interfacename)
{

  void *lib = lib_open(libname);

  if(symbol) *symbol = 0;

  if(!lib)
    return LIBSYM_NODLL;

  void *retval = lib_sym(lib, interfacename);

  if(!retval)
    return LIBSYM_NOSYMBOL;


  if(symbol) *symbol = retval;

  return LIBSYM_SUCCESS;

}
