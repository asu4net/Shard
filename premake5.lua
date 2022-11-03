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
IncludeDir["GLM"] = "Shard/vendor/glm/glm"
IncludeDir["GLFW"] = "Shard/vendor/glfw/include"
IncludeDir["GLEW"] = "Shard/vendor/glew/include"
IncludeDir["SHARD"] = "Shard/src/Shard"
IncludeDir["SHARD_CORE"] = "Shard/src/Shard/Core"
IncludeDir["STB_IMAGE"] = "Shard/vendor/stb_image"

-- Library files
LibFile = {}

LibFile["GLEW_STATIC"] = "glew32s.lib"
LibFile["GLEW"] = "glew32.lib"
LibFile["OPENGL"] = "opengl32.lib"

-- Library directories
LibDir = {}

LibDir["GLEW"] = "Shard/vendor/glew/lib"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/stb_image.h",
		"%{prj.name}/vendor/stb_image/stb_image.cpp"
	}

    includedirs
    {
        "%{IncludeDir.SHARD_SRC}",
        "%{IncludeDir.SHARD_CORE}",
		"%{IncludeDir.SHARD}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
        "%{IncludeDir.GLEW}",
		"%{IncludeDir.STB_IMAGE}"
    }

    libdirs
	{
		"%{LibDir.GLEW}"
	}

    links
    {
        "GLFW",
        "%{LibFile.GLEW}",
        "%{LibFile.GLEW_STATIC}",
        "%{LibFile.OPENGL}"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
			-- "GLEW_STATIC",
            "SHARD_PLATFORM_WINDOWS",
            "SHARD_BUILD_DLL"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game"),
			("{COPY}  %{prj.location}/vendor/glew/glew32.dll ../bin/" .. outputdir .. "/Game"),
			("{COPY}  %{wks.location}/Game/Shaders ../bin/" .. outputdir .. "/Game/Shaders"),
			("{COPY}  %{wks.location}/Game/Textures ../bin/" .. outputdir .. "/Game/Textures")
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
        "%{IncludeDir.SHARD_CORE}",
		"%{IncludeDir.SHARD}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
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
		"%{LibFile.GLEW_STATIC}",
		"%{LibFile.GLEW}",
		"%{LibFile.OPENGL}"
	}

	filter "system:windows"
	    cppdialect "C++17"
	    systemversion "latest"

	    defines 
	    {
			-- "GLEW_STATIC",
		    "SHARD_PLATFORM_WINDOWS"
	    }

	filter "configurations:Debug"
		defines "SHARD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SHARD_RELEASE"
		symbols "On"
		optimize "On"