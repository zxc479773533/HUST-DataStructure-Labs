project(lab04)

add_library(graph my_graph.c)

add_library(libqueue mylibqueue.c)

add_executable(lab04 main.c)

target_link_libraries(lab04 libqueue graph)