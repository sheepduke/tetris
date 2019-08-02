cmake_minimum_required (VERSION 2.8)
project (tetris)

file(GLOB tetris_SRC
  "src/*.cpp")

add_executable(tetris ${tetris_SRC})

TARGET_LINK_LIBRARIES(tetris
  pthread
  ncurses
)

install(TARGETS tetris DESTINATION bin)
