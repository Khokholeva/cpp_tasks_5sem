#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class T>
struct Complex {
	T r, i;
	
	Complex(T a = 0, T b = 0): r(a), i(b) {}
	bool operator==(Complex a) {
		return r == a.r and i == a.i;
	}
	bool operator!=(Complex a) {
		return r != a.r or i != a.i;
	}
	Complex operator+(Complex a) {
		return { r + a.r, i + a.i };
	}
	Complex operator-(Complex a) {
		return { r - a.r, i - a.i };
	}
	Complex operator*(Complex a) {
		return { r * a.r - i * a.i, r * a.i + i * a.r };
	}
	Complex operator/(Complex a) {
		return { (r * a.r + i * a.i) / (a.r * a.r + a.i * a.i), (i * a.r - r * a.i) / (a.r * a.r + a.i * a.i) };
	}

};

template <class T>
std::ostream& operator << (std::ostream& os, const Complex<T>& c)
{
	if (c.i == 0) return os << c.r;
	if (c.r == 0) return os << c.i << "i";
	if (c.i < 0) return os << c.r << " - " << c.i * -1 << "i";
	return os << c.r << " + " << c.i << "i";
}

template <class T>
std::istream& operator >> (std::istream& in, Complex<T>& c)
{
	return in >> c.r >> c.i;
}

template <class T>
struct Fraction {
	T n, d;

	Fraction(T a = 0, T b = 1) {
		n = a;
		d = b;
		T c = a % b;
		while (c != 0) {
			a = b;
			b = c;
			c = a % b;
		}
		
		n /= b;
		d /= b;
		if (d < 0) {
			n *= -1;
			d *= -1;
		}
	}
	bool operator==(Fraction a) {
		return n * a.d == d * a.n;
	}
	bool operator!=(Fraction a) {
		return n * a.d != d * a.n;
	}
	Fraction operator+(Fraction a) {
		return { n * a.d + d * a.n, d * a.d };
	}
	Fraction operator-(Fraction a) {
		return { n * a.d - d * a.n, d * a.d };
	}
	Fraction operator*(Fraction a) {
		return { n * a.n, d * a.d };
	}
	Fraction operator/(Fraction a) {
		return { n * a.d, d * a.n };
	}

};

template <class T>
std::ostream& operator << (std::ostream& os, const Fraction<T>& f)
{
	return os << f.n << "/" << f.d;
}

template <class T>
std::istream& operator >> (std::istream& in, Fraction<T>& f)
{
	T a, b;
	in >> a >> b;
	f = { a, b };
	return in;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//check_all_ts();

	
	Complex<double> x, y;
	cin >> x >> y;
	Complex<double> z = x / y;
	cout << "z:= x / y = " << z << endl;
	Complex<double> w = y * z;
	cout << "w:= y * z = " << w << endl;
	

	Fraction<int> a, b;
	cin >> a >> b;
	cout << a << " + " << b << " = " << a + b;

}
