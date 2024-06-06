# space-war

## Build command

### Windows
g++.exe -fdiagnostics-color=always -g -I .\include (Get-ChildItem -Recurse -Filter *.cpp -Path .\src, .\model-loader, .\animation | ForEach-Object { $_.FullName }) -o game.exe -lsoil -lopengl32 -lfreeglut -lglew32 -lglu32 -lstdc++ 

### Linux (not tested)
g++ -fdiagnostics-color=always -g -I ./include $(find ./src ./model-loader ./animation -type f -name '*.cpp') -o game -lSOIL -lGL -lglut -lGLEW -lGLU -lstdc++
