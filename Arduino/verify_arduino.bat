@echo on
setlocal enabledelayedexpansion

:: Call the Python script and capture the selected file path
for /f "delims=" %%i in ('python select_file.py') do set FILEPATH=%%i

:: Check if a file was selected
if not defined FILEPATH (
    echo No file selected.
    exit /b 1
)

:: Run arduino-cli to upload the selected file
arduino-cli verify -p COM3 --fqbn arduino:avr:uno "%FILEPATH%"

pause
