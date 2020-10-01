workspace "Project_1"
    startproject "Main"
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

project "Main"
        location "project_data"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetname("Project 1")
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

