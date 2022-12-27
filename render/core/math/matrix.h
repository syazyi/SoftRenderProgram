#ifndef KRENDER_MATRIX_H
#define KRENDER_MATRIX_H
#include "vec.h"
#include <cassert>
#include <utility>
namespace krender {
	namespace math {
		template<typename T, int rowSize, int colSize>
		class Matrix {
		public:
			Matrix<T, colSize, 1> row[rowSize] = {{}};
		public:
			Matrix() = default;
			Matrix(T value) {
				for (int i = 0; i < rowSize; i++) {
					for (int j = 0; j < colSize; j++) {
						if (i == j) {
							row[i][j] = value;
						}
						else {
							row[i][j] = 0;
						}
					}
				}
			} 
			Matrix<T, colSize, 1>& operator[](size_t const& index){
				return row[index];
			}
			Matrix<T, colSize, 1> const& operator[](size_t const& index)const{
				return row[index];
			}
			Matrix<T, rowSize, colSize>& Inverse() {
				assert(rowSize == colSize);
				Matrix<T, rowSize, colSize> temp(1.f);
				for (size_t j = 0; j < colSize; j++)
				{
					auto [mijMax, mijMaxRow] = GetMaxValueColForInverse(j);
					assert(mijMax != 0);
					if (mijMaxRow != j) {
						EleRowOpChangeRow(*this, j, mijMaxRow);
						//make same change
						EleRowOpChangeRow(temp, j, mijMaxRow);
					}
					EleRowOpMulScalar(*this, j, 1.0f / mijMax);
					EleRowOpMulScalar(temp, j, 1.0f / mijMax);
					for (int r = 0; r < rowSize; r++) {
						if (r != j) {
							T mrj = this->operator[](r)[j];
							EleRowOpAddRow(*this, j, -mrj, r);
							EleRowOpAddRow(temp, j, -mrj, r);
						}
					}
				}
				AssignmentMatrix(temp, *this);
				return *this;
			}
		};

		template<typename T, int rowSize, int colSize>
		static void EleRowOpChangeRow(Matrix<T, rowSize, colSize>& value, int from, int to){
			assert((from < rowSize) && (to < rowSize));
			for(int i = 0; i < colSize; i++){
				T change = 0;
				change = value[from][i];
				value[from][i] = value[to][i];
				value[to][i] = change;
			}
		}

		template<typename T, int rowSize, int colSize>
		static void EleRowOpMulScalar(Matrix<T, rowSize, colSize>& value, int row, float scalar){
			assert(row < rowSize);
			for(int i = 0; i < colSize; i++){
				value[row][i] *= scalar;
			}
		}

		template<typename T, int rowSize, int colSize>
		static void EleRowOpAddRow(Matrix<T, rowSize, colSize>& value, int from, float multiple, int to){
			assert((from < rowSize) && (to < rowSize));
			for(int i = 0; i < colSize; i++){
				value[to][i] += value[from][i] * multiple;
			}
		}

		template<typename T, int rowSize, int colSize>
		static void AssignmentMatrix(const Matrix<T, rowSize, colSize>& from, Matrix<T, rowSize, colSize>& to) {
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					to[i][j] = from[i][j];
				}
			}
		}

		template<typename T, int rowSize, int colSize>
		static auto GetMaxValueColForInverse(const Matrix<T, rowSize, colSize>& matValue, int col) {
			T max = 0;
			int maxRow = 0;
			T absMax = 0;
			for (int i = col; i < rowSize; i++) {
				auto value = matValue[i][col];
				auto absValue = abs(value);
				if (absMax < absValue) {
					absMax = absValue;
					max = value;
					maxRow = i;
				}
			}
			return std::make_pair(max, maxRow);
		}

		//Gauss-Jordan 
		template<typename T, int rowSize, int colSize>
		Matrix<T, rowSize, colSize> Inverse(Matrix<T, rowSize, colSize> value) {
			assert(rowSize == colSize);
			Matrix<T, rowSize, colSize> temp(1.f);
			for (size_t j = 0; j < colSize; j++)
			{
				auto [mijMax, mijMaxRow] = GetMaxValueColForInverse(value, j);
				assert(mijMax != 0);
				if (mijMaxRow != j) {
					EleRowOpChangeRow(value, j, mijMaxRow);
					//make same change
					EleRowOpChangeRow(temp, j, mijMaxRow);
				}
				EleRowOpMulScalar(value, j, 1.0f / mijMax);
				EleRowOpMulScalar(temp, j, 1.0f / mijMax);
				for (int r = 0; r < rowSize; r++) {
					if (r != j) {
						T mrj = value[r][j];
						EleRowOpAddRow(value, j, -mrj, r);
						EleRowOpAddRow(temp, j, -mrj, r);
					}
				}
			}
			AssignmentMatrix(temp, value);
			return temp;
		}

	}
	
}

#endif