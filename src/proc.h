#ifndef PROC_H
#define PROC_H

enum libsym_return
{
  LIBSYM_SUCCESS = 0,
  LIBSYM_NODLL = 1,
  LIBSYM_NOSYMBOL = 2
};

#ifdef _WIN32
#define PROC_EXT ".dll"
#elif defined(__linux__)
#define PROC_EXT ".so"
#endif

#define libsym(symbol, libname, interfacename) (libsym_intrnl_(symbol, libname PROC_EXT, interfacename))

template<typename t>
static libsym_return libsym_intrnl_(t *symbol, const char *libname, const char *interfacename)
{
  extern libsym_return libsym_intrnl(void **symbol, const char *libname, const char *interfacename);
  return libsym_intrnl((void **)symbol, libname, interfacename);
}


#endif
