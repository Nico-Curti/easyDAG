# Test files

add_executable(test_math ${TEST_DIR}/test_math.cpp ${HEADER} ${HPP})
target_link_libraries(test_math ${linked_libs})# ${DAGlib})

add_executable(test_object ${TEST_DIR}/test_object.cpp ${HEADER} ${HPP})
target_link_libraries(test_object ${linked_libs})# ${DAGlib})

# Installation of targets

install(TARGETS test_math             DESTINATION ${OUT_TEST})
install(TARGETS test_object           DESTINATION ${OUT_TEST})
