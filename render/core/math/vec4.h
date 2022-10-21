#pragma once
#include"vec.h"
#include"mat4x4.h"
namespace krender
{
	namespace math
	{
		template<typename T>
		class Matrix<T, 4, 1>{
		private:
			using value_type = T;
		public:
			value_type x = 0;
			value_type y = 0;
			value_type z = 0;
			value_type w = 1;
		public:
			Matrix<T, 4, 1>() = default;
			Matrix<T, 4, 1>(value_type const& px, value_type const& py, value_type const& pz, value_type const& pw = 1) : x(px), y(py), z(pz), w(pw){}
			Matrix<T, 4, 1>(Matrix<T, 3, 1> const& pvec3, value_type const& pw = 1) : x(pvec3[0]), y(pvec3[1]), z(pvec3[2]), w(pw){}
			
			Matrix<T, 4, 1>& operator*=(Matrix<T, 4, 4> const& rhs){
				Matrix<T, 4, 1> temp_Matrix;
				for(int i = 0; i < 4; i++){
					for(int j = 0; j < 4; j++){
						temp_Matrix[i] += rhs[i][j] * this->operator[](j);
					}
				}
				*this = temp_Matrix;
				return *this;
			} 
			value_type& operator[](size_t const& index) {
				switch (index)
				{
				case 0:
					return x;
					break;
				case 1:
					return y;
					break;
				case 2:
					return z;
					break;
				case 3:
					return w;
					break;
				}
			}
			value_type operator[](size_t const& index) const {
				switch (index)
				{
				case 0:
					return x;
					break;
				case 1:
					return y;
					break;
				case 2:
					return z;
					break;
				case 3:
					return w;
					break;
				}
			}

			Matrix<T, 3, 1> ToVec3() const{
				Matrix<T, 3, 1> tempvector;
				for(int i = 0; i < 3; i++){
					tempvector[i] = this->operator[](i);
				}
				return tempvector;
			}

			Matrix<T, 2, 1> ToVec2() const{
				Matrix<T, 2, 1> tempvector;
				for(int i = 0; i < 2; i++){
					tempvector[i] = this->data[i];
				}
				return tempvector;
			}

			Matrix<T, 4, 1>& operator+=(Matrix<T, 4, 1> const& rhs){
				for(int i = 0; i < 4; i++){
					this->operator[](i) += rhs[i]; 
				}
				return *this;
			}

			Matrix<T, 4, 1>& operator-=(Matrix<T, 4, 1> const& rhs){
				for(int i = 0; i < 4; i++){
					this->operator[](i) -= rhs[i]; 
				}
				return *this;
			}
	
			Matrix<T, 4, 1>& operator*=(value_type const& rhs){
				for(int i = 0; i < 4; i++){
					this->operator[](i) *= rhs;
				}
				return *this;
			}

			Matrix<T, 4, 1>& operator/=(value_type const& rhs){
				if(rhs == 0)
					return *this;
				for(int i = 0; i < 4; i++){
					this->operator[](i) /= rhs;
				}
				return *this;
			}
		};
		
		using Vec4uc = Matrix<unsigned char, 4, 1>;
		using Vec4f = Matrix<float, 4, 1>;
		using Vec4d = Matrix<double, 4, 1>;
		using Vec4i = Matrix<int, 4, 1>;
		//self type-aliasing
		using ColorVec4 = Vec4uc;
	} // namespace math
} // namespace krender
