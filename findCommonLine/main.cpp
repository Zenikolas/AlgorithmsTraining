// Description:
// Given a two-dimentional graph with points on it, find a line which passes the most
// number of points
#include <gtest/gtest.h>

const double epsilon = 0.000000001;

struct Point {
    double x;
    double y;
};

bool operator<(const Point& lhs, const Point& rhs) {
    return lhs.x - rhs.x < -epsilon || lhs.y - rhs.y < -epsilon;
}

struct Line {
    bool isVertical;
    double k;
    double b;

    Line() = default;

    Line(const Line&) = default;

    Line& operator=(const Line&) = default;

    Line(double _k, double _b) : isVertical(false), k(_k), b(_b) {}

    Line(double _b) : isVertical(true), k(), b(_b) {}

    void print(std::ostream& os) {
        if (isVertical) {
            os << "(x = " << b << ")";
        } else {
            os << "(k = " << k << ", b = " << b << ")";
        }
    }
};


bool operator<(const Line& lhs, const Line& rhs) {
    return lhs.b - rhs.b < -epsilon
           || (lhs.isVertical && !rhs.isVertical)
           || !(!lhs.isVertical && rhs.isVertical)
           || lhs.k - rhs.k < -epsilon;
}


Line createLine(const Point& lhs, const Point& rhs) {
    if (abs(lhs.x - rhs.x) < epsilon) {
        return Line(lhs.x);
    }

    double k = (lhs.y - rhs.y) / (lhs.x - rhs.x);
    double b = lhs.y - k * lhs.x;
    return Line(k, b);
}

void insertToMap(std::map<Line, std::set<Point>>& map, const Point& lhs, const Point&
rhs) {
    auto[iter, inserted] = map.emplace(createLine(lhs, rhs),
                                       std::set<Point>());
    if (inserted) {
        iter->second.emplace(lhs);
    }
    iter->second.emplace(rhs);
}


Line findCommonLine(const std::vector<Point>& points) {
    std::map<Line, std::set<Point>> linePoints;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            if (abs(points[i].x - points[j].x) < epsilon &&
                abs(points[i].y - points[j].y) < epsilon) {
                continue;
            }

            insertToMap(linePoints, points[i], points[j]);
        }
    }

    const Line* retLine = nullptr;
    size_t maxPoints = 0;
    for (auto& linePoint : linePoints) {
        if (maxPoints < linePoint.second.size()) {
            maxPoints = linePoint.second.size();
            retLine = &linePoint.first;
        }
    }

    return *retLine;
}

TEST(ClockHandsTest, One) {
    std::vector<Point> points = {{1,  1},
                                 {3,  3},
                                 {5,  5},
                                 {1,  2},
                                 {-9, 89},
                                 {1,  4},
                                 {1,  9},
                                 {1,  7},
                                 {1,  -1},
    };

    auto line = findCommonLine(points);
    std::stringstream sstream;

    line.print(sstream);
    ASSERT_TRUE(line.isVertical);
    ASSERT_EQ(line.b, 1);
}
