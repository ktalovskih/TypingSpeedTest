cmake_minimum_required(VERSION 3.10)

project(TapingSpeedTest)

set(CMAKE_CXX_STANDARD 20)

# Set the path to Qt6's CMake files, if necessary
set(Qt6_DIR "~/Qt/6.7.2/gcc_64/lib/cmake/Qt6")

# Find Qt6 packages
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/hdr)

# UI files
set(UI_FILES ui/window.ui)
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

# Add executable
add_executable(TapingSpeedTest
    src/main.cpp
    src/mainWindow.cpp
    src/virtualkeyboard.cpp
    src/logic.cpp
    ${UI_FILES}
)

# Link Qt6 libraries
target_link_libraries(TapingSpeedTest Qt6::Core Qt6::Gui Qt6::Widgets)

# Include the build directory to access the generated UI header
target_include_directories(TapingSpeedTest PRIVATE ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/hdr)
