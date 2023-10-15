project "sqlite"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files {
        "sqlite/*.c",
        "sqlite/*.h"
    }
