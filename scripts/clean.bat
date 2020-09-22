@ECHO off
REM Get to proper start directory

ECHO "Cleaning up..."
RMDIR /S /Q project_data bin-int .vs
DEL /Q *.exe *.ilk *.pdb *.sln