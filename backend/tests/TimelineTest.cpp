#include <gtest/gtest.h>
#include "../src/Timeline.hpp"
#include "../src/UniverseParameters.hpp"

class TimelineTest : public ::testing::Test {
protected:
    Timeline timeline;
    UniverseParameters defaultParams{0.3, 0.7, 70.0, 1e-9, -1.0};
};

TEST_F(TimelineTest, EmptyTimelineHasNoMilestones) {
    EXPECT_TRUE(timeline.getMilestones().empty());
}

TEST_F(TimelineTest, CanAddMilestone) {
    auto milestone = createMilestone(MilestoneType::BigBang, defaultParams);
    timeline.addMilestone(std::move(milestone));
    
    EXPECT_EQ(timeline.getMilestones().size(), 1);
    EXPECT_EQ(timeline.getMilestones()[0]->getType(), MilestoneType::BigBang);
}

TEST_F(TimelineTest, ClearRemovesAllMilestones) {
    auto milestone1 = createMilestone(MilestoneType::BigBang, defaultParams);
    auto milestone2 = createMilestone(MilestoneType::Inflation, defaultParams);
    
    timeline.addMilestone(std::move(milestone1));
    timeline.addMilestone(std::move(milestone2));
    EXPECT_EQ(timeline.getMilestones().size(), 2);
    
    timeline.clear();
    EXPECT_TRUE(timeline.getMilestones().empty());
}

TEST_F(TimelineTest, CanExportToJson) {
    auto milestone = createMilestone(MilestoneType::BigBang, defaultParams);
    timeline.addMilestone(std::move(milestone));
    
    nlohmann::json j = timeline.toJson();
    EXPECT_FALSE(j.empty());
    EXPECT_TRUE(j.contains("milestones"));
    EXPECT_EQ(j["milestones"].size(), 1);
} 