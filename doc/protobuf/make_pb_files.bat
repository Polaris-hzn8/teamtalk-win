@ECHO off
SETLOCAL enabledelayedexpansion
COLOR 1f
cls

ECHO.
ECHO   ##############################################################
ECHO   #               ��ӭʹ�� TeamTalk ����������               #
ECHO   #                   version 1.0                             		       #
ECHO   ##############################################################
ECHO.

echo make IM protocol buffer files...

REM ����ǰ����Ŀ¼�� ��Ϊ�ű����ڵ�Ŀ¼
cd %~dp0

REM ����PBЭ���ļ�Ŀ¼
mkdir %~dp0\include\ProtocolBuffer
echo copy im protocol buffer files finished

REM ����PBЭ���C++�汾
protoc.exe --cpp_out=%~dp0\include\ProtocolBuffer %~dp0\pb\*.proto
echo make pb files of c++ version has finished.

pause

