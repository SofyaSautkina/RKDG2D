# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles JOM" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e"

# Include any dependencies generated for this target.
include CMakeFiles\converterUNV.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\converterUNV.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\converterUNV.dir\flags.make

CMakeFiles\converterUNV.dir\FileConverter.cpp.obj: CMakeFiles\converterUNV.dir\flags.make
CMakeFiles\converterUNV.dir\FileConverter.cpp.obj: C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\FileConverter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/converterUNV.dir/FileConverter.cpp.obj"
	C:\Qt\Tools\mingw530_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\converterUNV.dir\FileConverter.cpp.obj -c C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\FileConverter.cpp

CMakeFiles\converterUNV.dir\FileConverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/converterUNV.dir/FileConverter.cpp.i"
	C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\FileConverter.cpp > CMakeFiles\converterUNV.dir\FileConverter.cpp.i

CMakeFiles\converterUNV.dir\FileConverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/converterUNV.dir/FileConverter.cpp.s"
	C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\FileConverter.cpp -o CMakeFiles\converterUNV.dir\FileConverter.cpp.s

CMakeFiles\converterUNV.dir\main.cpp.obj: CMakeFiles\converterUNV.dir\flags.make
CMakeFiles\converterUNV.dir\main.cpp.obj: C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/converterUNV.dir/main.cpp.obj"
	C:\Qt\Tools\mingw530_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\converterUNV.dir\main.cpp.obj -c C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\main.cpp

CMakeFiles\converterUNV.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/converterUNV.dir/main.cpp.i"
	C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\main.cpp > CMakeFiles\converterUNV.dir\main.cpp.i

CMakeFiles\converterUNV.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/converterUNV.dir/main.cpp.s"
	C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV\main.cpp -o CMakeFiles\converterUNV.dir\main.cpp.s

# Object files for target converterUNV
converterUNV_OBJECTS = \
"CMakeFiles\converterUNV.dir\FileConverter.cpp.obj" \
"CMakeFiles\converterUNV.dir\main.cpp.obj"

# External object files for target converterUNV
converterUNV_EXTERNAL_OBJECTS =

converterUNV.exe: CMakeFiles\converterUNV.dir\FileConverter.cpp.obj
converterUNV.exe: CMakeFiles\converterUNV.dir\main.cpp.obj
converterUNV.exe: CMakeFiles\converterUNV.dir\build.make
converterUNV.exe: CMakeFiles\converterUNV.dir\linklibs.rsp
converterUNV.exe: CMakeFiles\converterUNV.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable converterUNV.exe"
	"C:\Program Files\CMake\bin\cmake.exe" -E remove -f CMakeFiles\converterUNV.dir/objects.a
	C:\Qt\Tools\mingw530_32\bin\ar.exe cr CMakeFiles\converterUNV.dir/objects.a @CMakeFiles\converterUNV.dir\objects1.rsp
	C:\Qt\Tools\mingw530_32\bin\g++.exe  -std=c++11   -Wl,--whole-archive CMakeFiles\converterUNV.dir/objects.a -Wl,--no-whole-archive  -o converterUNV.exe -Wl,--out-implib,libconverterUNV.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles\converterUNV.dir\linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles\converterUNV.dir\build: converterUNV.exe

.PHONY : CMakeFiles\converterUNV.dir\build

CMakeFiles\converterUNV.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\converterUNV.dir\cmake_clean.cmake
.PHONY : CMakeFiles\converterUNV.dir\clean

CMakeFiles\converterUNV.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles JOM" C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV C:\Users\vkorchagova\Documents\GitHub\RKDG2D\converterUNV "C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e" "C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e" "C:\Users\vkorchagova\Documents\GitHub\RKDG2D\build-converterUNV-Desktop-u041fu043e u0443u043cu043eu043bu0447u0430u043du0438u044e\CMakeFiles\converterUNV.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\converterUNV.dir\depend

