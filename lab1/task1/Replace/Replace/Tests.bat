@echo off

SET MyProgram="%~1"
set OUT="%TEMP%\output.txt"

if %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

%MyProgram% empty.txt %OUT% my REPLACED || goto err
fc %OUT% "%~dp0empty.txt" > nul || goto err
echo test 1 has passed

%MyProgram% input.txt %OUT% ma mama || goto err
fc %OUT% "%~dp0output2.txt" > nul || goto err
echo test 2 has passed

%MyProgram% input.txt %OUT% 1231234 DIGITS || goto err
fc %OUT% "%~dp0output3.txt" > nul || goto err
echo test 3 has passed

%MyProgram% input.txt %OUT% my REPLACED || goto err
fc %OUT% "%~dp0output1.txt" > nul || goto err
echo test 4 has passed

%MyProgram% i.txt %OUT% my REPLACED && goto err
echo test 5 has passed

%MyProgram% input.txt %OUT% my && goto err
echo test 6 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo test failed
exit /B 1