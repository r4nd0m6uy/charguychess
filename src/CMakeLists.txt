set(APP_SOURCES
  chess/Board.cpp
  chess/PlayerPiece.cpp
  chess/Square.cpp
  chess/Move.cpp
  chess/GameLogic.cpp
  chess/IBoardObserver.cpp
  logging/ILogger.cpp
  logging/ILogSink.cpp
  logging/Logger.cpp
  logging/LoggerConsole.cpp
  logging/LoggerInstance.cpp
  logging/LogStream.cpp
)

add_library(${APP_LIB_NAME} ${APP_SOURCES})

add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME})