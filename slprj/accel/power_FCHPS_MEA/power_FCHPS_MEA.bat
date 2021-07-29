@echo off
set MATLAB=G:\Matlab_2b\software
"%MATLAB%\bin\win64\gmake" -f power_FCHPS_MEA.mk  NON_ANSI_TRIG_FCN=1 OPTS="-DTID01EQ=0"
