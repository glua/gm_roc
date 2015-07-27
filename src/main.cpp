/*so in gmod13 there was a cool little function called RunOnClient in the menu state, but I told kilburn about it after a while
kinda miss it though
as always tons of credit to willox*/

typedef unsigned char uchar;

#include "sourcestuff.h"
#include "GarrysMod/Lua/Interface.h"

#include "luaInterface.h"
#include "interface.h"
#include "conv.h"
#include "shared.h"

#include "Hook/VPTR.h"

using namespace GarrysMod;
using namespace Hook;

Lua::Shared* luaShared;

VPTR* luashared_vt;
VPTR* client_vt;

Lua::Interface* cState;
Lua::ILuaBase* LAU;

int RunOnClient(lua_State *state)
{
	if (!cState)
		LUA->ThrowError("Not in game");

	cState->RunStringEx("gamemode/base/cl_init.lua", "", LUA->GetString(), true, true, true); //free cookies for people that know how to detect stuff

	return 0;
}

typedef void *(__thiscall *hRunStringExFn)(Lua::Interface*, char const*, char const*, char const*, bool, bool, bool);
void *__hook hRunStringEx(Lua::Interface *ths, HOOK_EDX(void *) const char *path, const char *wtfisthis, const char *torun, bool run, bool showerrors, bool idk)
{
	LAU->PushSpecial(Lua::SPECIAL_GLOB);
	LAU->GetField(-1, "hook");
		LAU->GetField(-1, "Call");
			LAU->PushString("RunOnClient");
			LAU->PushNil();
			LAU->PushString(path);
			LAU->PushString(torun);
		LAU->Call(4, 1);
		if (!LAU->IsType(-1, Lua::Type::NIL))
			torun = LAU->CheckString();
	LAU->Pop(3);

	return client_vt->GetOriginal<hRunStringExFn>(Lua::Interface::RUNSTRINGEX)(ths, path, wtfisthis, torun, run, showerrors, idk);
}

typedef Lua::Interface *(__thiscall *hCreateLuaInterfaceFn)(Lua::Shared*, unsigned char, bool);
void *__hook hCreateLuaInterface(Lua::Shared *ths, HOOK_EDX(void *) uchar state, bool renew)
{
	Lua::Interface* hState = luashared_vt->GetOriginal<hCreateLuaInterfaceFn>(Lua::Shared::CREATELUAINTERFACE)(ths, state, renew);

	if (state != Lua::Interface::CLIENT)
		return hState;

	cState = hState;

	client_vt = new VPTR(cState);
	client_vt->Hook(Lua::Interface::RUNSTRINGEX, (void *)&hRunStringEx);

	return cState;
}

typedef void *(__thiscall *hCloseLuaInterfaceFn)(Lua::Shared *, Lua::Interface *);
void *__hook hCloseLuaInterface(Lua::Shared *ths, HOOK_EDX(void *) Lua::Interface *iface)
{
	if (iface == cState)
		cState = NULL;

	return luashared_vt->GetOriginal<hCloseLuaInterfaceFn>(Lua::Shared::CLOSELUAINTERFACE)(ths, iface);
}

GMOD_MODULE_OPEN()
{
	LAU = LUA;
	luaShared = GetInterface<Lua::Shared*>("lua_shared.dll", "LUASHARED003");

	LUA->PushSpecial(Lua::SPECIAL_GLOB);
	LUA->PushString("RunOnClient");
	LUA->PushCFunction(RunOnClient);
	LUA->SetTable(-3);
	LUA->Pop();

	luashared_vt = new VPTR(luaShared);
	luashared_vt->Hook(Lua::Shared::CREATELUAINTERFACE, (void *)&hCreateLuaInterface);
	luashared_vt->Hook(Lua::Shared::CLOSELUAINTERFACE, (void *)&hCloseLuaInterface);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
