@echo off
cd /d %S200HOME%
echo �����ļ��нṹ����
md %S200HOME%\s200_release
cd /d %S200HOME%\s200_release
echo �����ļ��нṹ��ɣ�
echo.

echo ����QT��ص�DLL����
copy  %QTDIR%\bin\QtCore4.dll %S200HOME%\s200_release\bin
copy  %QTDIR%\bin\QtGui4.dll %S200HOME%\s200_release\bin
copy  %QTDIR%\bin\QtSvg4.dll %S200HOME%\s200_release\bin
copy  %QTDIR%\bin\QtXml4.dll %S200HOME%\s200_release\bin
echo ����QT��ص�DLL��ɣ�
echo.
echo ���Ƶ�������DLL����
copy %S200HOME%\bin\dxflib.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\QtSolutions_PropertyBrowser-head.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xerces-c_3_1.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xlslib.dll %S200HOME%\s200_release\bin
copy %S200HOME%\bin\xqilla23.dll %S200HOME%\s200_release\bin
echo.
echo �����Զ��幦��ģ��DLL����
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
echo ����DLL��ɣ�
echo.
echo ���������򡭡�
copy %S200HOME%\bin\scleditor.exe %S200HOME%\s200_release\bin
copy %S200HOME%\bin\icdeditor.exe %S200HOME%\s200_release\bin
copy %S200HOME%\bin\contrast.exe %S200HOME%\s200_release\bin
echo ������������ɣ�
echo.
pause
