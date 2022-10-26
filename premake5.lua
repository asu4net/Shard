workspace "Shard"
    architecture "x64"
    startproject "Game"

configurations
{
    "Debug",
    "Release"
}

-- VARIABLES --

-- Include directories 
IncludeDir = {}

IncludeDir["SHARD_SRC"] = "Shard/src"
IncludeDir["GLFW"] = "Shard/vendor/glfw/include"
IncludeDir["GLEW"] = "Shard/vendor/glew/include"

-- Library files
LibFile = {}

LibFile["GLEW"] = "glew32s.lib"
LibFile["OPENGL"] = "opengl32.lib"

-- Library directories
LibDir = {}

LibDir["GLEW"] = "Shard/vendor/glew/lib"

-- Output directory
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Shard/vendor/glfw/premake5.lua"

project "Shard"
    location "Shard"
    kind "SharedLib"
    language "C++"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}"
    }

    libdirs
	{
		"%{LibDir.GLEW}"
	}

    links
    {
        "GLFW",
        "%{LibFile.GLEW}",
        "%{LibFile.OPENGL}"
    }

    filter "system:windows"
        cppdialect "C++11"
        systemversion "latest"

        defines
        {
            "SHARD_PLATFORM_WINDOWS",
            "SHARD_BUILD_DLL"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

    filter "configurations:Debug"
        defines "SHARD_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SHARD_RELEASE"
        symbols "On"
        optimize "On"

project "Game"
    location "Game"
	kind "ConsoleApp"
	language "C++"

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
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}"
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
		"%{LibFile.OPENGL}"
	}

	filter "system:windows"
	    cppdialect "C++11"
	    systemversion "latest"

	    defines 
	    {
		    "SHARD_PLATFORM_WINDOWS"
	    }

	filter "configurations:Debug"
		defines "SHARD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SHARD_RELEASE"
		symbols "On"
		optimize "On"