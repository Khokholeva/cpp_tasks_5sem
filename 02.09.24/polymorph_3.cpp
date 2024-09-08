#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Expr {
public:
	Expr() {};
	virtual void print() = 0;
	virtual double eval(double x) = 0;
	virtual Expr* der() = 0;
	virtual Expr* clone() = 0;
	virtual ~Expr() {}
};

class Constant : public Expr {
	double value;
public:
	Constant(double v) : value(v) {}
	void print() { cout << value; };
	double eval(double x) { return value; }
	Expr* der() {
		Expr* res = new Constant(0);
		return res;
	}
	Expr* clone() {
		Expr* res = new Constant(value);
		return res;
	}
};

class Variable : public Expr {
public:
	Variable() {}
	void print() { cout << "x"; };
	double eval(double x) { return x; }
	Expr* der() {
		Expr* res = new Constant(1);
		return res;
	}
	Expr* clone() {
		Expr* res = new Variable();
		return res;
	}
};

class Sum : public Expr {
	Expr* left, * right;
public:
	Sum(Expr* l, Expr* r): left(l), right(r){}
	void print() {
		cout << "(";
		left->print();
		cout << " + ";
		right->print();
		cout << ")";
	};
	double eval(double x) {
		double l = left->eval(x);
		double r = right->eval(x);
		return l + r;
	}
	Expr* der() {
		Expr* res = new Sum(left->der(), right->der());
		return res;
	}
	Expr* clone() {
		Expr* res = new Sum(left->clone(), right->clone());
		return res;
	}
};

class Mult: public Expr {
	Expr* left, * right;
public:
	Mult(Expr* l, Expr* r): left(l), right(r) {}
	void print() { 
		left->print();
		cout << " * ";
		right->print();
	};
	double eval(double x) { 
		double l = left->eval(x);
		double r = right->eval(x);
		return l * r;
	}
	Expr* der() {
		Expr* res = new Sum(new Mult(left->der(), right->clone()), new Mult(left->clone(), right->der()));
		return res;
	}
	Expr* clone() {
		Expr* res = new Mult(left->clone(), right->clone());
		return res;
	}
};

class Sin : public Expr {
	Expr* exp;
public:
	Sin(Expr* e) : exp(e) {}
	void print() {
		cout << "sin(";
		exp->print();
		cout << ")";
	};
	double eval(double x) {
		double r = exp->eval(x);
		return sin(r);
	}
	Expr* der();
	Expr* clone() {

		Expr* res = new Sin(exp->clone());
		return res;
	}
};

class Cos : public Expr {
	Expr* exp;
public:
	Cos(Expr* e) : exp(e) {}
	void print() {
		cout << "cos(";
		exp->print();
		cout << ")";
	};
	double eval(double x) { 
		double r = exp->eval(x);
		return cos(r); 
	}
	Expr* der() {
		Expr* res = new Mult(new Mult(new Constant(-1), new Sin(exp->clone())), exp->der());
		return res;
	}
	Expr* clone() {
		Expr* res = new Cos(exp->clone());
		return res;
	}
};

Expr* Sin::der() {
	Expr* res = new Mult(new Cos(exp->clone()), exp->der());
	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Expr* s1 = new Sum(new Constant(3), new Variable());
	Expr* s2 = new Sum(new Constant(7), new Sin(new Variable()));
	Expr* s3 = new Mult(s1, s2);
	s3->print();
	cout << endl;
	cout << s3->eval(1);
	
	return EXIT_SUCCESS;
}
