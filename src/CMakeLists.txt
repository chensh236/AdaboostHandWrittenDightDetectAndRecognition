project (main)

add_definitions(-std=c++11)

file(GLOB_RECURSE main_SOURCES "src/*.cpp")

set (main_INCLUDE_DIRS "")
foreach (_headerFile ${main_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND main_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES main_INCLUDE_DIRS)

include_directories(${main_INCLUDE_DIRS})
find_package( OpenCV REQUIRED )
add_executable (main ${main_SOURCES})
target_link_libraries( main ${OpenCV_LIBS} )