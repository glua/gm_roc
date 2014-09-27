dofile("../../common.lua")

RequireDefaultlibs()

SOLUTION 	"roc"

targetdir	"bin"
INCLUDES	"source_sdk"
INCLUDES 	"gmod_sdk"
defines		{"NDEBUG"}

WINDOWS()

PROJECT()
	files {"deps/**.h"}
	files {"deps/**.cpp"}

	includedirs {"deps"}

SOURCE_SDK_LINKS()
configuration 		"windows"
