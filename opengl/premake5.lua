GLFW_INCLUDE = os.getcwd() .. "/../deps/glfw-3.3/include"
GLFW_LIB = os.getcwd() .. "/../deps/glfw-3.3/lib-vc2019"

GLEW_INCLUDE = os.getcwd() .. "/../deps/glew-2.1.0/include"
GLEW_LIB = os.getcwd() .. "/../deps/glew-2.1.0/lib/Release/x64"

LODEPNG_INCLUDE = os.getcwd() .. "/../deps/lodepng"

GLM_INCLUDE = os.getcwd() .. "/../deps/glm"

RUN_DIR = os.getcwd() .. "/../run_dir"

workspace "OpenGLProjects"
	configurations { "Debug", "Release" }
	location "build"
	debugdir(RUN_DIR)
	targetdir(RUN_DIR)

include("hello_world/premake5.lua")
include("first_triangle/premake5.lua")
include("indices/premake5.lua")
include("textures/premake5.lua")
include("multi_textures/premake5.lua")
include("transform/premake5.lua")
include("projections/premake5.lua")
include("instanced/premake5.lua")
include("camera/premake5.lua")