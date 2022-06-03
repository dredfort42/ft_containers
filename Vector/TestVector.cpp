// compilation:
// c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror  -D STATUS=1 *.cpp -o
// vector.out && ./vector.out
#include <iostream>

#if STATUS
#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

// class with private constructor
class Test
{
private:
	unsigned _id;
	int _int;
	std::string _string;
	Test() {};
//	{ std::cout << "constructor" << std::endl; }

public:

	Test(unsigned id) : _id(id)
	{
//		std::cout << "constructor" << std::endl;
		if (id == 42)
			throw "ERROR DATA";
		if (_id % 2)
			_int = -_id;
		else
			_int = _id;
		_string = std::to_string(_int).append("_tester");
	};

	Test(char chr)
	{
		if (chr == 'e')
			throw "ERROR CONSTRUCTION";
//		std::cout << "constructor" << std::endl;
	}

	~Test()
	{
//		std::cout << "destructor" << std::endl;
	}

	unsigned getId() const
	{
		return _id;
	}

	int getInt() const
	{
		return _int;
	}

	std::string getString() const
	{
		return _string;
	}

	bool operator==(const Test &value) const
	{
		bool result = false;
		if (_id == value.getId()
			&& _int == value.getInt()
			&& !_string.compare(value._string))
			result = true;
		return result;
	}
};

std::ostream &operator<<(std::ostream &out, const Test &value)
{
	out << value.getId() << " | " << value.getInt() << " | "
		<< value.getString();
	return out;
}

