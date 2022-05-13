// compilation:
// c++ -Wall -Wextra -Werror  -D STATUS=1 *.cpp -o vector.out && ./vector.out
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
	Test t1((unsigned)1);
	Test t2((unsigned)1);

		std::cout << (t1 == t2) << std::endl;
//		ft::vector<Test> vector;
//
//		for (int i = 0; i < 11; i++) {
//			Test    testData(i + 21);
//			vector.push_back(testData);
//		}

}
