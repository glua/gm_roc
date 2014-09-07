/*so in gmod13 there was a cool little function called RunOnClient in the menu state, but I told kilburn about it after a while
kinda miss it though
as always tons of credit to willox*/

#include "deps.h"
using namespace GarrysMod;

Lua::Shared* luaShared;

int RunOnClient(lua_State* state)
{
	Lua::Interface* cState = luaShared->GetLuaInterface(Lua::Interface::CLIENT);
	cState->RunStringEx("gamemode/base/cl_init.lua", "", LUA->GetString(), true, true, true); //free cookies for people that know how to detect stuff

	return 0;
}

GMOD_MODULE_OPEN()
{
	luaShared = GetInterface<Lua::Shared*>("lua_shared.dll", "LUASHARED003");

	if (!luaShared)
		MessageBox(NULL, "", "", NULL);

	LUA->PushSpecial(Lua::SPECIAL_GLOB);
	LUA->PushString("RunOnClientRaw");
	LUA->PushCFunction(RunOnClient);
	LUA->SetTable(-3);
	LUA->Pop();
	
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
