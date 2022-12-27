#ifndef KRENDER_VEC_H
#define KRENDER_VEC_H
#include <cmath>
//#include <cstdarg>
#include "matrix.h"
namespace krender {
	namespace math {
		template<typename T, int rowSize, int colSize>
		class Matrix;
		template<typename T, int rowSize>
		class Matrix<T, rowSize, 1> { 
			public:
				using value_type = T;
			public:
				Matrix<T, rowSize, 1>() = default;
				// explicit Matrix(...) {
				// 	va_list args;
				// 	va_start(args, rowSize);
				// 	for(int i = 0; i < rowSize; i++){
				// 		data[i] = va_arg(args , T);
				// 	}
				// 	va_end(args);
				// }

				value_type& operator[](size_t const index){
					return data[index];
				}

				value_type operator[](size_t const index) const{
					return data[index];
				}

				Matrix<T, rowSize, 1>& operator+=(Matrix<T, rowSize, 1> const& rhs){
					for(int i = 0; i < rowSize; i++){
						this->operator[](i) += rhs[i]; 
					}
					return *this;
				}

				Matrix<T, rowSize, 1>& operator-=(Matrix<T, rowSize, 1> const& rhs){
					for(int i = 0; i < rowSize; i++){
						this->operator[](i) -= rhs[i]; 
					}
					return *this;
				}
	
				Matrix<T, rowSize, 1>& operator*=(value_type const& rhs){
					for(int i = 0; i < rowSize; i++){
						this->operator[](i) *= rhs;
					}
					return *this;
				}

				Matrix<T, rowSize, 1>& operator/=(value_type const& rhs){
					if(rhs == 0)
						return *this;
					for(int i = 0; i < rowSize; i++){
						this->operator[](i) /= rhs;
					}
					return *this;
				}
				
				value_type Norm() const{
					return std::sqrt((*this) * (*this));
				}
			public:
				value_type data[rowSize] = {0};
		};
//As long as [] operator is overloaded, these functions can be used correctly
		template<typename T, int rowSize>
		T operator*(Matrix<T, rowSize, 1> const & lhs, Matrix<T, rowSize, 1> const & rhs){
			T tempvalue = 0;
			for(int i = 0; i < rowSize; i++){
				tempvalue +=  lhs[i] * rhs[i];
			}
			return tempvalue;
		}

		template<typename T, int rowSize>
		Matrix<T, rowSize, 1> operator*(Matrix<T, rowSize, 1> const& lhs, T const& rhs){
			Matrix<T, rowSize, 1> tempMatrix;
			for(int i = 0; i < rowSize; i++){
				tempMatrix[i] = lhs[i] * rhs;
			}
			return tempMatrix;
		}

		template<typename T, int rowSize>
		Matrix<T, rowSize, 1> operator*(T const& lhs, Matrix<T, rowSize, 1> const& rhs){
			Matrix<T, rowSize, 1> tempMatrix;
			for(int i = 0; i < rowSize; i++){
				tempMatrix[i] = rhs[i] * lhs;
			}
			return tempMatrix;
		}

		template<typename T, int rowSize>
		Matrix<T, rowSize, 1> operator+(Matrix<T, rowSize, 1> const& lhs, Matrix<T, rowSize, 1> const& rhs){
			Matrix<T, rowSize, 1> tempMatrix;
			for(int i = 0; i < rowSize; i++){
				tempMatrix[i] = lhs[i] + rhs[i];
			}
			return tempMatrix;
		}

		template<typename T, int rowSize>
		Matrix<T, rowSize, 1> operator-(Matrix<T, rowSize, 1> const& lhs, Matrix<T, rowSize, 1> const& rhs){
			Matrix<T, rowSize, 1> tempMatrix;
			for(int i = 0; i < rowSize; i++){
				tempMatrix[i] = lhs[i] - rhs[i];
			}
			return tempMatrix;
		}

		template<typename T, int rowSize>
		Matrix<T, rowSize, 1> operator/(Matrix<T, rowSize, 1> const& lhs, T const& rhs){
			if(rhs == 0) 
				return Matrix<T, rowSize, 1>();
			Matrix<T, rowSize, 1> tempMatrix;
			for(int i = 0; i < rowSize; i++){
				tempMatrix[i] = lhs[i] - rhs;
			}
			return tempMatrix;
		}
	}//namespace math
}//namespace krender

#endif