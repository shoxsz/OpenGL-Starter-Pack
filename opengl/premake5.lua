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