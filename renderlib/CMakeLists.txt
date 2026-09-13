add_library(renderlib 
    vec3.h
    color.h
    dummy.cpp
)

set_target_properties(renderlib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(mainCode
    mainCode.cpp
)

target_link_libraries(mainCode PRIVATE renderlib)