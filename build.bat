@echo off
g++ -std=c++17 -O2 -Wall src\*.cpp src\alumno2\*.cpp -o genoma.exe
if errorlevel 1 (
  echo Error de compilacion
  pause
  exit /b 1
)
genoma.exe data\HIV2_ALL_2021_env_DNA.2000.fasta
pause
