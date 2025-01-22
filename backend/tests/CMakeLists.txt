find_package(GTest REQUIRED)

add_executable(milestone_tests
    MilestoneTests.cpp
)

target_link_libraries(milestone_tests
    PRIVATE
    GTest::GTest
    GTest::Main
    cosmic_core
)

include(GoogleTest)
gtest_discover_tests(milestone_tests) 