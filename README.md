# Voxelcraft
Voxelcraft is a clone of the popular indie game called Minecraft, originally created by [Notch](https://x.com/notch?ref_src=twsrc%5Egoogle%7Ctwcamp%5Eserp%7Ctwgr%5Eauthor) and [Mojang Studios](https://www.minecraft.net/en-us/article/meet-mojang-studios).

## About The Project
The project is built with C++ and OpenGL. I wanted to use this as an opportunity to strengthen my skills in C++ and learn more about OpenGL. I also love Minecraft, so I thought that this would be a great challenge for me. 😺
## Current Features
I am planning on adding more features in the future such as:
  - [x] Chunk generation and management
  - [x] Terrain & world generation
  - [x] Lighting
  - [x] Player & block collisions
  - [x] Gravity
  - [x] ImGui integration for metrics
  - [ ] Day and night cycle
  - [ ] Block placement/destruction
  - [ ] Gameplay aspects such as a health bar, inventory, etc.
  - [ ] Cool world destruction superpowers (For gameplay) 
 
## How to Play
### Controls
* WASD to move around
* Use the mouse to look around
* SPACE to jump [NEW!]
* ESC to pause game [NEW!]

## Installation

### Prerequisites
* C++20
* CMake (3.31+)

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

