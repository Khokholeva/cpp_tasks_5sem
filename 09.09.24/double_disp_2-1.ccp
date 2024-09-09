#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
using namespace std;

struct Number;
struct String;
struct Array;
struct AssocArr;

struct Base
{
	virtual ~Base() {}
	virtual bool operator<(const Base&) const = 0;
	virtual bool operator<(const Number&) const = 0;
	virtual bool operator<(const String&) const = 0;
	virtual bool operator<(const Array&) const = 0;
	virtual bool operator<(const AssocArr&) const = 0;
	virtual bool operator>(const Base&) const = 0;
	virtual bool operator>(const Number&) const = 0;
	virtual bool operator>(const String&) const = 0;
	virtual bool operator>(const Array&) const = 0;
	virtual bool operator>(const AssocArr&) const = 0;
};

struct Element {
	Base* data;
	~Element() {
		delete data;
	}
	bool operator<(const Element& x) const {
		return *data < *(x.data);
	}
	bool operator>(const Element& x) const {
		return *data > *(x.data);
	}
};

struct Number : Base
{
	int n;
	bool operator<(const Base&) const;
	bool operator<(const Number&) const;
	bool operator<(const String&) const;
	bool operator<(const Array&) const;
	bool operator<(const AssocArr&) const;
	bool operator>(const Base&) const;
	bool operator>(const Number&) const;
	bool operator>(const String&) const;
	bool operator>(const Array&) const;
	bool operator>(const AssocArr&) const;
};

struct String : Base
{
	string s;
	bool operator<(const Base&) const;
	bool operator<(const Number&) const;
	bool operator<(const String&) const;
	bool operator<(const Array&) const;
	bool operator<(const AssocArr&) const;
	bool operator>(const Base&) const;
	bool operator>(const Number&) const;
	bool operator>(const String&) const;
	bool operator>(const Array&) const;
	bool operator>(const AssocArr&) const;
};

struct Array : Base
{
	vector<Element> ar;
	
	bool operator<(const Base&) const;
	bool operator<(const Number&) const;
	bool operator<(const String&) const;
	bool operator<(const Array&) const;
	bool operator<(const AssocArr&) const;
	bool operator>(const Base&) const;
	bool operator>(const Number&) const;
	bool operator>(const String&) const;
	bool operator>(const Array&) const;
	bool operator>(const AssocArr&) const;
};

struct AssocArr : Base
{
	map<string, Element> as_ar;

	bool operator<(const Base&) const;
	bool operator<(const Number&) const;
	bool operator<(const String&) const;
	bool operator<(const Array&) const;
	bool operator<(const AssocArr&) const;
	bool operator>(const Base&) const;
	bool operator>(const Number&) const;
	bool operator>(const String&) const;
	bool operator>(const Array&) const;
	bool operator>(const AssocArr&) const;
};


//Операторы Number
bool Number::operator<(const Base& x) const {
	return x > *this;
}
bool Number::operator<(const Number& x) const {
	return n < x.n;
}
bool Number::operator<(const String& x) const {
	return 1;
}
bool Number::operator<(const Array& x) const {
	return 1;
}
bool Number::operator<(const AssocArr& x) const {
	return 1;
}

bool Number::operator>(const Base& x) const {
	return x < *this;
}
bool Number::operator>(const Number& x) const {
	return n > x.n;
}
bool Number::operator>(const String& x) const {
	return 0;
}
bool Number::operator>(const Array& x) const {
	return 0;
}
bool Number::operator>(const AssocArr& x) const {
	return 0;
}

//Операторы String
bool String::operator<(const Base& x) const {
	return x > *this;
}
bool String::operator<(const Number& x) const {
	return 0;
}
bool String::operator<(const String& x) const {
	return s < x.s;
}
bool String::operator<(const Array& x) const {
	return 1;
}
bool String::operator<(const AssocArr& x) const {
	return 1;
}

bool String::operator>(const Base& x) const {
	return x < *this;
}
bool String::operator>(const Number& x) const {
	return 1;
}
bool String::operator>(const String& x) const {
	return s > x.s;
}
bool String::operator>(const Array& x) const {
	return 0;
}
bool String::operator>(const AssocArr& x) const {
	return 0;
}

//Операторы Array
bool Array::operator<(const Base& x) const {
	return x > *this;
}
bool Array::operator<(const Number& x) const {
	return 0;
}
bool Array::operator<(const String& x) const {
	return 0;
}
bool Array::operator<(const Array& x) const {
	return ar < x.ar;
}
bool Array::operator<(const AssocArr& x) const {
	return 1;
}

bool Array::operator>(const Base& x) const {
	return x < *this;
}
bool Array::operator>(const Number& x) const {
	return 1;
}
bool Array::operator>(const String& x) const {
	return 1;
}
bool Array::operator>(const Array& x) const {
	return ar > x.ar;
}
bool Array::operator>(const AssocArr& x) const {
	return 0;
}

//Операторы AssocArr
bool AssocArr::operator<(const Base& x) const {
	return x > *this;
}
bool AssocArr::operator<(const Number& x) const {
	return 0;
}
bool AssocArr::operator<(const String& x) const {
	return 0;
}
bool AssocArr::operator<(const Array& x) const {
	return 0;
}
bool AssocArr::operator<(const AssocArr& x) const {
	return as_ar < x.as_ar;
}

bool AssocArr::operator>(const Base& x) const {
	return x < *this;
}
bool AssocArr::operator>(const Number& x) const {
	return 1;
}
bool AssocArr::operator>(const String& x) const {
	return 1;
}
bool AssocArr::operator>(const Array& x) const {
	return 1;
}
bool AssocArr::operator>(const AssocArr& x) const {
	return as_ar > x.as_ar;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	return EXIT_SUCCESS;
}
