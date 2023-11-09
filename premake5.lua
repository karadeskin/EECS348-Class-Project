workspace "CalculatorApp"
    architecture "x86_64"

    configurations {
        "Debug",
        "Release"
    }

include "thirdparty/sqlite-3.43.1"

project "Calculator"
    kind "ConsoleApp"
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
        "calculator/**.cpp",
        "calculator/**.h",
        "include/**.h"
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
        "website/**.cpp",
        "website/**.hpp",
        "website/**.h",
        "include/**.h"
    }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release*"
        optimize "On"
