local action = _ACTION or ""

workspace "svg-auto-viewbox"
	location 		("../build/" .. action)
	targetdir		("../build/bin")

  configurations {"Debug", "Release"}
	defines { "GLM_FORCE_RADIANS" }
	filter "action:vs*"
		defines     { "_CRT_SECURE_NO_WARNINGS" }

  project "svg-auto-viewbox"
    kind "ConsoleApp"

		language "C++"
		files {
			"../Externals/glm/**.hpp",
			"../Externals/cmdline/**.h",
			"../Externals/nanosvg/**.h",
			"../Externals/tinyxml2/**.h",
			"../Externals/tinyxml2/**.cpp",
			"../svg-auto-viewbox.cpp"
		}

		includedirs {
			"../Externals",
		}

		filter { "files:../*.cpp" }


		filter "system:linux"
			buildoptions { "-std=c++11"}
			linkoptions  { "-std=c++11"}
			links {"m", "dl"}

		filter "system:macosx"
			platforms 	{"Universal"}
			defines {"MACOSX"}
			links       { "CoreFoundation.framework", "Cocoa.framework", "IOKit.framework"}
			buildoptions { "-mmacosx-version-min=10.4" }
			linkoptions  { "-mmacosx-version-min=10.4" }

		filter "system:windows"
			architecture ("x86")
		filter "configurations:Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"
