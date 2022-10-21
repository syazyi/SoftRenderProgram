#pragma once
#include "vec.h"
namespace krender {
	namespace math {
		template<typename T, int rowSize, int colSize>
		class Matrix {
		public:
			Matrix<T, colSize, 1> row[rowSize] = {{}};
		public:
			Matrix() = default;
			Matrix<T, colSize, 1>& operator[](size_t const& index){
				return row[index];
			}
			Matrix<T, colSize, 1> const& operator[](size_t const& index)const{
				return row[index];
			}
		};
	}
	
}
