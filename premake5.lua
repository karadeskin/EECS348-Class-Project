workspace "CalculatorApp"
    configurations {
        "Debug",
        "Release"
    }

project "CalculatorApp"
    kind "ConsoleApp"
    language "C++"

    files {
        "**.cpp",
        "**.h"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
