# Voxelcraft
Voxelcraft is a clone of the popular indie game called Minecraft, originally created by [Notch](https://x.com/notch?ref_src=twsrc%5Egoogle%7Ctwcamp%5Eserp%7Ctwgr%5Eauthor) and [Mojang Studios](https://www.minecraft.net/en-us/article/meet-mojang-studios).

## About The Project
The project is built with C++ and OpenGL. I wanted to use this as an opportunity to strengthen my skills in C++ and learn more about OpenGL. I then figured, what is better than to clone Minecraft for this exact purpose?
## Current Features
* Currently, I have yet to extensively work on the project, so right now it only renders a small 16x384x16 chunk (length x height x width).
* I am planning on adding the features that are seen in the original game, such as:
  - [x] Chunk loading
  - [ ] Terrain & world generation
  - [ ] Block placement/destruction
  - [ ] Gameplay aspects such as a health bar, inventory, etc.
 
## How to Play
If you are on MacOS, good luck. It shouldn't actually be that hard to generate the correct build for MacOS, given that you know what you are doing. Here is the installation guide for Windows and Linux.

### Prerequisites
* CMake

### Installation Guide For Windows
1. Recursively clone the repository
```markdown
git clone --recurse-submodules https://github.com/kevtu2/voxelcraft.git
```
2. Go into the working directory
```markdown
cd voxelcraft
```
3. Run desired CMake build.
For Visual Studio 2022:
```markdown
cmake -B build -G "Visual Studio 17 2022"
```
4. Inside the build directory that was generated, open the .sln file

5. After building the project solution, the project can be ran/debugged inside of Visual Studio.

###  Installation Guide For Linux
1. Recursively clone the repository
```markdown
git clone --recurse-submodules https://github.com/kevtu2/voxelcraft.git
```
2. Go into the working directory
```markdown
cd voxelcraft
```
3. Run desired CMake build.
For Linux:
```markdown
cmake -B build
```
4. Go into the build directory
```markdown
cd build
```
5. If successful, you can run make inside build to compile the program and run the executable.
```markdown
make
./voxelcraft
```

