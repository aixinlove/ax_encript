PROJECT(axencript)
ADD_LIBRARY(axencript ax_encript.c)
ADD_EXECUTABLE(main main.c)
TARGET_LINK_LIBRARIES(main axencript)

