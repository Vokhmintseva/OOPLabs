@echo off

SET MyProgram="%~1"
set OUT="%TEMP%\output.bin"

if  %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

%MyProgram% crypt inputToCrypt.bin %OUT% 10 || goto err
fc %OUT% crypted.bin > nul || goto err
echo test 1 has passed

%MyProgram% decrypt crypted.bin %OUT% 10 || goto err
fc %OUT% inputToCrypt.bin > nul || goto err
echo test 2 has passed

%MyProgram% decryptIt crypted.bin %OUT% 10 && goto err
echo test 3 has passed

%MyProgram% crypt inputToCrypt.bin %OUT% && goto err
echo test 4 has passed

%MyProgram% crypt inputToCrypt.bin %OUT% 256 && goto err
echo test 5 has passed

%MyProgram% crypt notExistingFile.bin %OUT% 15 && goto err
echo test 6 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo test failed
exit /B 1
