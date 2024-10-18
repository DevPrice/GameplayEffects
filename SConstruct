#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")
sources.extend(Glob("src/**/*.cpp"))

addon_path = "demo/addons/gameplay_effects"
debug_suffix = "" if env["target"] == "template_release" else ".{}".format(env["target"].replace("template_", ""))
arch_suffix = "" if env["platform"] == "windows" and env["arch"] == "x86_64" else ".{}".format(env["arch"])
threads_suffix = "nothreads" if env["platform"] == "web" and not env["threads"] else ""

if env["platform"] == "macos":
    library_name = "gameplayeffects{0}.framework/gameplayeffects{0}".format(debug_suffix),
else:
    library_name = "gameplayeffects{}{}{}{}".format(debug_suffix, arch_suffix, threads_suffix, env["SHLIBSUFFIX"])

library = env.SharedLibrary(
    "/".join([addon_path, "bin", env["platform"], library_name]),
    source=sources,
)

Default(library)

env.Tool('compilation_db')
cdb = env.CompilationDatabase('compile_commands.json')
Alias('cdb', cdb)
