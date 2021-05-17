@echo off

REM Compiler Flags:
REM Zi                      : Debug info (Z7 older debug format for complex builds)
REM Zo                      : More debug info for optimized builds
REM FC                      : Full path on errors
REM Oi                      : Always do intrinsics with you can
REM Od                      : No optimizations
REM O1                      : Optimizations (Minimize Size)
REM O2                      : Full optimizations (Maximize Speed)
REM MT                      : Use the c static lib instead of searching for dll at run-time
REM MTd                     : Sabe as MT but using the debug version of CRT
REM GR-                     : Turn off C++ run-time type info
REM Gm-                     : Turn off incremental build
REM EHa-                    : Turn off exception handling
REM WX                      : Treat warning as errors
REM W4                      : Set Warning level to 4 (Wall to all levels)
REM wd                      : Ignore warning
REM fp:fast                 : Ignores the rules in some cases to optimize fp operations
REM Fmfile.map              : Outputs a map file (mapping of the functions on the exr)

REM Linker Options:
REM subsystem:windows,5.1   : Make exe compatible with Windows XP (only works on x86)
REM opt:ref                 : Don't put unused things in the exe
REM incremental:no          : Don't need to do incremental builds
REM LD                      : Build a dll
REM PDB:file.pdb            : Change the .pdb's path
REM Debug:fastlink          : Allows for faster linking. Generates a limited .pdb that cannot be used for debugging.

set application_name=ws
set build_options=-DBUILD_WIN32=1
set compile_flags=-nologo /O2 /FC /EHsc
set linker_flags = -incremental:no -opt:ref

if not exist build mkdir build
pushd build

start /b /wait "" "cl.exe" %build_options% %compile_flags% ../main.cpp /link %linker_flags% /out:%application_name%.exe

popd