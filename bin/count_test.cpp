#include "count.h"
#include "gtest/gtest.h"
using namespace std;

TEST(MessageTest, OutputTimeTest) {
  time_t current_time = time(nullptr);
  char* date_time = ctime(&current_time);
  date_time[strcspn(date_time, "\n")] = '\0';
  string expected = "Miles: " + string(date_time) + " #5";
  EXPECT_EQ(expected, output_time(current_time, 5));
}

TEST(MessageTest, OutputTerminationTest) {
  time_t current_time = time(nullptr);
  char* date_time = ctime(&current_time);
  date_time[strcspn(date_time, "\n")] = '\0';
  string expected = "Miles: " + string(date_time) + " Received SIGTERM, exiting";
  EXPECT_EQ(expected, output_termination(current_time));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
