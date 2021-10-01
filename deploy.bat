set PATH=%PATH%;C:\Qt\6.0.3\msvc2019_64\bin

IF EXIST .\Deploy-Release (
    rmdir .\Deploy-Release /s /q
)
md .\Deploy-Release

windeployqt --dir .\Deploy-Release --no-translations ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release\
copy .\LICENSE .\Deploy-Release\
REM copy .\README.md .\Deploy-Release\

IF EXIST .\Deploy-Release-PDB (
    rmdir .\Deploy-Release-PDB /s /q
)
md .\Deploy-Release-PDB

windeployqt --pdb --dir .\Deploy-Release-PDB --no-translations ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release-PDB\
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtDoppelKopf\release\QtDoppelKopf.map .\Deploy-Release-PDB\
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtDoppelKopf\release\QtDoppelKopf.pdb .\Deploy-Release-PDB\
copy .\LICENSE .\Deploy-Release-PDB\
REM copy .\README.md .\Deploy-Release-PDB\

IF EXIST .\Deploy-Release-Private (
    rmdir .\Deploy-Release-Private /s /q
)
md .\Deploy-Release-Private

windeployqt --dir .\Deploy-Release-Private --no-translations ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release-Private\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release-Private\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release-Private\
copy .\LICENSE .\Deploy-Release-Private\
REM copy .\README.md .\Deploy-Release-Private\

IF EXIST .\Deploy-Release-Private-PDB (
    rmdir .\Deploy-Release-Private-PDB /s /q
)
md .\Deploy-Release-Private-PDB

windeployqt --pdb --dir .\Deploy-Release-Private-PDB --no-translations ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release-Private\QtDoppelKopf\release\QtDoppelKopf.exe
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release-Private\QtDoppelKopf\release\QtDoppelKopf.exe .\Deploy-Release-Private-PDB\
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release-Private\QtDoppelKopf\release\QtDoppelKopf.map .\Deploy-Release-Private-PDB\
copy ..\build-QtDoppelkopfSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release-Private\QtDoppelKopf\release\QtDoppelKopf.pdb .\Deploy-Release-Private-PDB\
copy .\LICENSE .\Deploy-Release-Private-PDB\
REM copy .\README.md .\Deploy-Release-Private-PDB\
