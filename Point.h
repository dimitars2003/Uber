#pragma once

class Point {
private:
	int x;
	int y;
public:
	Point(int x, int y);
	Point();

	int getDistance(const Point& other) const;

	int getX() const;
	int getY() const;

};