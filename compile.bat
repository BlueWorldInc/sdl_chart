@echo off
echo Compiling...
g++ -O0 -L lib -I include .\src\chart.cpp -o chart -lmingw32 -lSDL2main -lSDL2 -lsdl_circle -lsdl_triangle -lSDL2_ttf && powershell write-host -fore Green Compile success && .\chart.exe