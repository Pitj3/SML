project "googletest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir (binaries)
    objdir (intermediate)

    files {
        "src/gmock-all.cc",
        "src/gtest-all.cc",
    }

    includedirs {
        ".",
        "include"
    }

    filter "system:windows"
        toolset "msc-ClangCL"
        systemversion "latest"
        staticruntime "On"

    filter "system:linux"
        toolset "clang"
        staticruntime "On"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "Full"
        runtime "Release"
        symbols "Off"
