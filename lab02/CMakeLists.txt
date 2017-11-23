project(lab02)

add_library(link_list my_linklist.c)

add_executable(lab02 main.c)

target_link_libraries(lab02 link_list)