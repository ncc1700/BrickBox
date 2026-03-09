
@echo off

SET "build_dir=build"
SET "source_dir=."

if EXIST "%build_dir%\" (
    rd "%build_dir%" /s /q
)
md %build_dir%
cmake -S %source_dir% -B %build_dir%
echo now go to the "%build_dir%" directory and build it there