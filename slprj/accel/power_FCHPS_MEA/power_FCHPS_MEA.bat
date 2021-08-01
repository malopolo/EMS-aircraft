@echo off
set "VSCMD_START_DIR=%CD%"
call "D:\Visual Studio\IDE\VC\Auxiliary\Build\VCVARSALL.BAT" amd64

cd .
nmake -f power_FCHPS_MEA.mk  NON_ANSI_TRIG_FCN=1 OPTS="-DTID01EQ=0"
@if errorlevel 1 goto error_exit
exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1