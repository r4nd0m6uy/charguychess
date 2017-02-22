find_package(PkgConfig REQUIRED)
pkg_search_module(LIBEVENT REQUIRED libevent>=2.0)
message(STATUS "Found libevent version ${LIBEVENT_VERSION}")

set(APP_SOURCES
  chess/ChessDefinitions.cpp
  chess/Board.cpp
  chess/PlayerPiece.cpp
  chess/Square.cpp
  chess/Move.cpp
  chess/SquaresList.cpp
  chess/LegalSquares.cpp
  chess/GameLogic.cpp
  chess/IBoardObserver.cpp
  chess/GameTurn.cpp
  chess/GameHistory.cpp
  logging/ILogger.cpp
  logging/ILogSink.cpp
  logging/Logger.cpp
  logging/LoggerConsole.cpp
  logging/LoggerNull.cpp
  logging/NullLogSink.cpp
  logging/LoggerInstance.cpp
  logging/LogStream.cpp
  ui/console/ConsoleUI.cpp
  ui/hardware/ChessHardware.cpp
  ui/hardware/IBoardInputDriver.cpp
  ui/hardware/IBoardInputDriverObservable.cpp
  ui/hardware/IBoardInputObserver.cpp
  ui/hardware/BoardInputDriverPolled.cpp
  ui/hardware/ChessHardwareFactory.cpp
  ui/hardware/DispatchedBoardInputEvent.cpp
  ui/hardware/BitBoard.cpp
  ui/hardware/cgc/BoardInputDriverCharGuy.cpp
  ui/hardware/simulation/BoardInputDriverPipe.cpp
  ui/hardware/states/IHardwareStatePool.cpp
  ui/hardware/states/HardwareStatePool.cpp
  ui/hardware/states/IHardwareState.cpp
  ui/hardware/states/HardwareStateNull.cpp
  ui/hardware/states/HardwareStatePlayerThinking.cpp
  ui/hardware/states/HardwareStatePieceLifted.cpp
  ui/hardware/states/HardwareStateCapture.cpp
  ui/hardware/states/HardwareStatePanic.cpp
  event-loop/IHandledIo.cpp
  event-loop/IHandledSignal.cpp
  event-loop/HandledByLibevent.cpp
  event-loop/HandledIoLibevent.cpp
  event-loop/HandledSignalLibevent.cpp
  event-loop/EventLoop.cpp
  event-loop/HandledQuitSignal.cpp
  event-loop/ITimedOut.cpp
  event-loop/Timer.cpp
)

add_library(${APP_LIB_NAME} ${APP_SOURCES})

include_directories(${LIBEVENT_INCLUDE_DIRS} ../src/)
link_directories(${LIBEVENT_LIBRARIES})

add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME} ${LIBEVENT_LDFLAGS})

install (TARGETS ${APP_NAME} DESTINATION bin)

