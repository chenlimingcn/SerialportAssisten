@echo off

rem -- delete files of build --
for /r . %%i in (.) do (
REM	if exist "%%i\debug" (
REM		rmdir /s /q "%%i\debug"
REM	)
REM	if exist "%%i\release" (
REM		rmdir /s /q "%%i\release"
REM	)
	if exist "%%i\*.obj" (
		del /f /q "%%i\*.obj"
	)
	if exist "%%i\*.exp" (
		del /f /q "%%i\*.exp"
	)
	if exist "%%i\*.ilk" (
		del /f /q "%%i\*.ilk"
	)
	if exist "%%i\*.old" (
		del /f /q "%%i\*.old"
	)
	if exist "%%i\*.user" (
		del /f /q "%%i\*.user"
	)
	if exist "%%i\*.ncb" (
		del /f /q  "%%i\*.ncb"
	)
	if exist "%%i\*.suo" (
		del /f /q "%%i\*.suo"
		del /f /q /A:h "%%i\*.suo"
	)
	if exist "%%i\*.idb" (
		del /f /q "%%i\*.idb"
	)
	if exist "%%i\*~" (
		del /f /q "%%i\*~"
	)
	if exist "%%i\*.pdb" (
		del /f /q "%%i\*.pdb"
	)
	if exist "%%i\Makefile*" (
		del /f /q "%%i\Makefile*"
	)
    if !%1==!all (
        if exist "%%i\*.sln" (
            del /f /q "%%i\*.sln"
        )
        if exist "%%i\*.vcproj" (
            del /f /q "%%i\*.vcproj"
        )
    )

	:: -- remove .cpptest folder --
    if !%1==!all (
        if exist "%%i\.cpptest" (
            rmdir /s /q "%%i\.cpptest"
        )
        if exist "%%i\.parasoft.dat" (
            rmdir /s /q "%%i\.parasoft.dat"
        )
        if exist "%%i\.parasoft*" (
            del /f /q "%%i\.parasoft*"
        )
    )

	:: -- remove .svn folder --
    if !%1==!all (
        if exist %%i\.svn (
            rmdir /s /q %%i\.svn
        )
    )
)

@pause
