dofile("../../common.lua")

RequireDefaultlibs()

SOLUTION 	"gm_roc"

targetdir	"bin"
INCLUDES	"source_sdk"
INCLUDES 	"gmod_sdk"
defines		{"NDEBUG"}

WINDOWS()

PROJECT()
SOURCE_SDK_LINKS()
configuration 		"windows"
