add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		main.cc
		status_out.cc
		IntegrityCore.cc
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			${PROJECT_SOURCE_DIR}/include
		FILES
			${PROJECT_SOURCE_DIR}/include/status_out.h
			${PROJECT_SOURCE_DIR}/include/Statuses.h
			${PROJECT_SOURCE_DIR}/include/AcceptedFSType.h
			${PROJECT_SOURCE_DIR}/include/IntegrityCore.h			
)
