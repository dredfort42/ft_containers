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

// class without public constructor
class Test {
	private:
		unsigned 		_id;
		int     		_int;
		std::string		_string;
		Test() {};

	public:
		Test(unsigned id): _id(id) {
			if (id == 42)
				throw "ERROR DATA";
			if (_id % 2)
				_int = -_id;
			else
				_int = _id;
			_string = std::to_string(_int).append("_tester");
		};

		Test(char chr) {
			if (chr == 'e')
				throw "ERROR CONSTRUCTION";
		}

		~Test() {
//			(void)_id;
		};

		unsigned 	getId() const {
			return _id;
		}

		int			getInt() const {
			return _int;
		}

		std::string	getString() const {
			return _string;
		}

		bool	operator== (const Test &value) const {
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
	out << value.getId() << " | " << value.getInt() << " | " << value.getString();
	return out;
}

int main() {
//	Test t1((unsigned)1);
//	Test t2((unsigned)1);
//	std::cout << (t1 == t2) << std::endl;

	std::cout << "=-=-=-=-= CONSTRUCT VECTOR =-=-=-=-=" << std::endl;

	ft::vector<int> defaultConstructVectorInt;
	std::cout 	<< "01-[INT] size: " << defaultConstructVectorInt.size() << ""
																			  " | "
		<< "capacity: " << defaultConstructVectorInt.capacity() << std::endl;
	ft::vector<Test> defaultConstructVectorT;
	std::cout 	<< "02-[T] size: " << defaultConstructVectorT.size() << " | "
		<< "capacity: " << defaultConstructVectorT.capacity() << std::endl;

	ft::vector<int> fillConstructVectorInt((size_t)10, 42);
	std::cout 	<< "03-[INT] size: " << fillConstructVectorInt.size() << " | "
		<< "capacity: " << fillConstructVectorInt.capacity() << std::endl;
	ft::vector<Test> fillConstructVectorT(10, Test((unsigned)21));
	std::cout 	<< "04-[T] size: " << fillConstructVectorT.size() << " | "
		<< "capacity: " << fillConstructVectorT.capacity() << std::endl;
	try
	{
			ft::vector<Test> fillVectorErrInt(0, Test((unsigned)42));
	}
	catch (...)
	{
		std::cout 	<< "05-[T] You try construct empty vector!" << std::endl;
	}
	try
	{
		ft::vector<Test> fillVectorErrT(-1, Test((unsigned)42));
	}
	catch (...)
	{
		std::cout << "06-[T] You try construct negative vector!" << std::endl;
	}

	int testInts[] = {16,2,77,29};
	ft::vector<int> rangeConstructVectorT
	(testInts,testInts+ sizeof(testInts) / sizeof(int) );
	std::cout 	<< "07-[T] size: " << rangeConstructVectorT.size() << " | "
		<< "capacity: " << rangeConstructVectorT.capacity() << std::endl;

//	// constructors used in the same order as described above:
//	ft::vector<int> first;                             // empty vector of ints
//	ft::vector<int> second (4,100);          // four ints with value 100
//	std::vector<int> third (second.begin(),second.end());  // iterating through second
//	std::vector<int> fourth (third);                       // a copy of third
//
//	// the iterator constructor can also be used to construct from arrays:
//	int myints[] = {16,2,77,29};
//	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
//
//	std::cout << "The contents of fifth are:";
//	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//		std::cout << ' ' << *it;
//	std::cout << '\n';

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
}
