add_library(renderlib 
    vec3.h
    color.h
    Framebuffer.h Framebuffer.cpp
)

target_include_directories(renderlib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(renderlib PRIVATE
    PNG::PNG
    ZLIB::ZLIB
)

set_target_properties(renderlib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(mainCode
    mainCode.cpp
)

target_link_libraries(mainCode 
    PRIVATE 
        renderlib 
        PNG::PNG
        ZLIB::ZLIB
)





