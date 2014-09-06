assert(os.getenv("SOURCE_SDK"), "SOURCE_SDK environmental variable not set")

local SOURCE_SDK = os.getenv("SOURCE_SDK") .. "/mp/src"


solution "gmcl_roc_win32"
	language "C++"
	location ( os.get() .."-".. _ACTION )
	targetdir ( "build/" .. os.get() .. "/" )

	includedirs {
		"deps",
		SOURCE_SDK .. "/common",
		SOURCE_SDK .. "/public/tier0",
		SOURCE_SDK .. "/public/tier1",
		SOURCE_SDK .. "/public"
	}

	libdirs {
		"deps",
		SOURCE_SDK .. "/lib/public"
	}

	links {
		"tier0",
		"tier1",
		"vstdlib",
		"Shlwapi",
	}
	
	configurations
	{ 
		"Release"
	}
	
	configuration "Release"
		defines { "NDEBUG" }
		optimize "On"

	configuration "vs*"
		linkoptions {
			"/NODEFAULTLIB:libcmt"
		}

	project "gmcl_roc_win32"
		defines { "GMMODULE" }
		kind "SharedLib"
		
		files {
			"src/**.cpp",
			"src/**.h"
		}