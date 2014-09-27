/*so in gmod13 there was a cool little function called RunOnClient in the menu state, but I told kilburn about it after a while
kinda miss it though
as always tons of credit to willox*/

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif // _WIN32

typedef unsigned char uchar;

#include "sourcestuff.h"
#include "GarrysMod/Lua/Interface.h"
#include "main.h"

#include "Hook/VPTR.h"

using namespace GarrysMod;
using namespace Hook;

Lua::Shared* luaShared;

VPTR *sharedHooker;

Lua::Interface* cState;

int RunOnClient(lua_State* state)
{
	if (!cState)
		LUA->ThrowError("Not in game");

	cState->RunStringEx("gamemode/base/cl_init.lua", "", LUA->GetString(), true, true, true); //free cookies for people that know how to detect stuff

	return 0;
}

typedef Lua::Interface *(__thiscall *hCreateLuaInterfaceFn)(Lua::Shared*, unsigned char, bool);
void * __fastcall hCreateLuaInterface(Lua::Shared *_this, void *ukwn, uchar state, bool renew)
{
	if (state != Lua::Interface::CLIENT)
		return sharedHooker->GetOriginal<hCreateLuaInterfaceFn>(Lua::Shared::CREATELUAINTERFACE_OFFSET)(_this, state, renew);

	cState = sharedHooker->GetOriginal<hCreateLuaInterfaceFn>(Lua::Shared::CREATELUAINTERFACE_OFFSET)(_this, state, renew);

	return cState;
}

typedef void *(__thiscall *hCloseLuaInterfaceFn)(Lua::Shared*, Lua::Interface*);
void * __fastcall hCloseLuaInterface(Lua::Shared *_this, void *ukwn, Lua::Interface* iface)
{
	if (iface == cState)
		cState = NULL;

	return sharedHooker->GetOriginal<hCloseLuaInterfaceFn>(Lua::Shared::CLOSELUAINTERFACE_OFFSET)(_this, iface);
}

GMOD_MODULE_OPEN()
{
	luaShared = GetInterface<Lua::Shared*>("lua_shared.dll", "LUASHARED003");

	if (!luaShared)
		MessageBox(NULL, "", "", NULL);

	LUA->PushSpecial(Lua::SPECIAL_GLOB);
	LUA->PushString("RunOnClient");
	LUA->PushCFunction(RunOnClient);
	LUA->SetTable(-3);
	LUA->Pop();

	sharedHooker = new VPTR(luaShared);
	sharedHooker->Hook(Lua::Shared::CREATELUAINTERFACE_OFFSET, hCreateLuaInterface);
	sharedHooker->Hook(Lua::Shared::CLOSELUAINTERFACE_OFFSET, hCloseLuaInterface);
	
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
