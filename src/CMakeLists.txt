find_package(PkgConfig REQUIRED)
pkg_search_module(LIBEVENT REQUIRED libevent>=2.0)
message(STATUS "Found libevent version ${LIBEVENT_VERSION}")

set(APP_SOURCES
  chess/ChessDefinitions.cpp
  chess/Board.cpp
  chess/PlayerPiece.cpp
  chess/Square.cpp
  chess/Move.cpp
  chess/LegalSquares.cpp
  chess/GameLogic.cpp
  chess/IBoardObserver.cpp
  logging/ILogger.cpp
  logging/ILogSink.cpp
  logging/Logger.cpp
  logging/LoggerConsole.cpp
  logging/LoggerInstance.cpp
  logging/LogStream.cpp
  ui/console/ConsoleUI.cpp
  ui/hardware/ChessHardware.cpp
  ui/hardware/IBoardInputDriver.cpp
  ui/hardware/IBoardInputDriverObservable.cpp
  ui/hardware/IBoardInputObserver.cpp
  ui/hardware/BoardInputDriverPolled.cpp
  ui/hardware/ChessHardwareFactory.cpp
  ui/hardware/cgc/BoardInputDriverCharGuy.cpp
  ui/hardware/simulation/BoardInputDriverPipe.cpp
  ui/hardware/BitBoard.cpp
  event-loop/IHandledIo.cpp
  event-loop/IHandledSignal.cpp
  event-loop/HandledByLibevent.cpp
  event-loop/HandledIoLibevent.cpp
  event-loop/HandledSignalLibevent.cpp
  event-loop/EventLoop.cpp
  event-loop/HandledQuitSignal.cpp
)

add_library(${APP_LIB_NAME} ${APP_SOURCES})

include_directories(${LIBEVENT_INCLUDE_DIRS} ../src/)
link_directories(${LIBEVENT_LIBRARIES})

add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME} ${LIBEVENT_LDFLAGS})

add_executable(cgcTestInputDriver InputDriverTest.cpp)
target_link_libraries(cgcTestInputDriver ${APP_LIB_NAME})