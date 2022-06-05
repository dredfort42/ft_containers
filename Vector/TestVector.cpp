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

	Test()
	{};
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
	std::cout << "[01] size: " << defaultConstructVectorInt.size() << " | "
			  << "capacity: " << defaultConstructVectorInt.capacity()
			  << std::endl;
	ft::vector<Test> defaultConstructVectorT;
	std::cout << "[02] size: " << defaultConstructVectorT.size() << " | "
			  << "capacity: " << defaultConstructVectorT.capacity()
			  << std::endl;

	ft::vector<int> fillConstructVectorInt(10, 42);
	std::cout << "[03] size: " << fillConstructVectorInt.size() << " | "
			  << "capacity: " << fillConstructVectorInt.capacity() << std::endl;
	ft::vector<Test> fillConstructVectorT(10, Test((unsigned) 21));
	std::cout << "[04] size: " << fillConstructVectorT.size() << " | "
			  << "capacity: " << fillConstructVectorT.capacity() << std::endl;
	try
	{
		ft::vector<Test> fillVectorErrInt(0, Test((unsigned) 42));
	}
	catch (...)
	{
		std::cout << "[05] You try construct empty vector!" << std::endl;
	}
	try
	{
		ft::vector<Test> fillVectorErrT(-1, Test((unsigned) 42));
	}
	catch (...)
	{
		std::cout << "[06] You try construct negative vector!" << std::endl;
	}

	int testInts[] = {16, 2, 77, 29};
	ft::vector<int> rangeConstructVectorInt
			(testInts, testInts + sizeof(testInts) / sizeof(int));
	std::cout << "[07] size: " << rangeConstructVectorInt.size() << " | "
			  << "capacity: " << rangeConstructVectorInt.capacity()
			  << std::endl;

