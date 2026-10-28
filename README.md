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
