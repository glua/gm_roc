dofile("../../common.lua")

RequireDefaultlibs()

SOLUTION 	"roc"

targetdir	"bin"
INCLUDES	"source_sdk"
INCLUDES 	"gmod_sdk"
defines		{"NDEBUG"}

WINDOWS()

PROJECT()
	files {"includes/**.h"}
	files {"includes/**.cpp"}

	includedirs {"includes"}

SOURCE_SDK_LINKS()

WINDOWS()
configuration 		"windows"

LINUX()
configuration     "linux"
