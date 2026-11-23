In order to compile and run this code, you must use CMake, and build the project
with the default presets. It will also require the VCPKG default CMake build. 

To do this, open the terminal and run the following:

cd PATH_TO_buildVCPkg

cmake ..

cmake --build . 

Then, any current and future executables should be runnable through the terminal!

To do this, either choose a scene currently in the 'scenes' directory, or create
a new json file within that directory. After doing that, run:

./renderlib/debug/maincode.exe ../scenes/<scene-file-name>

The output of this will be in the buildVCPackage directory.



| ---- OPENGL ---- |

In order to run any OpenGL scene, follow the steps above up until 
"cmake --build ."
from there any scenes are made inside the "glfwexample" file.

To run this, in the terminal, type:

./OpenGL/Debug/glfwExample.exe

The output of this will appear in a separate window.

The camera is controllable through the "wasd" keys 

w -> move the camera in the -z direction

a -> move the camera in the -x direction

s -> move the camera in the +z direction

d -> move the camera in the +x direction
