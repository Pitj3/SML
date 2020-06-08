workspace "SML"
   configurations { 
       "Debug", 
       "Release" 
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


project "SMLTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "smltest/include/**.h",
        "smltest/include/**.hpp",
        "smltest/src/**.cpp" 
    }

    includedirs {
        "%{IncludeDir.SML}",
        "%{prj.name}/include"
    }

    links {
        "sml"
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