cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
# project(torch_app)

# set(CMAKE_PREFIX_PATH "/home/busoye_tm/Documents/matthew/libtorch")
# find_package(Torch REQUIRED)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# add_executable(torch_app torch.cpp)
# target_link_libraries(torch_app "${TORCH_LIBRARIES}")
# set_property(TARGET torch_app PROPERTY CXX_STANDARD 17)


project(tensor C CXX ASM)
add_subdirectory(xtl)
add_subdirectory(xtensor)
add_subdirectory(xtensor-blas)
add_executable(tensor main.cpp)

target_link_libraries(tensor PUBLIC xtensor xtensor-blas)