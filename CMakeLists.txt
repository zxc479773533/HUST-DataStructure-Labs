project(Make)

add_library(linearlist ./lab01/my_linearlist.c)

add_executable(wsserver ./server/wsserver.c)

target_link_libraries(wsserver linearlist crypto)