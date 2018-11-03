#include <iostream>

template<typename Object>
class Vector {
public:
	explicit Vector(int initSize = 0) : theSize{ initSize },
		theCapacity{ initSize + SPACE_CAPACITY } {
		objects = new Object[theCapacity];
	}

	Vector(const Vector & rhs) :theSize{ rhs.theSize },
		theCapacity{ rhs.theCapacity }, objects{ nullptr } {
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k) {
			objects[k] = rhs.objects[k];
		}
	}

public:
	static const int SPACE_CAPACITY = 16;

private:
	int theSize;
	int theCapacity;
	Object *objects;
};

int main() {

	Vector<int> a;

	return 0;
}