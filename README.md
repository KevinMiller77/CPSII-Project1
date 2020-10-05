# CPSII-Project 1

**How to use**

*Windows*

    1) Open a new Powershell instance and navigate the the root dir of the project.
        You can also 'Shift+Right Click' in the folder in Explorer to see the option to open Powershell here
    2) Run 'scripts\premake5 vs2019' to build the .sln file. You may use vs2017 or vs2015 as well according to your installed version.
    3) Open the .sln file created for you in the root dir 
    4) Run as normal

*Unix*

    Prerequisits
    You must have gmake (make) installed in order to compile the project (You probably already do)
    To install, run 'sudo apt-get install make' on Ubuntu and most Debian systems

    1) Open a new terminal and navigate to the root dir
    2) Run 'scripts/premake5 gmake' to generate the make file
    3) Run 'make' to generate the executable with an optional '-jx' flag where x is the number of cores you'd like to compile with
    4) Run './Carpool' to run the program
