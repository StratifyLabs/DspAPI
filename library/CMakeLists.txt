
set(LIBRARIES VarAPI FsAPI ChronoAPI)
if(SOS_IS_LINK)
	list(APPEND LIBRARIES mbedtls)
endif()

api_add_api_library(${PROJECT_NAME} "${LIBRARIES}")

