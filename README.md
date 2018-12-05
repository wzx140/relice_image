## Slice Image
read from mhd image file, and you can use mouse to change the slice of the image 
### PREREQUISITES
* GCC
* VTK
* CMake

### BUILD
#### LINUX
- just run `cd slice_image`, `cmake .`and `make` 
  
- or you can use out-of-source-build
```
cd slice_image
mkdir build
cd build
cmake ..
make
```
- If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build  
`cmake -DVTK_DIR:PATH=/home/me/vtk_build ..`
#### WINDOWS
Be sure to add the VTK **bin** and **lib** directory to your path. This will resolve the VTK dll's at run time

### RUN
`./slice_image`

### TEST
If you want to run the test, just run `cd test` and `./slice_image_test`