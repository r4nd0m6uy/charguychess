set(APP_SOURCES
  chess/Board.cpp
  chess/PlayerPiece.cpp
)

add_library(${APP_LIB_NAME} ${APP_SOURCES})

add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME})