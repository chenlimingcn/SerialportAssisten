@ECHO OFF 
@ECHO ɱ������
TASKKILL /im scleditor.exe /f
@ECHO ���� dll ��ʼ......
COPY /Y  /B %S200HOME%\dev\lib\*.dll %S200HOME%\bin\ /B
@ECHO �������
pause