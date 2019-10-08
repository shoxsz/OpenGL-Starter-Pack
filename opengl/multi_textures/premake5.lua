project "MultiTextures"
	kind "ConsoleApp"
	language "C++"
	architecture "x64"
	location "build/MultiTextures"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.h", LODEPNG_INCLUDE .. "/**.h", "src/**.cpp", LODEPNG_INCLUDE .. "/**.cpp" }
	includedirs { LODEPNG_INCLUDE, GLFW_INCLUDE, GLEW_INCLUDE }
	libdirs { GLFW_LIB, GLEW_LIB }
	links { "glfw3", "glew32.lib", "opengl32" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"