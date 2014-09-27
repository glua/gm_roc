#include "GarrysMod/Lua/Interface.h"
#include "sourcestuff.h"

typedef unsigned int uint;

struct ILuaCallback;
struct ILuaObject;
struct IThreadedCall;

struct string;

struct buff;


namespace GarrysMod {
	namespace Lua {

		class Interface {
		public:

			lua_State *state;

			enum {
				CLIENT,
				SERVER,
				MENU,
				RUNSTRINGEX = 107 //offset
			};

			static const char* Names[];

			static const char *GetName(int state_id) {
				return Names[state_id];
			}

			virtual void* Top(void) = 0;
			virtual void* Push(int) = 0;
			virtual void* Pop(int) = 0;
			virtual void* GetTable(int) = 0;
			virtual void* GetField(int, char  const*) = 0;
			virtual void* SetField(int, char  const*) = 0;
			virtual void* CreateTable(void) = 0;
			virtual void* SetTable(int) = 0;
			virtual void* SetMetaTable(int) = 0;
			virtual void* GetMetaTable(int) = 0;
			virtual void* Call(int, int) = 0;
			virtual void* PCall(int, int, int) = 0;
			virtual void* Equal(int, int) = 0;
			virtual void* RawEqual(int, int) = 0;
			virtual void* Insert(int) = 0;
			virtual void* Remove(int) = 0;
			virtual void* Next(int) = 0;
			virtual void* NewUserdata(uint) = 0;
			virtual void* ThrowError(char  const*) = 0;
			virtual void* CheckType(int, int) = 0;
			virtual void* ArgError(int, char  const*) = 0;
			virtual void* RawGet(int) = 0;
			virtual void* RawSet(int) = 0;
			virtual void* GetString(int, uint *) = 0;
			virtual void* GetNumber(int) = 0;
			virtual void* GetBool(int) = 0;
			virtual void* GetCFunction(int) = 0;
			virtual void* GetUserdata(int) = 0;
			virtual void* PushNil(void) = 0;
			virtual void* PushString(char  const*, uint) = 0;
			virtual void* PushNumber(double) = 0;
			virtual void* PushBool(bool) = 0;
			virtual void* PushCFunction(int(*)(lua_State *)) = 0;
			virtual void* PushCClosure(int(*)(lua_State *), int) = 0;
			virtual void* PushUserdata(void *) = 0;
			virtual void* ReferenceCreate(void) = 0;
			virtual void* ReferenceFree(int) = 0;
			virtual void* ReferencePush(int) = 0;
			virtual void* PushSpecial(int) = 0;
			virtual void* IsType(int, int) = 0;
			virtual void* GetType(int) = 0;
			virtual void* GetTypeName(int) = 0;
			virtual void* CreateMetaTableType(char  const*, int) = 0;
			virtual void* CheckString(int) = 0;
			virtual void* CheckNumber(int) = 0;
			virtual void* ObjLen(int) = 0;
			virtual void* AddThreadedCall(IThreadedCall *) = 0;
			virtual void* Init(ILuaCallback *, bool) = 0;
			virtual void* Shutdown(void) = 0;
			virtual void* Cycle(void) = 0;
			virtual void* GetLuaState(void) = 0;
			virtual void* Global(void) = 0;
			virtual void* GetObject(int) = 0;
			virtual void* DELETE_ME_5437(int) = 0;
			virtual void* _DELETE_ME2466(int) = 0;
			virtual void* PushLuaObject(ILuaObject *) = 0;
			virtual void* PushLuaFunction(int(*)(lua_State *)) = 0;
			virtual void* LuaError(char  const*, int) = 0;
			virtual void* TypeError(char  const*, int) = 0;
			virtual void* CallInternal(int, int) = 0;
			virtual void* CallInternalNoReturns(int) = 0;
			virtual void* CallInternalGetBool(int) = 0;
			virtual void* CallInternalGetString(int) = 0;
			virtual void* CallInternalGet(int, ILuaObject *) = 0;
			virtual void* _DELETE_ME(ILuaObject *, void *) = 0;
			virtual void* NewGlobalTable(char  const*) = 0;
			virtual void* NewTemporaryObject(void) = 0;
			virtual void* isUserData(int) = 0;
			virtual void* GetMetaTableObject(char  const*, int) = 0;
			virtual void* GetMetaTableObject(int) = 0;
			virtual void* GetReturn(int) = 0;
			virtual void* IsServer(void) = 0;
			virtual void* IsClient(void) = 0;
			virtual void* IsDedicatedServer(void) = 0;
			virtual void* DestroyObject(ILuaObject *) = 0;
			virtual void* CreateObject(void) = 0;
			virtual void* SetMember(ILuaObject *, ILuaObject *, ILuaObject *) = 0;
			virtual void* GetNewTable(void) = 0;
			virtual void* SetMember(ILuaObject *, float) = 0;
			virtual void* SetMember(ILuaObject *, float, ILuaObject *) = 0;
			virtual void* SetMember(ILuaObject *, char  const*) = 0;
			virtual void* SetMember(ILuaObject *, char  const*, ILuaObject *) = 0;
			virtual void* SetIsServer(bool) = 0;
			virtual void* PushLong(long) = 0;
			virtual void* GetFlags(int) = 0;
			virtual void* FindOnObjectsMetaTable(int, int) = 0;
			virtual void* FindObjectOnTable(int, int) = 0;
			virtual void* SetMemberFast(ILuaObject *, int, int) = 0;
			virtual bool RunString(char  const* szFileName, char  const* szFolderName, char  const* szStringToRun, bool bRun, bool bShowErrors) = 0;
			virtual void* IsEqual(ILuaObject *, ILuaObject *) = 0;
			virtual void* Error(char const*) = 0;
			virtual void* GetStringOrError(int) = 0;
			virtual void* RunLuaModule(char const*) = 0;
			virtual void* FindAndRunScript(char const*, bool, bool, char  const*) = 0;
			virtual void* SetPathID(char const*) = 0;
			virtual void* GetPathID(void) = 0;
			virtual void* ErrorNoHalt(char  const*, ...) = 0;
			virtual void* Msg(char  const*, ...) = 0;
			virtual void* PushPath(char  const*) = 0;
			virtual void* PopPath(void) = 0;
			virtual void* GetPath(void) = 0;
			virtual void* GetColor(int) = 0;
			virtual void* PushColor(int, int, int, int) = 0;
			virtual void* GetStack(int, void *) = 0;
			virtual void* GetInfo(char  const*, void *) = 0;
			virtual void* GetLocal(void *, int) = 0;
			virtual void* GetUpvalue(int, int) = 0;
			virtual void* RunStringEx(char  const*, char  const*, char  const*, bool, bool, bool) = 0;
			virtual void* DELETE_ME1(char  const*, int) = 0;
			virtual void* GetDataString(int, void **) = 0;
			virtual void* ErrorFromLua(char  const*, ...) = 0;
			virtual void* GetCurrentLocation(void) = 0;
			virtual void* MsgColour(Color  const&, char  const*, ...) = 0;
			virtual void* SetState(lua_State *) = 0;
			virtual void* DELETE_ME2(void) = 0;
			virtual void* GetCurrentFile(string &) = 0;
			virtual void* CompileString(buff &, string const&) = 0;
			virtual void* ThreadLock(void) = 0;
			virtual void* ThreadUnlock(void) = 0;
			virtual void* CallFunctionProtected(int, int, bool) = 0;
			virtual void* Require(char  const*) = 0;
			virtual void* GetActualTypeName(int) = 0;
			virtual void* SetupInfiniteLoopProtection(void) = 0;
		};

	}
}
