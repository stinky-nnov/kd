# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stinky/projects/kd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stinky/projects/kd/build

# Include any dependencies generated for this target.
include CMakeFiles/kd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kd.dir/flags.make

CMakeFiles/kd.dir/logger.cpp.o: CMakeFiles/kd.dir/flags.make
CMakeFiles/kd.dir/logger.cpp.o: ../logger.cpp
CMakeFiles/kd.dir/logger.cpp.o: logger.moc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stinky/projects/kd/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/kd.dir/logger.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kd.dir/logger.cpp.o -c /home/stinky/projects/kd/logger.cpp

CMakeFiles/kd.dir/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kd.dir/logger.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/stinky/projects/kd/logger.cpp > CMakeFiles/kd.dir/logger.cpp.i

CMakeFiles/kd.dir/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kd.dir/logger.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/stinky/projects/kd/logger.cpp -o CMakeFiles/kd.dir/logger.cpp.s

CMakeFiles/kd.dir/logger.cpp.o.requires:
.PHONY : CMakeFiles/kd.dir/logger.cpp.o.requires

CMakeFiles/kd.dir/logger.cpp.o.provides: CMakeFiles/kd.dir/logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/kd.dir/build.make CMakeFiles/kd.dir/logger.cpp.o.provides.build
.PHONY : CMakeFiles/kd.dir/logger.cpp.o.provides

CMakeFiles/kd.dir/logger.cpp.o.provides.build: CMakeFiles/kd.dir/logger.cpp.o
.PHONY : CMakeFiles/kd.dir/logger.cpp.o.provides.build

CMakeFiles/kd.dir/kd.cpp.o: CMakeFiles/kd.dir/flags.make
CMakeFiles/kd.dir/kd.cpp.o: ../kd.cpp
CMakeFiles/kd.dir/kd.cpp.o: kd.moc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stinky/projects/kd/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/kd.dir/kd.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kd.dir/kd.cpp.o -c /home/stinky/projects/kd/kd.cpp

CMakeFiles/kd.dir/kd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kd.dir/kd.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/stinky/projects/kd/kd.cpp > CMakeFiles/kd.dir/kd.cpp.i

CMakeFiles/kd.dir/kd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kd.dir/kd.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/stinky/projects/kd/kd.cpp -o CMakeFiles/kd.dir/kd.cpp.s

CMakeFiles/kd.dir/kd.cpp.o.requires:
.PHONY : CMakeFiles/kd.dir/kd.cpp.o.requires

CMakeFiles/kd.dir/kd.cpp.o.provides: CMakeFiles/kd.dir/kd.cpp.o.requires
	$(MAKE) -f CMakeFiles/kd.dir/build.make CMakeFiles/kd.dir/kd.cpp.o.provides.build
.PHONY : CMakeFiles/kd.dir/kd.cpp.o.provides

CMakeFiles/kd.dir/kd.cpp.o.provides.build: CMakeFiles/kd.dir/kd.cpp.o
.PHONY : CMakeFiles/kd.dir/kd.cpp.o.provides.build

CMakeFiles/kd.dir/main.cpp.o: CMakeFiles/kd.dir/flags.make
CMakeFiles/kd.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stinky/projects/kd/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/kd.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kd.dir/main.cpp.o -c /home/stinky/projects/kd/main.cpp

CMakeFiles/kd.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kd.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/stinky/projects/kd/main.cpp > CMakeFiles/kd.dir/main.cpp.i

CMakeFiles/kd.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kd.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/stinky/projects/kd/main.cpp -o CMakeFiles/kd.dir/main.cpp.s

CMakeFiles/kd.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/kd.dir/main.cpp.o.requires

CMakeFiles/kd.dir/main.cpp.o.provides: CMakeFiles/kd.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/kd.dir/build.make CMakeFiles/kd.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/kd.dir/main.cpp.o.provides

CMakeFiles/kd.dir/main.cpp.o.provides.build: CMakeFiles/kd.dir/main.cpp.o
.PHONY : CMakeFiles/kd.dir/main.cpp.o.provides.build

logger.moc: ../logger.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stinky/projects/kd/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating logger.moc"
	/usr/bin/moc -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtDBus -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtSvg -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/home/stinky/projects/kd/build -o /home/stinky/projects/kd/build/logger.moc /home/stinky/projects/kd/logger.h

kd.moc: ../kd.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stinky/projects/kd/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating kd.moc"
	/usr/bin/moc -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtDBus -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtSvg -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/home/stinky/projects/kd/build -o /home/stinky/projects/kd/build/kd.moc /home/stinky/projects/kd/kd.h

# Object files for target kd
kd_OBJECTS = \
"CMakeFiles/kd.dir/logger.cpp.o" \
"CMakeFiles/kd.dir/kd.cpp.o" \
"CMakeFiles/kd.dir/main.cpp.o"

# External object files for target kd
kd_EXTERNAL_OBJECTS =

kd: CMakeFiles/kd.dir/logger.cpp.o
kd: CMakeFiles/kd.dir/kd.cpp.o
kd: CMakeFiles/kd.dir/main.cpp.o
kd: /usr/lib/qt4/libQtCore.so
kd: /usr/lib/qt4/libQtGui.so
kd: CMakeFiles/kd.dir/build.make
kd: CMakeFiles/kd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable kd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kd.dir/build: kd
.PHONY : CMakeFiles/kd.dir/build

CMakeFiles/kd.dir/requires: CMakeFiles/kd.dir/logger.cpp.o.requires
CMakeFiles/kd.dir/requires: CMakeFiles/kd.dir/kd.cpp.o.requires
CMakeFiles/kd.dir/requires: CMakeFiles/kd.dir/main.cpp.o.requires
.PHONY : CMakeFiles/kd.dir/requires

CMakeFiles/kd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kd.dir/clean

CMakeFiles/kd.dir/depend: logger.moc
CMakeFiles/kd.dir/depend: kd.moc
	cd /home/stinky/projects/kd/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stinky/projects/kd /home/stinky/projects/kd /home/stinky/projects/kd/build /home/stinky/projects/kd/build /home/stinky/projects/kd/build/CMakeFiles/kd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kd.dir/depend

