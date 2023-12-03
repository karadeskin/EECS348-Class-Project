workspace "CalculatorApp"
    architecture "x86_64"

    configurations {
        "Debug",
        "Release"
    }

include "thirdparty/sqlite-3.43.1"

project "Calculator"
    kind "StaticLib"
    language "C++"
    cppdialect "C++2a"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    links {
        "sqlite"
    }

    filter "system:Linux"
        links {
            "pthread",
            "dl"
        }

    filter {}

    includedirs {
        "thirdparty/inja-3.4.0/",
        "thirdparty/nlohmann-3.11.2/single_include/",
        "thirdparty/sqlite-3.43.1/",
        "thirdparty/cpp-httplib-0.14.1"
    }

    files {
        "calculator/Evaluator.cpp",
        "calculator/Interface.cpp",
        "calculator/Tokenizer.cpp",
        "calculator/**.h",
    }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release*"
        optimize "On"


project "Website"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++2a"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    links {
        "sqlite",
        "Calculator"
    }

    filter "system:Linux"
        links {
            "pthread",
            "dl"
        }

    filter {}


    includedirs {
        "thirdparty/inja-3.4.0/",
        "thirdparty/nlohmann-3.11.2/single_include/",
        "thirdparty/sqlite-3.43.1/",
        "thirdparty/cpp-httplib-0.14.1",
        "calculator/"
    }

    files {
        "website/**.cpp",
        "website/**.hpp",
        "website/**.h",
        "include/**.h"
    }

    postbuildcommands {
        "cp ./bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name} ./www/%{prj.name}"
    }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release*"
        optimize "On"
