@echo off

SET MyProgram="%~1"
set OUTencrypted="%TEMP%\outputEncrypted.bin"
set OUTdecrypted="%TEMP%\outputDecrypted.bin"

if  %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

%MyProgram% crypt inputToCrypt.bin %OUTencrypted% 10 || goto err
%MyProgram% decrypt %OUTencrypted% %OUTdecrypted% 10 || goto err
fc %OUTdecrypted% inputToCrypt.bin > nul || goto err
echo test 1 has passed

%MyProgram% decryptIt %OUTencrypted% %OUTdecrypted% 10 && goto err
echo test 2 has passed

%MyProgram% crypt inputToCrypt.bin %OUTencrypted% && goto err
echo test 3 has passed

%MyProgram% crypt inputToCrypt.bin %OUTencrypted% 256 && goto err
echo test 4 has passed

%MyProgram% crypt notExistingFile.bin %OUTencrypted% 15 && goto err
echo test 5 has passed

%MyProgram% crypt inputToCrypt.bin %OUTencrypted% 1A && goto err
echo test 6 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo test failed
exit /B 1
