workspace "SML"
    configurations { 
       "Debug", 
       "Release" 
    }

    platforms {
        "Static32",
        "Static64"
    }

    flags {
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["SML"] = "sml/include"

project "sml"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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

    filter "platforms:Static32"
        architecture "x86"

    filter "platforms:Static64"
        architecture "x86_64"


project "SMLTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	vectorextensions "AVX"

    files {
        "smltest/include/**.h",
        "smltest/include/**.hpp",
        "smltest/src/**.cpp" 
    }

    includedirs {
        "%{IncludeDir.SML}",
        "smltest/include"
    }

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