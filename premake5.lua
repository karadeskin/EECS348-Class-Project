workspace "CalculatorApp"
    architecture "x86_64"

    configurations {
        "Debug",
        "Release"
    }

project "CalculatorApp"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")

    files {
        "**.cpp",
        "**.h"
    }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release*"
        optimize "On"
