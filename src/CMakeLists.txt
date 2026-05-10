add_executable(${PROJECT_NAME} main.cc)

add_library(Integrity
	IntegrityCore.cc
	status_out.cc
	WriteMode.cc
	DirectoryContent.cc
	FileInfo.cc
)

target_sources(Integrity
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			${PROJECT_SOURCE_DIR}/include
		FILES
			${PROJECT_SOURCE_DIR}/include/status_out.h
			${PROJECT_SOURCE_DIR}/include/Statuses.h
			${PROJECT_SOURCE_DIR}/include/AcceptedFSType.h
			${PROJECT_SOURCE_DIR}/include/IntegrityCore.h
			${PROJECT_SOURCE_DIR}/include/DirectoryContent.h
			${PROJECT_SOURCE_DIR}/include/FileInfo.h
)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Integrity PUBLIC OpenSSL::Crypto nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE Integrity)
