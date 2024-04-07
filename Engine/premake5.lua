local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Engine")
kind("StaticLib")
language("C++")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/**.h",
    "source/**.cpp",
})

includedirs({
    "source",
})

libdirs({})

links({
    "sfml-graphics",
    "sfml-window",
    "sfml-system",
})

filter("system:linux")
system("linux")
cppdialect("C++17")
systemversion("latest")
defines({
    "PLATFORM_LINUX",
})

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
