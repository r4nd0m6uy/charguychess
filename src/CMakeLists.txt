find_package(PkgConfig REQUIRED)
pkg_search_module(LIBEVENT REQUIRED libevent>=2.0)
message(STATUS "Found libevent version ${LIBEVENT_VERSION}")

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
  ui/ConsoleUI.cpp
  event-loop/IHandledIo.cpp
  event-loop/EventLoop.cpp
)

add_library(${APP_LIB_NAME} ${APP_SOURCES})

include_directories(${LIBEVENT_INCLUDE_DIRS} ../src/)
link_directories(${LIBEVENT_LIBRARIES})

add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME} ${LIBEVENT_LDFLAGS})