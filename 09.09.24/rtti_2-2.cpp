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
};

struct Element {
	Base* data;
	~Element() {
		delete data;
	}
	bool operator<(const Element& x) const;
	bool operator>(const Element& x) const;
};

struct Number : Base
{
	int n;
};

struct String : Base
{
	string s;
};

struct Array : Base
{
	vector<Element> ar;
};

struct AssocArr : Base
{
	map<string, Element> as_ar;
};

bool Element::operator<(const Element& x) const {
	if (typeid(*data) != typeid(*x.data)) {
		return typeid(*data).before(typeid(*x.data));
	}
	if (typeid(*data) == typeid(Number)) {
		return ((Number*)data)->n < ((Number*)x.data)->n;
	}
	else if (typeid(*data) == typeid(String)) {
		return ((String*)data)->s < ((String*)x.data)->s;
	}
	else if (typeid(*data) == typeid(Array)) {
		return ((Array*)data)->ar < ((Array*)x.data)->ar;
	}
	else if (typeid(*data) == typeid(AssocArr)) {
		return ((AssocArr*)data)->as_ar < ((AssocArr*)x.data)->as_ar;
	}
}
bool Element::operator>(const Element& x) const {
	return x < *this;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	return EXIT_SUCCESS;
}
