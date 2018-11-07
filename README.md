## Slice Image
read from mhd image file, and you can use mouse to change the slice of the image 
### PREREQUISITES
* GCC
* VTK
* CMake
* googletest  
need it only if you want to run test
### BUILD
1. Change the value of *VTK_ROOT* and *GTEST_ROOT* (optional) in *CMakeLists.txt*  
If you use linux, you can add your VTK and GTest to environment variable and comment out that two lines of code

2. Change the value of *CMAKE_BUILD_TYPE* in keep with your version of VTK

3. `cd slice_image` 

4. `cmake .`

5. `make`

6. `./slice_image`

### TEST
If you want to run the test, try the following steps
1. undo comment out the main function for GTest in main.cpp and comment out the default main function
2. introduce the GTest Libraries, see [BUILD](#BUILD)

### PROBLEM
If you meet up with the problem *vtkMetaImageReader (0x55e565f78af0): MetaImage cannot parse file.*, maybe because you use the out-of-source-build. You can copy the dir *res* to your build path