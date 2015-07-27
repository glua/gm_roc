#ifndef CONV_H
#define CONV_H

#ifndef _WIN32

#ifndef __cdecl
#define __cdecl __attribute__((cdecl))
#endif

#ifndef __stdcall
#define __stdcall __attribute__((stdcall))
#endif

#ifndef __fastcall
#define __fastcall __attribute__((fastcall))
#endif

#ifndef __thiscall
#define __thiscall __attribute__((cdecl))
#endif


#ifndef _cdecl

#define _cdecl __attribute__((cdecl))
#define _stdcall __attribute__((stdcall))
#define _fastcall __attribute__((fastcall))
#define _thiscall __attribute__((cdecl))

#endif

#define __hook __cdecl
#define _hook __cdecl
#define HOOK_EDX(arg)

#else

#define __hook __fastcall

#define HOOK_EDX(arg) arg,

#endif

#endif // CONV_H
