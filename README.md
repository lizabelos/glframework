# BELOSGL - OpenGL Framework by BELOS Thomas

![Screenshot](example/solarsystem/res/screenshot_earth.png)

![Screenshot](example/noel/res/screenshot0.png)

![Screenshot](example/noel/res/screenshot1.png)

## Required packages

OpenGL, SDL2, GLEW, GLM, and ASSIMP are required.

You can install these packages on Ubuntu by using : 

```
sudo apt install gcc g++ make cmake git
sudo apt install libsdl2-dev libglew-dev libglm-dev libassimp-dev
```

## Compilation and installation

Clone the repository : 
```
git clone https://github.com/belosthomas/glframework.git
cd glframework
```

Build the project with cmake : 
```
mkdir build
cmake ..
make
```

From your project, you can use the generated ```libbelosgl.a```.


## Example : GL Noel Viewer

From the build directory, go into the executable directory, and run on of the generated binaries
```
cd noel

# Load the default model
./noel

# Load a .obj model with ASSIMP
./noel res/objs/sponza
# or
./noel ASSIMP res/objs/sponza

# Load a GLTF model
./noel GLTF res/gltfs/Buggy.glb
```

Warning : to not specify the extension for .obj files.

## References

### GLTools

#### IMGUI

https://github.com/ocornut/imgui

#### STB Image

https://github.com/nothings/stb

### Example : Solar System

#### Planet Pixel Emporium

http://planetpixelemporium.com/

#### NASA

https://nssdc.gsfc.nasa.gov/planetary/planetfact.html

#### STB Image

https://github.com/nothings/stb

### Example : Noel

#### McGuire Computer Graphics Archive

https://casual-effects.com/data/