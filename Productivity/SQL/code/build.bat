set CommonCompilerFlags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib d3d9.lib Ws2_32.lib

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

REM Windows client build
cl %CommonCompilerFlags% -D_CRT_SECURE_NO_WARNINGS ..\code\identity_insert.cpp /link %CommonLinkerFlags%

popd