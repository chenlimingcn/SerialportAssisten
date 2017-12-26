@ECHO off
ECHO 把所有工程转化成vc project
ECHO 正在进行……

cd %S200HOME%\dev\
for /r . %%i in (.) do (
	if exist "%%i\*.pro" (
		cd "%%i"
		echo "%%i"
		qmake -tp vc
	)
)

ECHO 工程转化完成
PAUSE