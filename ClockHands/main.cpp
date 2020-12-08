// Description:
// This problem is known as Clock angle problem where we need to find angle between hands
// of an analog clock at a given time.
#include <gtest/gtest.h>

double handsAngle(int hour, int minutes) {
    double hh = (hour % 12) * 30 + (double) (minutes % 60) / 2;
    double mh = 6 * minutes;
    double diff = hh > mh ? hh - mh : mh - hh;
    return diff > 180 ? 360.0 - diff : diff;
}

TEST(ClockHandsTest, One) {
    ASSERT_EQ(handsAngle(2, 45), 172.5);
}

TEST(ClockHandsTest, Two) {
    ASSERT_EQ(handsAngle(12, 0), 0);
}

TEST(ClockHandsTest, Three) {
    ASSERT_EQ(handsAngle(9, 0), 90);
}