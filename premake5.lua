workspace "CalculatorApp"
    architecture "x86_64"

    configurations {
        "Debug",
        "Release"
    }

project "CalculatorApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    includedirs {
        "./thirdparty/inja-3.4.0/",
        "./thirdparty/nlohmann-3.11.2/single_include/"
    }

    files {
        "**.cpp",
        "**.h"
    }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release*"
        optimize "On"
