-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you
--  wrote the original software. If you use this software in a product, an acknowledgment
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software. <-- yeah... i guess its altered
--
--  3. This notice may not be removed or altered from any source distribution. 
raylib_path = path.join(_MAIN_SCRIPT_DIR, "lib/raylib-master")

lib_path = path.join(_MAIN_SCRIPT_DIR, "lib")
libraries = {"game_objects"}

out_path = path.join(_MAIN_SCRIPT_DIR, "bin/Debug")

newoption {
    trigger = "graphics",
    value = "OPENGL_VERSION",
    description = "version of OpenGL to build raylib against",
    allowed = {
        {"opengl11", "OpenGL 1.1"},
        {"opengl21", "OpenGL 2.1"},
        {"opengl33", "OpenGL 3.3"},
        {"opengl43", "OpenGL 4.3"}
    },
    default = "opengl33"
}

function link_to(lib)
    links(lib)
    local base = path.join(lib_path, lib)
    includedirs(path.join(base, "include"))
    includedirs(path.join(base, ""))
end




function check_raylib()
    print ("Checking for raylib in " .. raylib_path)

    if (os.isdir(raylib_path) == false) then
        if (not os.isfile("raylib-master.zip")) then
            print("Raylib not found, downloading from github")
            local result_str, response_code =
                http.download(
                "https://github.com/raysan5/raylib/archive/refs/heads/master.zip",
                "raylib-master.zip",
                {
                    progress = 
                    function (total, current)
                        local ratio = current / total
                        ratio = math.min(math.max(ratio, 0), 1)
                        local percent = math.floor(ratio * 100)
                        print("Download progress (" .. percent .. "%/100%)")
                    end,
                    headers = {"From: Premake", "Referer: Premake"}
                }
            )
        end
        print("Unzipping to " .. path.getdirectory(raylib_path))
        zip.extract("raylib-master.zip", path.getdirectory(raylib_path))
        os.remove("raylib-master.zip")
    end
end



function platform_defines()
    defines {"PLATFORM_DESKTOP"}

    filter {"options:graphics=opengl43"}
    defines {"GRAPHICS_API_OPENGL_43"}

    filter {"options:graphics=opengl33"}
    defines {"GRAPHICS_API_OPENGL_33"}

    filter {"options:graphics=opengl21"}
    defines {"GRAPHICS_API_OPENGL_21"}

    filter {"options:graphics=opengl11"}
    defines {"GRAPHICS_API_OPENGL_11"}

    filter {"system:macosx"}
    disablewarnings {"deprecated-declarations"}

    filter {"system:linux"}
    defines {"_GLFW_X11"}
    defines {"_GNU_SOURCE"}
    -- This is necessary, otherwise compilation will fail since
    -- there is no CLOCK_MONOTOMIC. raylib claims to have a workaround
    -- to compile under c99 without -D_GNU_SOURCE, but it didn't seem
    -- to work. raylib's Makefile also adds this flag, probably why it went
    -- unnoticed for so long.
    -- It compiles under c11 without -D_GNU_SOURCE, because c11 requires
    -- to have CLOCK_MONOTOMIC
    -- See: https://github.com/raysan5/raylib/issues/2729

    filter {}
end



function link_raylib()
    links {"raylib"}

    includedirs {raylib_path .. "/src"}
    includedirs {raylib_path .. "/src/external"}
    includedirs {raylib_path .. "/src/external/glfw/include"}
    platform_defines()

    filter "action:vs*"
    defines {"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
    dependson {"raylib"}
    links {"raylib.lib"}
    characterset("MBCS")
    buildoptions {"/Zc:__cplusplus"}

    filter "system:windows"
    defines {"_WIN32"}
    links {"winmm", "kernel32", "gdi32"}
    libdirs {"../bin/%{cfg.buildcfg}"}

    filter "system:linux"
    links {"pthread", "m", "dl", "rt", "X11"}

    filter "system:macosx"
    links {
        "OpenGL.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreFoundation.framework",
        "CoreAudio.framework",
        "CoreVideo.framework",
        "AudioToolbox.framework"
    }

    filter {}
end



function include_raylib()
    includedirs {raylib_path .. "/src"}
    includedirs {raylib_path .. "/src/external"}
    includedirs {raylib_path .. "/src/external/glfw/include"}
    platform_defines()

    filter "action:vs*"
    defines {"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}

    filter {}
end

workspaceName = path.getbasename(os.getcwd())

if (string.lower(workspaceName) == "raylib") then
    print("raylib is a reserved name. Name your project directory something else.")
    -- Project generation will succeed, but compilation will definitely fail, so just abort here.
    os.exit()
end


-- WORKSPACE CONFIG

workspace(workspaceName)
configurations {"Debug", "Release"}
platforms {"x64", "x86", "ARM64"}

defaultplatform("x64")

filter "configurations:Debug"
defines {"DEBUG"}
symbols "On"

filter "configurations:Release"
defines {"NDEBUG"}
optimize "On"

filter {"platforms:x64"}
architecture "x86_64"

filter {"platforms:Arm64"}
architecture "ARM64"

filter {}

targetdir (out_path)

if (os.isdir("game")) then
    startproject(workspaceName)
end

cdialect "C99"
cppdialect "C++17"
check_raylib()

project "raylib"
kind "StaticLib"

platform_defines()

location(raylib_path)
language "C"
targetdir (out_path)

filter "action:vs*"
defines {"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
characterset("MBCS")
buildoptions {"/Zc:__cplusplus"}
filter {}

print("Using raylib dir " .. raylib_path)
includedirs {raylib_path .. "/src", raylib_path .. "/src/external/glfw/include"}
vpaths {
    ["Header Files"] = {raylib_path .. "/src/**.h"},
    ["Source Files/*"] = {raylib_path .. "/src/**.c"}
}
files {raylib_path .. "/src/*.h", raylib_path .. "/src/*.c"}

removefiles {raylib_path .. "/src/rcore_*.c"}

--  filter { "system:macosx", "files:" .. raylib_path .. "/src/rglfw.c" }
--        compileas "Objective-C"

filter {}

---------
if (os.isdir("game")) then
    include("game")
end

for k,v in pairs(libraries) do
    local lib = path.join(lib_path, v)
    print("LIBRARY: " .. lib)
    include(lib)
  end