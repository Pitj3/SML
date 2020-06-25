workspace "SML"
    configurations { 
       "debug", 
       "release" 
    }

    flags {
		"MultiProcessorCompile"
	}

    binaries = "%{sln.location}/bin/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"
    intermediate = "%{sln.location}/bin-int/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["SML"] = "sml/include"
    IncludeDir["gtest"] = "%{sln.location}/dependencies/googletest/include"

    include "dependencies/googletest"

project "sml"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir (binaries)
	objdir (intermediate)

    files {
        "sml/include/**.h", 
        "sml/src/**.cpp" 
    }

    includedirs {
        "%{prj.name}/include"
    }

    filter "configurations:Debug"
        defines { 
            "DEBUG",
            "SML_DEBUG"
        }

		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
        defines { 
            "NDEBUG",
            "SML_RELEASE"
        }
        
        runtime "Release"
        optimize "On"

project "SMLTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir (binaries)
	objdir (intermediate)
	
	vectorextensions "AVX"

    files {
        "smltest/include/**.h",
        "smltest/include/**.hpp",
        "smltest/src/**.cpp" 
    }

    includedirs {
        "%{IncludeDir.SML}",
        "%{IncludeDir.gtest}",
        "smltest/src",
        "smltest/include"
    }

    links {
        "googletest"
    }

    filter "system:windows"
        toolset "msc-ClangCL"

    filter "system:linux"
        toolset "clang"

        links {
            "pthread"
        }

    filter {}

    filter "configurations:Debug"
        defines { 
            "DEBUG" 
        }
        symbols "On"

    filter "configurations:Release"
        defines { 
            "NDEBUG" 
        }
        optimize "On"
