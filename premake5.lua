workspace "Uphonic"
    configurations { "Debug", "Release" }

project "Uphonic"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.c", "src/**.cpp" }
    includedirs {
        ".",
        "src",
        "src/vendor/miniaudio",
        "src/vendor/imgui",
        "src/vendor/glfw/include"
    }

    links { "opengl32" }

    filter { "system:windows" }
        defines { "_GLFW_WIN32" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"