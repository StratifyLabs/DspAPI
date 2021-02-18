

if(NOT DEFINED API_IS_SDK)
	include(API)
	sos_sdk_include_target(DspAPI "${API_CONFIG_LIST}")
endif()
