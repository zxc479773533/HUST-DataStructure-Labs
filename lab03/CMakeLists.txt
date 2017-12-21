project(lab03)

add_library(binary_tree my_binarytree.c)

add_library(libqueue mylibqueue.c)

add_executable(lab03 main.c)

target_link_libraries(lab03 libqueue binary_tree)