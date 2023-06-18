#include "Address.h"

Address::Address() : name(), coordinates(), additionalInfo() {

}
Address::Address(MyString name, Point coordinates, MyString additionalInfo) : name(name), coordinates(coordinates), additionalInfo(additionalInfo){

}
Address::Address(MyString name, Point coordinates) : name(name), coordinates(coordinates), additionalInfo() {

}


void Address::setName(const MyString& name) {
	this->name = name;
}
void Address::setAdditionalInfo(const MyString& additionalInfo) {
	this->additionalInfo = additionalInfo;
}
void Address::setPoint(const Point& point) {
	this->coordinates = point;
}

const Point& Address::getPoint() const {
	return coordinates;
}
const MyString& Address::getName() const {
	return name;
}
const MyString& Address::getAdditionalInfo() const {
	return additionalInfo;
}