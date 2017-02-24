if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

set(TEST_APP_NAME ${APP_NAME}_tests)
set(TEST_SOURCES
    mocks/IBoardObserverMock.cpp
    mocks/IBoardInputObserverMock.cpp
    mocks/IHardwareStateMock.cpp
    mocks/IHardwareStatePoolMock.cpp
    PlayerPieceTest.cpp
    BitBoardTest.cpp
    BoardTest.cpp
    SquareTest.cpp
    MoveTest.cpp
    SquaresListTest.cpp
    LegalSquaresTest.cpp
    GameLogicTest.cpp
    DispatchedBoardInputEventTest.cpp
    HardwareStatePanicTest.cpp
    HardwareStatePlayerThinkingTest.cpp
    HardwareStatePieceLiftedTest.cpp
    main.cpp
)

include_directories(${CPPUTEST_INCLUDE_DIRS} ../src/)
link_directories(${CPPUTEST_LIBRARIES})

add_executable(${TEST_APP_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_APP_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS})

option(RUN_TESTS "Run the tests" ON)
if(RUN_TESTS)
    add_custom_command(TARGET ${TEST_APP_NAME} COMMAND ./${TEST_APP_NAME} POST_BUILD)
else()
    message(STATUS "Unit tests won't be executed")
endif(RUN_TESTS)
