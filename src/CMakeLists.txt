add_executable(${PROJECT_NAME} main.cc)

add_library(Integrity
	IntegrityCore.cc
	status_out.cc
	
	WriteMode.cc
	ReadMode.cc
	
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
			${PROJECT_SOURCE_DIR}/include/IntegrityCore.h

			${PROJECT_SOURCE_DIR}/include/models/AcceptedFSType.h
			${PROJECT_SOURCE_DIR}/include/models/DirectoryContent.h
			${PROJECT_SOURCE_DIR}/include/models/FileInfo.h
			${PROJECT_SOURCE_DIR}/include/models/ModeContext.h
			
			${PROJECT_SOURCE_DIR}/include/modes/Mode.h
			${PROJECT_SOURCE_DIR}/include/modes/WriteMode.h
			${PROJECT_SOURCE_DIR}/include/modes/ReadMode.h

)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Integrity PUBLIC OpenSSL::Crypto nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE Integrity)
