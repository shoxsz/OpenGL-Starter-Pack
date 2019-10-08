workspace "FlappySpaceShip"
	configurations {"Debug", "Release"}
	location "build"
	debugdir "game_dir"
	targetdir "game_dir"

project "FlappySpaceShip"
	kind "ConsoleApp"
	language "C++"
	architecture "x64"
	location "build/FlappySpaceShip"

	files { "src/**.hpp", "../deps/lodepng/**.h", "src/**.cpp", "../deps/lodepng/**.cpp" }
	includedirs { "src/", "../deps/glm/", "../deps/lodepng", "../deps/glfw-3.3/include", "../deps/glew-2.1.0/include" }
	libdirs { "../deps/glfw-3.3/lib-vc2019", "../deps/glew-2.1.0/lib/Release/x64" }
	links { "glfw3", "glew32.lib", "opengl32" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"