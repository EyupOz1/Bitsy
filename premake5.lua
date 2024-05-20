-- https://github.com/raylib-extras/game-premake

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
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.


workspaceName = "Bitsy"
gameFolderName = "game"
raylibPath = "lib/raylib-master"


function download_progress(total, current)
    local ratio = current / total;
    ratio = math.min(math.max(ratio, 0), 1);
    local percent = math.floor(ratio * 100);
    print("Download progress (" .. percent .. "%/100%)")
end

function check_raylib()
    if(os.isdir("lib/raylib") == false and os.isdir(raylibPath) == false) then
        if(not os.isfile("raylib-master.zip")) then
            print("Raylib not found, downloading from github")
            local result_str, response_code = http.download("https://github.com/raysan5/raylib/archive/refs/heads/master.zip", "raylib-master.zip", {
                progress = download_progress,
                headers = { "From: Premake", "Referer: Premake" }
            })
        end
        print("Unzipping to " ..  "lib")
        zip.extract("raylib-master.zip", "lib")
        os.remove("raylib-master.zip")
    end
end

function platform_defines()
    defines{"PLATFORM_DESKTOP"}

    filter {"options:graphics=opengl43"}
        defines{"GRAPHICS_API_OPENGL_43"}

    filter {"options:graphics=opengl33"}
        defines{"GRAPHICS_API_OPENGL_33"}

    filter {"options:graphics=opengl21"}
        defines{"GRAPHICS_API_OPENGL_21"}

    filter {"options:graphics=opengl11"}
        defines{"GRAPHICS_API_OPENGL_11"}

    filter {"system:macosx"}
        disablewarnings {"deprecated-declarations"}

    filter {"system:linux"}
        defines {"_GLFW_X11"}
        defines {"_GNU_SOURCE"}

    filter{}
end


function link_raylib()
    links {"raylib"}

    includedirs {raylibPath .. "/src" }
    includedirs {raylibPath .."/src/external" }
    includedirs {raylibPath .."/src/external/glfw/include" }
    platform_defines()

    filter "action:vs*"
        defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
        dependson {"raylib"}
        links {"raylib.lib"}
        characterset ("MBCS")
        buildoptions { "/Zc:__cplusplus" }

    filter "system:windows"
        defines{"_WIN32"}
        links {"winmm", "gdi32"}
        libdirs {"../bin/%{cfg.buildcfg}"}

    filter "system:linux"
        links {"pthread", "m", "dl", "rt", "X11"}

    filter "system:macosx"
        links {"OpenGL.framework", "Cocoa.framework", "IOKit.framework", "CoreFoundation.framework", "CoreAudio.framework", "CoreVideo.framework", "AudioToolbox.framework"}

    filter{}
end

function include_raylib()
    includedirs {raylibPath .."/src" }
    includedirs {raylibPath .."/src/external" }
    includedirs {raylibPath .."/src/external/glfw/include" }
    platform_defines()

    filter "action:vs*"
        defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}

    filter{}
end





newoption
{
    trigger = "graphics",
    value = "OPENGL_VERSION",
    description = "version of OpenGL to build raylib against",
    allowed = {
        { "opengl11", "OpenGL 1.1"},
        { "opengl21", "OpenGL 2.1"},
        { "opengl33", "OpenGL 3.3"},
        { "opengl43", "OpenGL 4.3"}
    },
    default = "opengl33"
}

if (string.lower(workspaceName) == "raylib") then
        -- Project generation will succeed, but compilation will definitely fail, so just abort here.    
        os.exit()
        print("raylib is a reserved name. Name your project directory something else.")
end    

workspace (workspaceName)
    configurations { "Debug", "Release"}
    platforms { "x64", "x86", "ARM64"}

    defaultplatform ("x64")

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"    
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x64" }    
        architecture "x86_64"

    filter { "platforms:Arm64" }    
        architecture "ARM64"

    filter {}    

    targetdir "bin/%{cfg.buildcfg}/"

    startproject(gameFolderName)

cdialect "C99"    
cppdialect "C++17"
check_raylib();

function string.starts(String,Start)
    return string.sub(String,1,string.len(Start))==Start
end    








project "raylib"
    kind "StaticLib"
    raylib_dir = raylibPath

    platform_defines()

    location (raylib_dir)
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    filter "action:vs*"
        defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
        characterset ("MBCS")
        buildoptions { "/Zc:__cplusplus" }
    filter{}

    print ("Using raylib dir " .. raylib_dir);
    includedirs {raylib_dir .. "/src", raylib_dir .. "/src/external/glfw/include" }
    vpaths
    {
        ["Header Files"] = { raylib_dir .. "/src/**.h"},
        ["Source Files/*"] = { raylib_dir .. "/src/**.c"},
    }
    files {raylib_dir .. "/src/*.h", raylib_dir .. "/src/*.c"}

    removefiles {raylib_dir .. "/src/rcore_*.c"}

      filter { "system:macosx", "files:" .. raylib_dir .. "/src/rglfw.c" }
          compileas "Objective-C"

    filter{}

link_raylib()


-- "Compile"
include (gameFolderName)
include ("lib/example_library")
