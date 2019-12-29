project "HelloWorld"
	kind "ConsoleApp"
	language "C"
	architecture "x64"
	location "build/HelloWorld"
	debugdir "bin/%{cfg.buildcfg}"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.h", "src/**.cpp" }
	includedirs { GLFW_INCLUDE }
	libdirs { GLFW_INCLUDE }
	links { "glfw3", "opengl32" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"