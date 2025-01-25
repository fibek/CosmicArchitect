find_package(GTest REQUIRED)

add_executable(milestone_tests
    MilestoneTests.cpp
)

target_link_libraries(milestone_tests PRIVATE
    cosmic_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(milestone_tests) 