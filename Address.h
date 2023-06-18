#pragma once
#include "Point.h"
#include "MyString.h"

class Address {
private:
	
	MyString name;
	Point coordinates;
	MyString additionalInfo;


public:

	Address();
	Address(MyString name, Point coordinates, MyString additionalInfo);
	Address(MyString name, Point coordinates);

	void setName(const MyString& name);
	void setAdditionalInfo(const MyString& additionalInfo);
	void setPoint(const Point& point);
	
	const Point& getPoint() const;
	const MyString& getName() const;
	const MyString& getAdditionalInfo() const;
};