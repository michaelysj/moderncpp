#include "tester.h"

void f(int n1, int n2, int n3, const int& n4, int n5)
{
	cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << endl;
}

int g(int n1)
{
	return n1;
}

struct Foo {
	void print_sum(int n1, int n2)
	{
		cout << n1 + n2 << endl;
	}
	int data = 10;
};

void test_bind()
{
	cout << "1) argument redordering and pass-by-reference: ";
	int n = 7;
	//(_1 and _2 are from std::placeholders, and represent furture
	// arguments that will be passed to f1)
	auto f1 = bind(f, placeholders::_2, 42, placeholders::_1, cref(n), n);
	n = 10;
	f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
	                // makes a call to f(2, 42, 1, n, 7)
	cout << "2) achieving the same effect using a lambda: ";
	n = 7;
	auto lambda = [ncref = cref(n), n = n](auto a, auto b, auto/*unused*/){
		f(b, 42, a, ncref, n);
	};
	n = 10;
	lambda(1, 2, 1001);

	cout << "3) nested bind subexpressions share the placeholders: ";
	auto f2 = bind(f, placeholders::_3, bind(g, placeholders::_3), placeholders::_3, 4, 5);
	f2(10, 11, 12); // makes a call to f(12, g(12), 12, 4, 5);
	auto f22 = bind(f, placeholders::_3, bind(g, n), placeholders::_3, 4, 5);
	n = 22;
	f22(10, 11, 12); // makes a call to f(12, g(22), 12, 4, 5);
	auto f222 = bind(f, placeholders::_3, bind(g, cref(n)), placeholders::_3, 4, 5);
	n = 222;
	f222(10, 11, 12,666); // makes a call to f(12, g(n), 12, 4, 5);

	cout << "4) bind a RNG with a distribution: ";
	default_random_engine e;
	uniform_int_distribution<> d(0, 10);
	auto rnd = bind(d, e); // a copy of e is sotred in rnd
	for (int n = 0; n < 10; ++n)
	{
		cout << rnd() << ' ';
	}
	cout << endl;

	cout << "5) bind to a pointer to member function: ";
	Foo foo;
	auto f3 = bind(&Foo::print_sum, &foo, 95, placeholders::_1);
	//auto f3 = bind(&Foo::print_sum, 95, placeholders::_1);
	f3(5);

	cout << "6) bind to a mem_fn that is a pointer to member fucntion: ";
	auto ptr_to_print_sum = mem_fn(&Foo::print_sum);
	auto f4 = bind(ptr_to_print_sum, &foo, 95, placeholders::_1);
	f4(5);

	cout << "7) bind to a pointer to data member: ";
	auto f5 = bind(&Foo::data, placeholders::_1);
	cout << f5(foo) << endl;
	cout << "7) bind to a pointer to data member: ";
	auto f55 = bind(&Foo::data, &foo);
	cout << f55() << endl;

	cout << "8) bind to a mem_fn that is a pointer to data member: ";
	auto ptr_to_data = mem_fn(&Foo::data);
	auto f6 = bind(ptr_to_data, placeholders::_1);
	cout << f6(foo) << endl;
	cout << "8) bind to a mem_fn that is a pointer to data member: ";
	auto f66 = bind(ptr_to_data,&foo);
	cout << f66() << endl;

	cout << "9) use smart pointers to call member of the reference objects: ";
	cout << f6(make_shared<Foo>(foo)) << ' '
		<< f6(make_unique<Foo>(foo)) << endl;
}