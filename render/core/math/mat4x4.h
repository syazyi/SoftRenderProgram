#pragma once
#include"matrix.h"
namespace krender {
	namespace math {
		template<typename T>
		class Matrix<T, 4, 4> {
		private:
			using value_type = T;
		public:
			//row1
		Matrix<T, 4, 1> row[4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
		public:
			Matrix<T, 4, 4>() = default;
			explicit Matrix<T, 4, 4>(T const& value) {
				for (int i = 0; i < 4; i++)
					row[i][i] = value;
			}
			Matrix<T, 4, 4>(value_type const& row1x, value_type const& row1y, value_type const& row1z, value_type const& row1w,
				   			value_type const& row2x, value_type const& row2y, value_type const& row2z, value_type const& row2w,
				 	 		value_type const& row3x, value_type const& row3y, value_type const& row3z, value_type const& row3w,
				  			value_type const& row4x, value_type const& row4y, value_type const& row4z, value_type const& row4w){
					row[0][0] = row1x; row[0][1] = row1y; row[0][2] = row1z; row[0][3] = row1w;
				 	row[1][0] = row2x; row[1][1] = row2y; row[1][2] = row2z; row[1][3] = row2w;
				 	row[2][0] = row3x; row[2][1] = row3y; row[2][2] = row3z; row[2][3] = row3w;
				 	row[3][0] = row4x; row[3][1] = row4y; row[3][2] = row4z; row[3][3] = row4w;
			}

			Matrix<T, 4, 1>& operator[](size_t const& index){
				return row[index];
			}
			Matrix<T, 4, 1> const& operator[](size_t const& index)const{
				return row[index];
			}

			Matrix<T, 4, 4>& operator*=(Matrix<T, 4, 4> const& pmat4){
				Matrix<T, 4, 4> temp_Matrix;
				for(int i = 0; i < 4; i++){
					for(int k = 0; k < 4; k++){
						for(int j = 0; j < 4; j++){
							temp_Matrix[i][k] += this->operator[](i)[j] * pmat4[j][k];
						}
					}
				}
				*this = temp_Matrix;
				return *this;
			}

			void MatClear() {
				for(int i = 0; i < 4; i++)
					for(int j = 0; j < 4; j++){
						if( i == j)
							row[i][j] = 1;
						else
							row[i][j] = 0;
					}
				// row[0][0] = 1; row[0][1] = 0; row[0][2] = 0; row[0][3] = 0;
				// row[1][0] = 0; row[1][1] = 1; row[1][2] = 0; row[1][3] = 0;
				// row[2][0] = 0; row[2][1] = 0; row[2][2] = 1; row[2][3] = 0;
				// row[3][0] = 0; row[3][1] = 0; row[3][2] = 0; row[3][3] = 1;
			}


		};
		template<typename T, int rowSize, int colSize>
		Matrix<T, rowSize, 1> operator*(Matrix<T, rowSize, colSize> const& lhs, Matrix<T, colSize, 1> const& rhs){
			Matrix<T, rowSize, 1> temp_Matrix;
			for(int i = 0; i < rowSize; i++){
				for(int j = 0; j < colSize; j++){
					temp_Matrix[i] += lhs[i][j] * rhs[j];
				}
			}
			return temp_Matrix;
		} 

		template<typename T, int rowSize, int colSize, int otherSize>
		Matrix<T, rowSize, otherSize> operator*(Matrix<T, rowSize, colSize> const& lhs, Matrix<T, colSize, otherSize> const& rhs){
			Matrix<T, rowSize, otherSize> temp_Matrix;
			for(int i = 0; i < rowSize; i++){
				for(int k = 0; k < otherSize; k++){
					for(int j = 0; j < colSize; j++){
						temp_Matrix[i][k] += lhs[i][j] * rhs[j][k];
					}
				}
			}
			return temp_Matrix;
		} 
		using mat4 = Matrix<float, 4, 4>;
	}
	
}
