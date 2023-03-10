set PATH=%PATH%;C:\Qt\6.4.2\msvc2019_64\bin

set SOURCE=build-QtDoppelKopfSuper-Desktop_Qt_6_4_2_MSVC2022_64bit-Release

IF EXIST .\Deploy-Release (
    rmdir .\Deploy-Release /s /q
)
md .\Deploy-Release

windeployqt --dir .\Deploy-Release --no-translations ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release\
copy .\LICENSE .\Deploy-Release\
copy .\README.md .\Deploy-Release\
copy .\LIESMICH.md .\Deploy-Release\

IF EXIST .\Deploy-Release-PDB (
    rmdir .\Deploy-Release-PDB /s /q
)
md .\Deploy-Release-PDB

windeployqt --pdb --dir .\Deploy-Release-PDB --no-translations ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release-PDB\
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.map .\Deploy-Release-PDB\
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.pdb .\Deploy-Release-PDB\
copy .\LICENSE .\Deploy-Release-PDB\
copy .\README.md .\Deploy-Release-PDB\
copy .\LIESMICH.md .\Deploy-Release-PDB\

set SOURCE=build-QtDoppelKopfSuper-Desktop_Qt_6_4_2_MSVC2022_64bit-Release-Private

IF EXIST .\Deploy-Release-Private (
    rmdir .\Deploy-Release-Private /s /q
)
md .\Deploy-Release-Private

windeployqt --dir .\Deploy-Release-Private --no-translations ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release-Private\
copy .\LICENSE .\Deploy-Release-Private\
copy .\README.md .\Deploy-Release-Private\
copy .\LIESMICH.md .\Deploy-Release-Private\

IF EXIST .\Deploy-Release-Private-PDB (
    rmdir .\Deploy-Release-Private-PDB /s /q
)
md .\Deploy-Release-Private-PDB

windeployqt --pdb --dir .\Deploy-Release-Private-PDB --no-translations ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release-Private-PDB\
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.map .\Deploy-Release-Private-PDB\
copy ..\%SOURCE%\QtDoppelKopf\release\QtDoppelKopf.pdb .\Deploy-Release-Private-PDB\
copy .\LICENSE .\Deploy-Release-Private-PDB\
copy .\README.md .\Deploy-Release-Private-PDB\
copy .\LIESMICH.md .\Deploy-Release-Private-PDB\
