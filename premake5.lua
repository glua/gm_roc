dofile("../../common.lua")

RequireDefaultlibs()

SOLUTION 	"gmcl_roc_win32"

targetdir	"bins"
INCLUDES	"source_sdk"
INCLUDES 	"gmod_sdk"
defines		{"NDEBUG"}

WINDOWS()
LINUX()

PROJECT()
SOURCE_SDK_LINKS()
configuration 		"windows"
configuration 		"linux"
