namespace GarrysMod {
	namespace Lua {

		class Shared {
		public:

			enum { //offsets
#ifdef _WIN32
				CREATELUAINTERFACE= 4,
				CLOSELUAINTERFACE = 5
#else
				CREATELUAINTERFACE= 5,
				CLOSELUAINTERFACE = 6
#endif
			};

			virtual				~Shared() = 0;
			virtual void*		Init(void *) = 0;
			virtual void*		Shutdown(void) = 0;
			virtual void*		DumpStats(void) = 0;
			virtual Interface*	CreateLuaInterface(unsigned char, bool) = 0;
			virtual void*		CloseLuaInterface(Interface *) = 0;
			virtual Interface*	GetLuaInterface(unsigned char) = 0;
			virtual void*		LoadFile() = 0;
			virtual void*		GetCache() = 0;
			virtual void*		MountLua(char  const*) = 0;
			virtual void*		MountLuaAdd(char  const*, char  const*) = 0;
			virtual void*		UnMountLua(char  const*) = 0;
			virtual void*		SetFileContents(char  const*, char  const*) = 0;
			virtual void*		SetLuaFindHook(void *) = 0;
			virtual void*		FindScripts() = 0;
		};


		void Init();
		Shared *GetShared();
	}
}