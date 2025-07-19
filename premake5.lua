workspace "Uphonic"
    configurations { "Debug", "Release" }

project "Uphonic"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    targetdir "bin/%{cfg.buildcfg}"

    files {
        "src/**.h",
        "src/**.c",
        "src/**.cpp"
    }
    includedirs {
        ".",
        "src",
        "src/vendor/miniaudio",
        "src/vendor/imgui",
        "src/vendor/vst2sdk",
        "src/vendor/ImGuiFileDialog",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"