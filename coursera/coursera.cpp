#include "pch.h"
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

class Rational {
public:

	Rational();
	Rational(int numerator, int denominator) {
	}

	int Numerator() const {  //числитель
	}

	int Denominator() const { // знаменатель 
	}
};

void empty() {
	Rational a;
	AssertEqual(a.Numerator(), 0, "empty 1");
	AssertEqual(a.Denominator(), 1, "empty 1");
}

void fraction_reduction() {

	Rational a(2, 3);
	AssertEqual(a.Numerator(), 2, "fraction_reduction 1");
	AssertEqual(a.Denominator(), 3, "fraction_reduction 2");

	Rational b(6, 18);
	AssertEqual(b.Numerator(), 1, "fraction_reduction 3");
	AssertEqual(b.Denominator(), 3, "fraction_reduction 4");
}

void negative_fraction() {
	Rational a(-3, 2);
	AssertEqual(a.Numerator(), -3, "negative_fraction 1");
	AssertEqual(a.Denominator(), 2, "negative_fraction 2");

	Rational b(3, -2);
	AssertEqual(b.Numerator(), -3, "negative_fraction 3");
	AssertEqual(b.Denominator(), 2, "negative_fraction 4");

	Rational c(9, -36);
	AssertEqual(c.Numerator(), -1, "negative_fraction 5");
	AssertEqual(c.Denominator(), 4, "negative_fraction 6");
}

void the_numerator_is_0() {
	Rational a(0, 13);
	AssertEqual(a.Numerator(), 0, "the_numerator_is_0 1");
	AssertEqual(a.Denominator(), 1, "the_numerator_is_0 2");

	Rational c(0, -23);
	AssertEqual(c.Numerator(), 0, "the_numerator_is_0 3");
	AssertEqual(c.Denominator(), 1, "the_numerator_is_0 4");
}

void positive_fraction() {

	Rational a(-5, -6);
	AssertEqual(a.Numerator(), 5, "positive_fraction 1");
	AssertEqual(a.Denominator(), 6, "positive_fraction 2");

	Rational c(-10, -100);
	AssertEqual(c.Numerator(), 1, "positive_fraction 3");
	AssertEqual(c.Denominator(), 10, "positive_fraction 4");
}

void AllTests(TestRunner& test) {
	empty();
	fraction_reduction();
	negative_fraction();
	the_numerator_is_0();
	positive_fraction();
}

int main() {
	TestRunner runner;
	AllTests(runner);
	return 0;
}