int main()
{
//	Test t1((unsigned)1);
//	Test t2((unsigned)1);
//	std::cout << (t1 == t2) << std::endl;

	std::cout << "=-=-=-=-= CONSTRUCT VECTOR =-=-=-=-=" << std::endl;

	ft::vector<int> defaultConstructVectorInt;
	std::cout << "01-[INT] size: " << defaultConstructVectorInt.size() << " | "
			  << "capacity: " << defaultConstructVectorInt.capacity()
			  << std::endl;
	ft::vector<Test> defaultConstructVectorT;
	std::cout << "02-[T] size: " << defaultConstructVectorT.size() << " | "
			  << "capacity: " << defaultConstructVectorT.capacity()
			  << std::endl;

	ft::vector<int> fillConstructVectorInt((size_t) 10, 42);
	std::cout << "03-[INT] size: " << fillConstructVectorInt.size() << " | "
			  << "capacity: " << fillConstructVectorInt.capacity() << std::endl;
	ft::vector<Test> fillConstructVectorT(10, Test((unsigned) 21));
	std::cout << "04-[T] size: " << fillConstructVectorT.size() << " | "
			  << "capacity: " << fillConstructVectorT.capacity() << std::endl;
	try
	{
		ft::vector<Test> fillVectorErrInt(0, Test((unsigned) 42));
	}
	catch (...)
	{
		std::cout << "05-[T] You try construct empty vector!" << std::endl;
	}
	try
	{
		ft::vector<Test> fillVectorErrT(-1, Test((unsigned) 42));
	}
	catch (...)
	{
		std::cout << "06-[T] You try construct negative vector!" << std::endl;
	}

	int testInts[] = {16, 2, 77, 29};
	ft::vector<int> rangeConstructVectorInt
			(testInts, testInts + sizeof(testInts) / sizeof(int));
	std::cout << "07-[Int] size: " << rangeConstructVectorInt.size() << " | "
			  << "capacity: " << rangeConstructVectorInt.capacity()
			  << std::endl;

// 	constructing vectors
	ft::vector<int> first;
	std::cout << "The contents of first are:";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::vector<int> second((size_t) 4, 100);
	std::cout << "The contents of second are:";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::vector<int> third (second.begin(),second.end());
	std::cout << "The contents of third are:";
	for (ft::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::vector<int> fourth (second);
	std::cout << "The contents of fourth are:";
	for (ft::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	// vector assignment
		ft::vector<int> foo ((size_t)3,0);
		ft::vector<int> bar ((size_t)5,0);

		bar = foo;
		foo = ft::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';

//	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//		std::cout << (vector1[2] == vector1[7]) << std::endl;
//
//		for (unsigned i = 0; i < 11; i++) {
//			Test    testData(i + 21);
////			vector.push_back(testData);
//		}

// capacity test
//	std::vector<int> myvector;
//
//	// set some content in the vector:
//	for (int i=0; i<100; i++) myvector.push_back(i);
//
//	std::cout << "size: " << (int) myvector.size() << '\n';
//	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
//	std::cout << "max_size: " << (int) myvector.max_size() << '\n';

// max size test
//	std::cout 	<< "[max_size] " << vector.max_size()
//				<< " | " << vector1.max_size() << std::endl;

// vector::operator[]
	ft::vector<int> myvector(10);   // 10 zero-initialized elements
	ft::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i = 0; i < sz; i++) myvector[i] = i;

	// reverse vector using operator[]:
	for (unsigned i = 0; i < sz / 2; i++)
	{
		int temp;
		temp = myvector[sz - 1 - i];
		myvector[sz - 1 - i] = myvector[i];
		myvector[i] = temp;
	}

	std::cout << "[operator[]] myvector contains:";
	for (unsigned i = 0; i < sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//	std::cout << *myvector.begin() << std::endl;
	// vector::begin/end

		std::cout << "[operator++() preincrement] myvector contains:";
		for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector
		.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	std::cout << "[operator++() postincrement] myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector
			.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << myvector[2] << "\n";
	std::cout << *myvector.rbegin() << "\n";
	std::cout << *(--myvector.rend()) << "\n";

	myvector.resize(5);
	myvector.resize(20,100);
	myvector.resize(25);
	std::cout << "resize myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				<< myvector.size() << " "
				<< myvector.capacity() << " "
				<< (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
				<< std::endl;
	ft::vector<Test> tester;
	std::cout 	<< "T type tester: "
				<< tester.size() << " "
				<< tester.capacity() << " "
				<< (tester.empty() ?  "EMPTY" : "NOT EMPTY") << " "
				<< std::endl;

	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << ' ' << fifth[i];
	std::cout << '\n';
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	fifth.swap(myvector);
	std::cout << "swap fifth and myvector:" << std::endl;
	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << ' ' << fifth[i];
	std::cout << '\n';
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.erase(myvector.begin() + 1);
	std::cout << "erase [1] myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << myvector.size() << " "
				 << myvector.capacity() << " "
				 << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;

	fifth.erase(fifth.begin() + 5, fifth.begin() + 15);
	std::cout << "erase from middle in fifth:";
	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << ' ' << fifth[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << fifth.size() << " "
				 << fifth.capacity() << " "
				 << (fifth.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;

	myvector.clear();
	std::cout << "clear myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << myvector.size() << " "
				 << myvector.capacity() << " "
				 << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;

	first.clear();
	second.clear();
	third.clear();
	third.erase(third.begin(), third.end());
	first.assign ((size_t)7,100);
	std::cout << "assign first:";
	for (unsigned i = 0; i < first.size(); i++)
		std::cout << ' ' << first[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << first.size() << " "
				 << first.capacity() << " "
				 << (first.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;
	int myints1[] = {1776,7,4};
	third.assign(myints1,myints1 + 3);
	std::cout << "assign third:";
	for (unsigned i = 0; i < third.size(); i++)
		std::cout << ' ' << third[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << third.size() << " "
				 << third.capacity() << " "
				 << (third.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;

	myvector.assign(third.begin(), third.end());
	for (int i = 0; i <= 21; i++)
		myvector.push_back(42 - i);
	std::cout << "push_back myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << myvector.size() << " "
				 << myvector.capacity() << " "
				 << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;

	for (int i = 21; i; i--)
		myvector.pop_back();
	std::cout << "pop_back myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout 	<< "INT type tester: "
				 << myvector.size() << " "
				 << myvector.capacity() << " "
				 << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
				 << std::endl;
}
