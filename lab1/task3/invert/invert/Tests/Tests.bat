@echo off

SET MyProgram="%~1"
set OUT="%TEMP%\output.txt"

if  %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

%MyProgram% matrix.txt > %OUT% || goto err
fc %OUT% "%~dp0matrix-out.txt" > nul || goto err
echo test 1 has passed

%MyProgram% matrix2.txt > %OUT% || goto err
fc %OUT% "%~dp0matrix2-out.txt" > nul || goto err
echo test 2 has passed

%MyProgram% matrix2x2.txt && goto err
echo test 3 has passed

%MyProgram% matrix4x5.txt && goto err
echo test 4 has passed

%MyProgram% matrix3.txt > %OUT% || goto err
fc %OUT% "%~dp0matrix3-out.txt" > nul || goto err
echo test 5 has passed

%MyProgram% matrixNotNumber.txt && goto err
echo test 6 has passed

%MyProgram% matrix2.txt matrix3.txt && goto err
echo test 7 has passed

%MyProgram% empty.txt && goto err
echo test 8 has passed

%MyProgram% matrix0determ.txt > %OUT% || goto err
fc %OUT% "%~dp0matrix0determ-output.txt" > nul || goto err
echo test 9 has passed

%MyProgram% matrix3x5.txt && goto err
echo test 10 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo test failed
exit /B 1