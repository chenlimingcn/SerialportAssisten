@ECHO off
ECHO �����й���ת����vc project
ECHO ���ڽ��С���

cd %S200HOME%\dev\
for /r . %%i in (.) do (
	if exist "%%i\*.pro" (
		cd "%%i"
		echo "%%i"
		qmake -tp vc
	)
)

ECHO ����ת�����
PAUSE