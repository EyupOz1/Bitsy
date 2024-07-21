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

project_name = "Bitsy"

game_dir = "game"

libraries = {}

raylib_path = path.join(_MAIN_SCRIPT_DIR, "lib/raylib-master")
lib_path = path.join(_MAIN_SCRIPT_DIR, "3rd")
out_path = path.join(_MAIN_SCRIPT_DIR, "bin/Debug")

-- Include helper functions
include(path.join(path.join(_MAIN_SCRIPT_DIR, "res"), "scripts"))

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


-- WORKSPACE CONFIG

workspace(project_name)
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

startproject(project_name)

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

include(game_dir)

for k,v in pairs(libraries) do
    local lib = path.join(lib_path, v)
    print("LIBRARY: " .. lib)
    include(lib)
    
  end