workspace "Project_1"
    startproject "Carpool"
    configurations 
    { 
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}/%{cfg.system}%{cfg.architecture}"

project "Carpool"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetname("Carpool")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        
        files
        {
            "src/**.h",
            "src/**.cpp",
        }

        sysincludedirs
        {
            "src",
        }

        targetdir("./")
        debugdir("./")

        filter "system:windows"
            pchheader "pch.h"
            pchsource "src/pch.cpp"

        filter "system:linux"
            pchheader "src/pch.h"

        filter "system:macos"
            pchheader "src/pch.h"