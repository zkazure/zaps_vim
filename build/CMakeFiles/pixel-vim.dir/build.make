# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zka_wsl/dev/pixel-vim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zka_wsl/dev/pixel-vim/build

# Include any dependencies generated for this target.
include CMakeFiles/pixel-vim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pixel-vim.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pixel-vim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pixel-vim.dir/flags.make

CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o: /home/zka_wsl/dev/pixel-vim/src/core/key_handler.cpp
CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o -MF CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/core/key_handler.cpp

CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/core/key_handler.cpp > CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.i

CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/core/key_handler.cpp -o CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.s

CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o: /home/zka_wsl/dev/pixel-vim/src/core/mode_manager.cpp
CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o -MF CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/core/mode_manager.cpp

CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/core/mode_manager.cpp > CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.i

CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/core/mode_manager.cpp -o CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.s

CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o: /home/zka_wsl/dev/pixel-vim/src/core/status_bar.cpp
CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o -MF CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/core/status_bar.cpp

CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/core/status_bar.cpp > CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.i

CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/core/status_bar.cpp -o CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.s

CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o: /home/zka_wsl/dev/pixel-vim/src/core/ui_automation.cpp
CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o -MF CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/core/ui_automation.cpp

CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/core/ui_automation.cpp > CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.i

CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/core/ui_automation.cpp -o CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.s

CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o: /home/zka_wsl/dev/pixel-vim/src/core/window_manager.cpp
CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o -MF CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/core/window_manager.cpp

CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/core/window_manager.cpp > CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.i

CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/core/window_manager.cpp -o CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.s

CMakeFiles/pixel-vim.dir/src/main.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/main.cpp.o: /home/zka_wsl/dev/pixel-vim/src/main.cpp
CMakeFiles/pixel-vim.dir/src/main.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/pixel-vim.dir/src/main.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/main.cpp.o -MF CMakeFiles/pixel-vim.dir/src/main.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/main.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/main.cpp

CMakeFiles/pixel-vim.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/main.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/main.cpp > CMakeFiles/pixel-vim.dir/src/main.cpp.i

CMakeFiles/pixel-vim.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/main.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/main.cpp -o CMakeFiles/pixel-vim.dir/src/main.cpp.s

CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o: /home/zka_wsl/dev/pixel-vim/src/mode/hint_mode.cpp
CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o -MF CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/mode/hint_mode.cpp

CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/mode/hint_mode.cpp > CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.i

CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/mode/hint_mode.cpp -o CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.s

CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o: /home/zka_wsl/dev/pixel-vim/src/mode/insert_mode.cpp
CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o -MF CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/mode/insert_mode.cpp

CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/mode/insert_mode.cpp > CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.i

CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/mode/insert_mode.cpp -o CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.s

CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o: /home/zka_wsl/dev/pixel-vim/src/mode/mode_manager.cpp
CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o -MF CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/mode/mode_manager.cpp

CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/mode/mode_manager.cpp > CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.i

CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/mode/mode_manager.cpp -o CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.s

CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o: CMakeFiles/pixel-vim.dir/flags.make
CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o: /home/zka_wsl/dev/pixel-vim/src/mode/normal_mode.cpp
CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o: CMakeFiles/pixel-vim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o -MF CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o.d -o CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o -c /home/zka_wsl/dev/pixel-vim/src/mode/normal_mode.cpp

CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.i"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zka_wsl/dev/pixel-vim/src/mode/normal_mode.cpp > CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.i

CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.s"
	x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zka_wsl/dev/pixel-vim/src/mode/normal_mode.cpp -o CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.s

# Object files for target pixel-vim
pixel__vim_OBJECTS = \
"CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/main.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o" \
"CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o"

# External object files for target pixel-vim
pixel__vim_EXTERNAL_OBJECTS =

pixel-vim: CMakeFiles/pixel-vim.dir/src/core/key_handler.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/core/mode_manager.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/core/status_bar.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/core/ui_automation.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/core/window_manager.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/main.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/mode/hint_mode.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/mode/insert_mode.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/mode/mode_manager.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/src/mode/normal_mode.cpp.o
pixel-vim: CMakeFiles/pixel-vim.dir/build.make
pixel-vim: CMakeFiles/pixel-vim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zka_wsl/dev/pixel-vim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable pixel-vim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pixel-vim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pixel-vim.dir/build: pixel-vim
.PHONY : CMakeFiles/pixel-vim.dir/build

CMakeFiles/pixel-vim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pixel-vim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pixel-vim.dir/clean

CMakeFiles/pixel-vim.dir/depend:
	cd /home/zka_wsl/dev/pixel-vim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zka_wsl/dev/pixel-vim /home/zka_wsl/dev/pixel-vim /home/zka_wsl/dev/pixel-vim/build /home/zka_wsl/dev/pixel-vim/build /home/zka_wsl/dev/pixel-vim/build/CMakeFiles/pixel-vim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pixel-vim.dir/depend

