echo off
set MODULE=*
if "%XSI_USERHOME%"=="" goto error
set STARTUP=%XSI_USERHOME%\Application\fx\ufos
if not exist "%STARTUP%" mkdir %STARTUP%
copy %MODULE%.dll %STARTUP%

goto end
:error
echo "Variable XSI_USERHOME not define. Make sure to run from a Softimage command prompt."
:end
echo "installation done"