workspace "CalculatorApp"
    architecture "x86_64"

    configurations {
        "Debug",
        "Release"
    }

include "thirdparty/sqlite-3.43.1"

project "CalculatorApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    links {
        "sqlite"
    }

    includedirs {
        "thirdparty/inja-3.4.0/",
        "thirdparty/nlohmann-3.11.2/single_include/",
        "thirdparty/sqlite-3.43.1/",
        "thirdparty/cpp-httplib-0.14.1"
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
