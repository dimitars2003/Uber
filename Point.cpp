#include "Point.h"
#include <cmath>

Point::Point(int x, int y) : x(x), y(y){

}

Point::Point() : x(0), y(0){

}

int Point::getDistance(const Point& other) const{
	return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

int Point::getX() const{
	return x;
}
int Point::getY() const {
	return y;
}
