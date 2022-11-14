workspace "Shard"
    architecture "x64"
    startproject "Game"

configurations
{
    "Debug",
    "Release"
}

-- VARIABLES --

-- Output directory
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories 
IncludeDir = {}

IncludeDir["SHARD_SRC"] = "Shard/src"
IncludeDir["GLM"] = "Shard/vendor/glm"
IncludeDir["GLFW"] = "Shard/vendor/glfw/include"
IncludeDir["GLEW"] = "Shard/vendor/glew/include"
IncludeDir["SHARD"] = "Shard/src/Shard"
IncludeDir["SHARD_CORE"] = "Shard/src/Shard/Core"
IncludeDir["STB_IMAGE"] = "Shard/vendor/stb_image"
IncludeDir["STB_TRUETYPE"] = "Shard/vendor/stb_truetype"
IncludeDir["IMGUI"] = "Shard/vendor/imgui"
IncludeDir["ENTT"] = "Shard/vendor/entt"

-- Library files
LibFile = {}

LibFile["GLEW"] = "glew32s.lib"
LibFile["OPENGL"] = "opengl32.lib"

-- Library directories
LibDir = {}

LibDir["GLEW"] = "Shard/vendor/glew/lib"

include "Shard/vendor/glfw/premake5.lua"
include "Shard/vendor/imgui/premake5.lua"

project "Shard"
    location "Shard"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "shpch.h"
	pchsource "Shard/src/shpch.cpp"

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/stb_image.h",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",
		"%{prj.name}/vendor/stb_truetype/stb_truetype.h",
		"%{prj.name}/vendor/stb_truetype/stb_truetype.cpp",
		"%{prj.name}/vendor/entt/entt.hpp"
	}

    includedirs
    {
        "%{IncludeDir.SHARD_SRC}",
        "%{IncludeDir.SHARD_CORE}",
		"%{IncludeDir.SHARD}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
        "%{IncludeDir.GLEW}",
		"%{IncludeDir.STB_IMAGE}",
		"%{IncludeDir.STB_TRUETYPE}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.ENTT}"
    }

    libdirs
	{
		"%{LibDir.GLEW}"
	}

    links
    {
        "GLFW",
        "%{LibFile.GLEW}",
        "%{LibFile.OPENGL}",
		"ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
			"GLEW_STATIC",
            "SHARD_PLATFORM_WINDOWS",
            "SHARD_BUILD_DLL"
        }

        postbuildcommands
		{
			("{COPY}  %{wks.location}/Game/res ../bin/" .. outputdir .. "/Game/res")
		}

    filter "configurations:Debug"
        defines "SHARD_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SHARD_RELEASE"
        runtime "Release"
        optimize "on"

project "Game"
    location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

    includedirs
    {
        "%{IncludeDir.SHARD_SRC}",
        "%{IncludeDir.SHARD_CORE}",
		"%{IncludeDir.SHARD}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.ENTT}"
    }

    libdirs
	{
		"%{LibDir.GLFW}",
		"%{LibDir.GLEW}"
	}

	links
	{
		"Shard",
		"GLFW",
		"%{LibFile.GLEW}",
		"%{LibFile.OPENGL}",
		"ImGui"
	}

	filter "system:windows"
	    systemversion "latest"

	    defines 
	    {
			"GLEW_STATIC",
		    "SHARD_PLATFORM_WINDOWS"
	    }

	filter "configurations:Debug"
		defines "SHARD_DEBUG"
		runtime "Debug"
        symbols "on"

	filter "configurations:Release"
		defines "SHARD_RELEASE"
		runtime "Release"
        optimize "on"