// 	constructing vectors
	ft::vector<int> first;
	std::cout << "[08] The contents of first are:";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::vector<int> second(4, 100);
	std::cout << "[09] The contents of second are:";
	for (ft::vector<int>::iterator it = second.begin();
		 it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::vector<int> third(second.begin(), second.end());
	std::cout << "[10] The contents of third are:";
	for (ft::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::vector<int> fourth(second);
	std::cout << "[11] The contents of fourth are:";
	for (ft::vector<int>::iterator it = fourth.begin();
		 it != fourth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	ft::vector<int> foo( 3, 0);
	ft::vector<int> bar( 5, 0);

	bar = foo;
	foo = ft::vector<int>();

	std::cout << "[12] Size of foo: " << int(foo.size()) << '\n';
	std::cout << "[13] Size of bar: " << int(bar.size()) << '\n';

	int myints[] = {16, 2, 77, 29};
	ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	std::cout << "[14] The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

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

	std::cout << "[15] [operator[]] myvector contains:";
	for (unsigned i = 0; i < sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	std::cout << "[16] [operator++() preincrement] myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector
			.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "[17] [operator++() postincrement] myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector
			.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "[18] " << myvector[2] << "\n";
	std::cout << "[19] " << *myvector.rbegin() << "\n";
	std::cout << "[20] " << *(--myvector.rend()) << "\n";

	myvector.resize(5);
	myvector.resize(20, 100);
	myvector.resize(25);
	std::cout << "[21] resize myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "[22] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;
	ft::vector<Test> tester;
	std::cout << "[23] "
			  << tester.size() << " "
			  << tester.capacity() << " "
			  << (tester.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl << "[24] ";

	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << fifth[i];
	std::cout << '\n' << "[25] ";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << myvector[i];
	std::cout << '\n';
	fifth.swap(myvector);
	std::cout << "[26] swap fifth and myvector:" << std::endl << "[27] ";
	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << fifth[i];
	std::cout << '\n' << "[28] ";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << myvector[i];
	std::cout << '\n';

	myvector.erase(myvector.begin() + 1);
	std::cout << "[29] erase [1] myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "[30] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	fifth.erase(fifth.begin() + 5, fifth.begin() + 15);
	std::cout << "[31] erase from middle in fifth:";
	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << ' ' << fifth[i];
	std::cout << '\n';
	std::cout << "[32] "
			  << fifth.size() << " "
			  << fifth.capacity() << " "
			  << (fifth.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	myvector.clear();
	std::cout << "[33] clear myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << myvector[i];
	std::cout << '\n';
	std::cout << "[34] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	first.clear();
	second.clear();
	third.clear();
	third.erase(third.begin(), third.end());
	first.assign(7, 100);
	std::cout << "[35] assign first:";
	for (unsigned i = 0; i < first.size(); i++)
		std::cout << first[i];
	std::cout << '\n';
	std::cout << "[36] "
			  << first.size() << " "
			  << first.capacity() << " "
			  << (first.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;
	int myints1[] = {1776, 7, 4};
	third.assign(myints1, myints1 + 3);
	std::cout << "[37] assign third:";
	for (unsigned i = 0; i < third.size(); i++)
		std::cout << third[i];
	std::cout << '\n';
	std::cout << "[38] "
			  << third.size() << " "
			  << third.capacity() << " "
			  << (third.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	myvector.assign(third.begin(), third.end());
	for (int i = 0; i <= 21; i++)
		myvector.push_back(42 - i);
	std::cout << "[39] push_back myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << myvector[i];
	std::cout << '\n';
	std::cout << "[40] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	for (int i = 21; i; i--)
		myvector.pop_back();
	std::cout << "[41] pop_back myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "[42] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	myvector.insert(myvector.begin() + 4, 21);
	std::cout << "[43] insert single element myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "[44] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	myvector.insert(myvector.begin() + 2, 6, 808);
	std::cout << "[45] insert fill myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "[46] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	myvector.insert(myvector.begin() + 4, fifth.begin() + 2, fifth.end() - 2);
	std::cout << "[47] insert range myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "[48] "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;

	std::cout <<"[49] "<< (myvector == fifth ? "equal" : "not equal") << std::endl;
	std::cout <<"[50] "<< (myvector == myvector ? "equal" : "not equal") <<
	std::endl;
	std::cout <<"[51] "<< (myvector != fifth ? "not equal" : "equal") <<
	std::endl;
	std::cout <<"[52] "<< (myvector != myvector ? "not equal" : "equal") <<
	std::endl;
	std::cout <<"[53] "<< (myvector < fifth ? "1" : "0") << std::endl;
	std::cout <<"[54] "<< (fifth < myvector ? "1" : "0") << std::endl;
	std::cout <<"[55] "<< (myvector < myvector ? "1" : "0") << std::endl;
	std::cout <<"[56] "<< (myvector <= fifth ? "1" : "0") << std::endl;
	std::cout <<"[57] "<< (fifth <= myvector ? "1" : "0") << std::endl;
	std::cout <<"[58] "<< (myvector <= myvector ? "1" : "0") << std::endl;
	std::cout <<"[59] "<< (myvector > fifth ? "1" : "0") << std::endl;
	std::cout <<"[60] "<< (fifth > myvector ? "1" : "0") << std::endl;
	std::cout <<"[61] "<< (myvector > myvector ? "1" : "0") << std::endl;
	std::cout <<"[62] "<< (myvector >= fifth ? "1" : "0") << std::endl;
	std::cout <<"[63] "<< (fifth >= myvector ? "1" : "0") << std::endl;
	std::cout <<"[64] "<< (myvector >= myvector ? "1" : "0") << std::endl;

	std::cout << "[65] myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << " >> "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;
	std::cout << "[66] fifth:";
	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << ' ' << fifth[i];
	std::cout << " >> "
			  << fifth.size() << " "
			  << fifth.capacity() << " "
			  << (fifth.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;
	myvector.swap(fifth);
	std::cout << "[67] SWAP\n" << "[68] myvector:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << " >> "
			  << myvector.size() << " "
			  << myvector.capacity() << " "
			  << (myvector.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;
	std::cout << "[69] fifth:";
	for (unsigned i = 0; i < fifth.size(); i++)
		std::cout << ' ' << fifth[i];
	std::cout << " >> "
			  << fifth.size() << " "
			  << fifth.capacity() << " "
			  << (fifth.empty() ? "EMPTY" : "NOT EMPTY") << " "
			  << std::endl;
}
