@ECHO off
SETLOCAL enabledelayedexpansion
COLOR 1f
cls

ECHO.
ECHO   ##############################################################
ECHO   #               欢迎使用 TeamTalk 工程配置向导               #
ECHO   #                   version 1.0                             		       #
ECHO   ##############################################################
ECHO.

echo make IM protocol buffer files...

REM 将当前工作目录更 改为脚本所在的目录
cd %~dp0

REM 创建PB协议文件目录
mkdir %~dp0\include\ProtocolBuffer
echo copy im protocol buffer files finished

REM 生成PB协议的C++版本
protoc.exe --cpp_out=%~dp0\include\ProtocolBuffer %~dp0\pb\*.proto
echo make pb files of c++ version has finished.

pause

