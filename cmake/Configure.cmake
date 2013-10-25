# Configure.cmake -- Set compiler flags, preprocessor definitions.

# Enforce a reasonably high warning level.
if(MSVC)
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wall -Wextra")
endif()

if(APPLE)
	include(MacOSXVersion)
	macosx_version(product_version)
	if(${product_version} STREQUAL "10.6")
		# On Mac OS 10.6, to work around bugs in libc headers like math.h and inttypes.h, we add following
		# definitions to the command line.
		add_definitions(-U__STRICT_ANSI__ -D__STDC_FORMAT_MACROS)
	endif()
endif()
