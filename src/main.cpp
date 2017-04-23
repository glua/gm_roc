#include "GarrysMod/Lua/Interface.h"
#include "vtable.h"
#include "util.h"
#include "windows.h"

#define CREATELUAINTERFACE 4
#define CLOSELUAINTERFACE 5
#define RUNSTRINGEX 111

typedef unsigned char uchar;

VTable* sharedHooker;
VTable* clientHooker;

using namespace GarrysMod;

Lua::ILuaBase *MENU;
void *clientState;

typedef void *(__thiscall *hRunStringExFn)(void*, char const*, char const*, char const*, bool, bool, bool, bool);
void * __fastcall hRunStringEx(void *_this, void*, char const* filename, char const* path, char const* torun, bool run, bool showerrors, bool idk, bool idk2)
{
	MENU->PushSpecial(Lua::SPECIAL_GLOB);
	MENU->GetField(-1, "hook");
		MENU->GetField(-1, "Call");
			MENU->PushString("RunOnClient");
			MENU->PushNil();
			MENU->PushString(filename);
			MENU->PushString(torun);
		MENU->Call(4, 1);
		if (!MENU->IsType(-1, Lua::Type::NIL))
			torun = MENU->CheckString();
	MENU->Pop(3);

	return hRunStringExFn(clientHooker->getold(RUNSTRINGEX))(_this, filename, path, torun, run, showerrors, idk, idk2);
}

typedef void *(__thiscall *hCreateLuaInterfaceFn)(void *, uchar, bool);
void * __fastcall hCreateLuaInterface(void *_this, void *, uchar stateType, bool renew)
{
	void *state = hCreateLuaInterfaceFn(sharedHooker->getold(CREATELUAINTERFACE))(_this, stateType, renew);

	MENU->PushSpecial(Lua::SPECIAL_GLOB);
	MENU->GetField(-1, "hook");
		MENU->GetField(-1, "Call");
			MENU->PushString("ClientStateCreated");
			MENU->PushNil();
		MENU->Call(2, 0);
	MENU->Pop(2);

	if (stateType != 0)
		return state;

	clientState = state;

	clientHooker = new VTable(clientState);
	clientHooker->hook(RUNSTRINGEX, hRunStringEx);

	return clientState;
}

typedef void *(__thiscall *hCloseLuaInterfaceFn)(void*, void*);
void * __fastcall hCloseLuaInterface(void *_this, void *ukwn, void *luaInterface)
{
	if (luaInterface == clientState)
		clientState = NULL;

	return hCloseLuaInterfaceFn(sharedHooker->getold(CLOSELUAINTERFACE))(_this, luaInterface);
}

class CLuaInterface
{
private:
	template<typename t>
	inline t get(unsigned short which)
	{
		return t((*(char ***)(this))[which]);
	}

public:
	void RunStringEx(char const* filename, char const* path, char const* torun, bool run = true, bool showerrors = true, bool idk = true, bool idk2 = true)
	{
		return get<void(__thiscall *)(void*,char const*, char const*, char const*, bool, bool, bool, bool)>(RUNSTRINGEX)(this, filename, path, torun, run, showerrors, idk, idk2); //free cookies for people that know how to detect stuff
	}

};

int RunOnClient(lua_State* state)
{
	if (!clientState)
		LUA->ThrowError("Not in game");

	reinterpret_cast<CLuaInterface *>(clientState)->RunStringEx(LUA->CheckString(-3), LUA->CheckString(-2), LUA->CheckString());

	return 0;
}

GMOD_MODULE_OPEN()
{
	MENU = LUA;

	auto luaShared = util::GetInterfaceSingle<void *>("lua_shared.dll", "LUASHARED003");
	
	if (!luaShared)
		MessageBoxA(NULL, "gay", "gay", NULL);

	sharedHooker = new VTable(luaShared);

	sharedHooker->hook(CREATELUAINTERFACE, hCreateLuaInterface);
	sharedHooker->hook(CLOSELUAINTERFACE, hCloseLuaInterface);
	
	LUA->PushSpecial(Lua::SPECIAL_GLOB);
	LUA->PushString("RunOnClient");
	LUA->PushCFunction(RunOnClient);
	LUA->SetTable(-3);
	LUA->Pop();

	return 0;
}