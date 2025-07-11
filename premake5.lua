workspace "Uphonic"
    configurations { "debug", "release" }

project "Uphonic"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.system}"

    files { "src/**.h", "src/**.c", "src/**.cpp" }
    includedirs {
        ".",
        "src",
        "src/vendor/miniaudio",
        "src/vendor/imgui",
        "src/vendor/glfw/include"
    }
    
    -- glfw excludes
    excludes { "src/vendor/glfw/tests/**.c", "src/vendor/glfw/examples/**.c", "src/vendor/glfw/deps/**.c" }

    filter { "system:windows" }
        links { "opengl32" }
        defines { "_GLFW_WIN32" }

    filter { "system:linux" }
        links { "GL" }
        defines { "_GLFW_X11" } -- todo: add Wayland support

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"