
set(exp_lists
	load
	create
	array
	)

option(ENABLE_VALGRIND "Enable valgrind memory check for the test" OFF)

if(ENABLE_VALGRIND)
	find_program(MEMORYCHECK_COMMAND valgrind)
	if ("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND")
		message(WARNING "Valgrind couldn't be found.")
		unset(MEMORYCHECK_COMMAND)
	else()
		set(MEMORYCHECK_COMMAND_OPTIONS --trace-children=yes --leak-check=full --error-exitcode=1 --suppressions=${CMAKE_CURRENT_SOURCE_DIR}/../valgrind.supp)
	endif()
endif()

foreach(exp ${exp_lists})
	add_executable("${exp}" "${exp}.cpp")
	target_link_libraries("${exp}" "${DATAFORMAT_LIB}")
endforeach()



