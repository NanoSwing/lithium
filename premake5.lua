workspace "Lithium"
	architecture "x64"
	configurations { "debug", "release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "lithium"
	location "lithium"
	kind "SharedLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.c" }
	includedirs { "%{prj.name}/src", "%{prj.name}/include" }

	defines {
		"LI_BUILD_DLL"
	}

	postbuildcommands {
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/testbed")
	}

	filter "configurations:Debug"
		defines "LI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

project "testbed"
	location "testbed"
	kind "ConsoleApp"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.c" }
	includedirs { "%{prj.name}/src", "lithium/include" }

	defines {}

	links {
		"lithium"
	}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"
