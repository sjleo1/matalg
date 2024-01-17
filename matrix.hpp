#include <iostream>
#include <vector>


template<typename T>
class Mat {
private:

	static constexpr size_t _dim = 2;
	T** _mat;
	size_t _height;        // FIRST INDEX
	size_t _width;         // SECOND INDEX

	bool isAddable(const Mat<T>& addend) const;
	bool isMultiplicable(const Mat<T>& multiplier) const;

public:
	static constexpr size_t npos = (-1) >> 1;

	// default constructor
	Mat();

	// constructor (size only)
	Mat(const size_t height, const size_t width);

	// constructor (double pointer)
	Mat(T** mat, const size_t height, const size_t width);

	// constructor (2d vector)
	Mat(const std::vector<std::vector<T>>& mat);

	// constructor (Mat)
	Mat(const Mat<T>& mat);

	// destructor
	~Mat();

	size_t height() const;
	size_t width() const;

	Mat<T>& operator=(const Mat<T>& other);
	bool operator==(const Mat<T>& other) const;
	T* const operator[](size_t i) const;
	Mat<T> operator+(const Mat<T>& addend) const;
	Mat<T> operator*(const Mat<T>& multiplier) const;

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Mat<T>& mat);

// Below are definitions of the class template.
// They have not been separated to .cpp file to avoid "Unresolved external" error.

template<typename T>
bool Mat<T>::isAddable(const Mat<T>& addend) const {
	if (this->_width == addend.width())
		if (this->_height == addend.height())
			return true;
		else return false;
	else return false;
}

template<typename T>
bool Mat<T>::isMultiplicable(const Mat<T>& multiplier) const {
	if (this->_width == multiplier.height()) return true;
	else return false;
}

// default constructor
template<typename T>
Mat<T>::Mat() : _mat(nullptr), _width(npos), _height(npos) {}

// constructor (size only)
template<typename T>
Mat<T>::Mat(const size_t height, const size_t width)
	: _mat(nullptr), _height(height), _width(width) {
	this->_mat = new T * [height];

	for (size_t i = 0; i < height; ++i)
		this->_mat[i] = new T[width];
}

// constructor (double pointer)
template<typename T>
Mat<T>::Mat(T** mat, const size_t height, const size_t width)
	: _mat(nullptr), _height(height), _width(width) {
	this->_mat = new T * [height];

	for (size_t i = 0; i < height; ++i) {
		this->_mat[i] = new T[width];

		for (size_t j = 0; j < width; ++j)
			this->_mat[i][j] = mat[i][j];
	}
}

// constructor (2d vector)
template<typename T>
Mat<T>::Mat(const std::vector<std::vector<T>>& mat)
	: _mat(nullptr), _height(mat.size()), _width(mat[0].size()) {
	this->_mat = new T * [_height];

	for (size_t i = 0; i < _height; ++i) {
		this->_mat[i] = new T[_width];

		for (size_t j = 0; j < _width; ++j)
			this->_mat[i][j] = mat[i][j];
	}
}

// constructor (Mat)
template<typename T>
Mat<T>::Mat(const Mat<T>& mat) : _mat(nullptr), _height(mat.height()), _width(mat.width()) {
	this->_mat = new T * [_height];

	for (size_t i = 0; i < _height; ++i) {
		this->_mat[i] = new T[_width];

		for (size_t j = 0; j < _width; ++j)
			this->_mat[i][j] = mat[i][j];
	}
}

// destructor
template<typename T>
Mat<T>::~Mat() {
	for (size_t i = 0; i < _height; ++i)
		delete this->_mat[i];

	delete[] this->_mat;

	this->_height = this->npos;
	this->_width = this->npos;
}

template<typename T>
size_t Mat<T>::height() const { return this->_height; }

template<typename T>
size_t Mat<T>::width() const { return this->_width; }

template<typename T>
Mat<T>& Mat<T>::operator=(const Mat<T>& other) {
	if (this == &other) return *this;

	this->~Mat();

	this->_height = other._height();
	this->_width = other._width();

	this->_mat = new T * [this->_height];

	for (size_t i = 0; i < this->_height; ++i) {
		this->_mat[i] = new T[this->_width];

		for (size_t j = 0; j < this->_width; ++j)
			this->_mat[i][j] = other[i][j];
	}

	return *this;
}

template<typename T>
bool Mat<T>::operator==(const Mat<T>& other) const {
	if (this->_height == other._height)
		if (this->_width == other._width)
			for (size_t i = 0; i < this->_height; ++i)
				for (size_t j = 0; j < this->_width; ++j) {
					if (this->_mat[i][j] != other[i][j])
						return false;
				}
		else return false;
	else return false;

	return true;
}


template<typename T>
T* const Mat<T>::operator[](size_t i) const {
	return this->_mat[i];
}

template<typename T>
Mat<T> Mat<T>::operator+(const Mat<T>& addend) const {
	if (!isAddable(addend)) return Mat<T>();

	Mat<T> sum = Mat<T>(*this);

	for (size_t i = 0; i < sum.height(); ++i)
		for (size_t j = 0; j < sum.width(); ++j)
			sum[i][j] += addend[i][j];

	return sum;
}

template<typename T>
Mat<T> Mat<T>::operator*(const Mat<T>& multiplier) const {
	if (!isMultiplicable(multiplier)) return Mat<T>();

	Mat<T> product = Mat<T>(this->_height, multiplier._width);

	for (size_t i = 0; i < this->_height; ++i)
		for (size_t j = 0; j < multiplier._width; ++j) {
			T acc = this->_mat[i][0] * multiplier[0][j];

			for (size_t k = 1; k < this->_width; ++k)
				acc += this->_mat[i][k] * multiplier[k][j];

			product[i][j] = acc;
		}

	return product;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Mat<T>& mat) {
	for (size_t i = 0; i < mat.height(); ++i) {
		for (size_t j = 0; j < mat.width(); ++j)
			os << mat[i][j] << " ";
		os << std::endl;
	}

	return os;
}