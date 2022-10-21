#pragma once
#include"vec.h"
namespace krender {
	namespace math {
		template<typename T>
		class Matrix<T, 3, 1> {
		private:
			using value_type = T;
			using vector3x = Matrix<T, 3, 1>;
		public:
			value_type x = 0;
			value_type y = 0;
			value_type z = 0;

		public:
			Matrix<T, 3, 1>() = default;
			Matrix<T, 3, 1>(value_type const& px, value_type const& py, value_type const& pz) : x(px), y(py), z(pz) {}
			//***
			value_type Norm() const{
				return std::sqrt((*this) * (*this));
			}
			
			Matrix<T, 3, 1>& Normalize(){
				*this /= Norm();
				return *this;
			}
			//operators overloading
			value_type& operator[](size_t const& index){
				return index ? (index == 1 ? y : z) : x;
			}

			value_type operator[](size_t const& index) const{
				return index ? (index == 1 ? y : z) : x;
			}

			vector3x& operator+=(vector3x const& vector3) {
				plus_self_imple(vector3);
				return *this;
			}
			vector3x& operator-=(vector3x const& vector3) {
				sub_self_imple(vector3);
				return *this;
			}

			vector3x& operator*=(value_type const& rhs){
				for(int i = 0; i < 3; i++){
					this->operator[](i) *= rhs;
				}
				return *this;
			}

			vector3x& operator/=(value_type const& rhs){
				if(rhs == 0)
					return *this;
				for(int i = 0; i < 3; i++){
					this->operator[](i) /= rhs;
				}
				return *this;
			}
		protected:
			void plus_self_imple(vector3x const& vector3) {
				this->x += vector3.x;
				this->y += vector3.y;
				this->z += vector3.z;
			}

			void sub_self_imple(vector3x const& vector3) {
				this->x -= vector3.x;
				this->y -= vector3.y;
				this->z -= vector3.z;
			}
		};

		template<typename T>
		Matrix<T, 3, 1> Cross(Matrix<T, 3, 1> const& lhs, Matrix<T, 3, 1> const& rhs){
			return Matrix<T, 3, 1>(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
		}
		//type-aliasing
		using Vec3i = Matrix<int, 3, 1>;
		using Vec3f = Matrix<float, 3, 1>;
		using Vec3d = Matrix<double, 3, 1>;
		using Vec3ui = Matrix<unsigned char, 3, 1>;
		using Point = Vec3f;
		using ColorVec3 = Vec3ui;
	}
	
}

