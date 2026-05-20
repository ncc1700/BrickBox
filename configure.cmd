
@echo off

SET "bbnet_dir=bbnet"
SET "build_dir=build"
SET "source_dir=."


if EXIST "%bbnet_dir%\" (
    rd "%bbnet_dir%" /s /q
)

if EXIST "%build_dir%\" (
    rd "%build_dir%" /s /q
)

git clone https://github.com/ncc1700/brickbox-net.git bbnet

md %build_dir%
cmake -S %source_dir% -B %build_dir%
echo now go to the "%build_dir%" directory and build it there