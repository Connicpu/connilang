workspace "connilang"
    objdir "obj/%{cfg.system}/%{prj.name}/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "bin/%{cfg.system}/%{cfg.platform}/%{cfg.buildcfg}"
    pic "On"
    warnings "Extra"

    configurations { "Debug", "Release" }
    platforms { "x64" }

    vpaths {
        Headers = { "**.h" },
        Inlines = { "**.inl" },
        Source = { "**.cpp" },
    }

    defines { "_USE_MATH_DEFINES" }

filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    symbols "On"

filter "system:windows"
    defines { "NOMINMAX", "WIN32_LEAN_AND_MEAN" }
    characterset "MBCS"

filter "not system:windows"
    toolset "clang"
    buildoptions { "-std=c++1z" }

filter "action:vs*"
    buildoptions { "/std:c++latest" }

project "connilang-common"
    kind "Utility"
    language "C++"

    files {
        "include/*.h",
        "include/*.inl",
    }

project "connilang-lexer"
    kind "StaticLib"
    language "C++"

    includedirs { "include" }

    files {
        "lexer/*.cpp",
        "lexer/*.h",
        "lexer/*.inl",
    }

project "connilang-parser"
    kind "StaticLib"
    language "C++"

    includedirs { "include" }
    links { "connilang-lexer" }

    files {
        "parser/*.cpp",
        "parser/*.h",
        "parser/*.inl",
    }

