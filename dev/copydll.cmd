@ECHO OFF 
@ECHO 杀死进程
TASKKILL /im scleditor.exe /f
@ECHO 复制 dll 开始......
COPY /Y  /B %S200HOME%\dev\lib\*.dll %S200HOME%\bin\ /B
@ECHO 复制完成
pause