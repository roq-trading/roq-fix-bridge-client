set(TARGET_NAME ${PROJECT_NAME}-test)

set(SOURCES fix_new_order_single.cpp main.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(
  ${TARGET_NAME} PRIVATE roq-fix-bridge::roq-fix-bridge-fix roq-fix::roq-fix roq-client::roq-client
                         roq-logging::roq-logging Catch2::Catch2 ${RT_LIBRARIES})

set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
