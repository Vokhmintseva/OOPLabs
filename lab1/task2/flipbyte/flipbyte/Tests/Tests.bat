@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM% 55 > %OUT% || goto err
fc %OUT% "%~dp055-out.txt" > nul || goto err
echo Test 1 has passed

%PROGRAM% 0 > %OUT% || goto err
fc %OUT% "%~dp00-out.txt" > nul || goto err
echo Test 2 has passed

%PROGRAM% 255 > %OUT% || goto err
fc %OUT% "%~dp0255-out.txt" > nul || goto err
echo Test 3 has passed

%PROGRAM% 14 > %OUT% || goto err
fc %OUT% "%~dp014-out.txt" > nul || goto err
echo Test 4 has passed

%PROGRAM% 97 > %OUT% || goto err
fc %OUT% "%~dp097-out.txt" > nul || goto err
echo Test 5 has passed

%PROGRAM% 198 > %OUT% || goto err
fc %OUT% "%~dp0198-out.txt" > nul || goto err
echo Test 6 has passed

%PROGRAM% -5 > %OUT% && goto err
echo Test 7 has passed

%PROGRAM% 256 > %OUT% && goto err
echo Test 8 has passed

%PROGRAM% 5F > %OUT% && goto err
echo Test 9 has passed

%PROGRAM% 15 67 > %OUT% && goto err
echo Test 10 has passed

%PROGRAM% > %OUT% && goto err
echo Test 11 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo Program testing has failed
exit /B 1