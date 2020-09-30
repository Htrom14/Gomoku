cmake_minimum_required(VERSION 3.10.2)
project (Gomoku)

add_library(gomokuLib STATIC FileHandler.cpp)
install(TARGETS gomokuLib DESTINATION lib)
install(FILES FileHandler.h DESTINATION include)

add_executable(gomoku Main.cpp)
target_link_libraries(gomoku gomokuLib)
install(TARGETS gomoku DESTINATION build)