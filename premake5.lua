if os.is("windows") then
	GLFW_LIB = os.getcwd() .. "/deps/glfw-3.3/lib-vc2019"
	GLEW_LIB = os.getcwd() .. "/deps/glew-2.1.0/Release/x64"
	GL_LIB_NAME = "OpenGL32"
elseif os.is("linux") then
	GLFW_LIB = os.getcwd() .. "/deps/glfw-3.3/lib"
	GLEW_LIB = os.getcwd() .. "/deps/glew-2.1.0/ReleaseLinux/x64"
	GL_LIB_NAME = "GL"
end

GLFW_INCLUDE = os.getcwd() .. "/deps/glfw-3.3/include"
GLEW_INCLUDE = os.getcwd() .. "/deps/glew-2.1.0/include"
LODEPNG_INCLUDE = os.getcwd() .. "/deps/lodepng"
GLM_INCLUDE = os.getcwd() .. "/deps/glm"

RUN_DIR = os.getcwd() .. "/run_dir"
LINUX_TARGET_DIR = RUN_DIR

function CreateProject(name)
	project(name)
	kind "ConsoleApp"
	language "C++"
	architecture "x64"
	location("build/" .. name)

	if os.is("windows") then
		targetdir "bin/%{cfg.buildcfg}"
	elseif os.is("linux") then
		targetdir(LINUX_TARGET_DIR)
	end

	files { os.getcwd() .. "/src/**.h", os.getcwd() .. "/src/**.hpp", LODEPNG_INCLUDE .. "/**.h", os.getcwd() .. "/src/**.cpp", LODEPNG_INCLUDE .. "/**.cpp" }
	includedirs { os.getcwd() .. "/src", GLM_INCLUDE, LODEPNG_INCLUDE, GLFW_INCLUDE, GLEW_INCLUDE }
	libdirs { GLFW_LIB, GLEW_LIB }

	if os.is("windows") then
		defines { "GLEW_STATIC" }
		links { "glfw3", "glew32", GL_LIB_NAME }
	elseif os.is("linux") then
		links { "glfw3", "glew32", "pthread", "X11", "dl", GL_LIB_NAME }
	end

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
end

include("opengl/premake5.lua")
include("game/premake5.lua")