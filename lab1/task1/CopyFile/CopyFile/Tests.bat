@echo off

REM путь к программе передается через первый аргумент командной строки и присваивается переменной окр. MyProgram
SET MyProgram="%~1"

REM защита от запуска без аргумента
if  %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

REM copy empty file
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo test 1 has passed

REM copy not empty file
%MyProgram% notEmpty.txt "%TEMP%\output.txt" || goto err
fc notEmpty.txt "%TEMP%\output.txt" > nul || goto err
echo test 2 has passed

REM copy missing file should fail
%MyProgram% missingFile.txt "%TEMP%\output.txt" && goto err
echo test 3 has passed

REM if output file is not specified the program should fail
%MyProgram% notEmpty.txt && goto err
echo test 4 has passed

REM too many arguments in the command line
%MyProgram% notEmpty.txt "%TEMP%\output.txt" excessFile.txt && goto err
echo test 5 has passed

REM if input and output files are not specified the program should fail
%MyProgram% && goto err
echo test 6 has passed

REM тесты прошли успешно
echo All the tests have passed successfully
exit /B 0

REM сюда будем попадать в случае ошибки
:err
echo test failed
exit /B 1