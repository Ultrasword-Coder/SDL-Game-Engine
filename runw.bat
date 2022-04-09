@echo off
cls

if exist "main.exe" (
    del "main.exe"
)

g++ -I src -o main.exe main.cpp -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
if not errorlevel 1 (
    "main.exe"
)
