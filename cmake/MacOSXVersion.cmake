# MacOSXVersion.cmake -- Determine the version of Mac OS X.

function(macosx_version version)
	set(${version} "macosx_version-NOTFOUND" PARENT_SCOPE)
	if(APPLE)
		execute_process(COMMAND /usr/bin/sw_vers OUTPUT_VARIABLE _out OUTPUT_STRIP_TRAILING_WHITESPACE)
		string(REGEX MATCH "ProductVersion:.*10[.]([0-9]+)[.][0-9]+" _out ${_out})
		set(${version} "10.${CMAKE_MATCH_1}" PARENT_SCOPE)
	endif()
endfunction()
