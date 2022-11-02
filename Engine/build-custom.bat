@echo off
g++ -Isrc/include -Lsrc/lib custom.cpp src/*.cpp -o out -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -w && del custom.cpp && out