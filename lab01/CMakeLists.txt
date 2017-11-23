project(lab01)

add_library(linear_list my_linearlist.c)

add_executable(lab01 main.c)

target_link_libraries(lab01 linear_list)