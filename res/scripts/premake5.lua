
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
