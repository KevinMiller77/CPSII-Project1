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
        
        pchheader("src/pch.h")
        pchsource("src/pch.cpp")

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

