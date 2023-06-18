cmake_minimum_required(VERSION 3.5)

project(Tultip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    src/main.cpp
    src/Block/Block.cpp
)

set(HEADER_FILES
    src/Block/Block.h
    src/Block/Transaction/Transaction.h
)

add_executable(Tultip ${SOURCE_FILES} ${HEADER_FILES})

find_package(OpenSSL REQUIRED)
add_subdirectory(thirdparty/leveldb)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto leveldb)
include_directories(${OPENSSL_INCLUDE_DIR})
add_subdirectory(thirdparty/json)
include_directories(thirdparty/json/include)

install(TARGETS Tultip
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
