@echo off
cd /d %S200HOME%
echo 创建文件夹结构……
md %S200HOME%\s200_release
cd /d %S200HOME%\s200_release
echo 创建文件夹结构完成！
echo.

echo 复制QT相关的DLL……
copy  %QTDIR%\bin\QtCore4.dll %S200HOME%\s200_release\bin
copy  %QTDIR%\bin\QtGui4.dll %S200HOME%\s200_release\bin
copy  %QTDIR%\bin\QtSvg4.dll %S200HOME%\s200_release\bin
copy  %QTDIR%\bin\QtXml4.dll %S200HOME%\s200_release\bin
echo 复制QT相关的DLL完成！
echo.
echo 复制第三方库DLL……
copy %S200HOME%\bin\dxflib.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\QtSolutions_PropertyBrowser-head.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xerces-c_3_1.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xlslib.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xqilla23.dll %S200HOME%\s200_release\bin
echo.
echo 复制自定义功能模块DLL……
copy %S200HOME%\bin\business.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\CIMmerger.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\ContrastManager.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\esframework.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\ftptool.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\iedcfgcode.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\layout.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\qribbon.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\sclcore.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\scldata.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\svgitemcreator.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\utility.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\validator.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\virtualTerminalEditor.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xsdbase.dll %S200HOME%\s200_release\bin
echo.
echo 复制DLL完成！
echo.
echo 复制主程序……
copy %S200HOME%\bin\scleditor.exe %S200HOME%\s200_release\bin
copy %S200HOME%\bin\icdeditor.exe %S200HOME%\s200_release\bin
copy %S200HOME%\bin\contrast.exe %S200HOME%\s200_release\bin
echo 复制主程序完成！
echo.
pause
