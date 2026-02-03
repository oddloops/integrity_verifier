set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest inclusion
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/56efe3983185e3f37e43415d1afa97e3860f187f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(RecordModeTest)

target_sources(RecordModeTest
	PRIVATE
		RecordModeTest.cc
		${PROJECT_SOURCE_DIR}/src/RecordMode.cc
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			${PROJECT_SOURCE_DIR}/include
		FILES
			${PROJECT_SOURCE_DIR}/include/RecordMode.h
)

target_link_libraries(
  RecordModeTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(RecordModeTest)
