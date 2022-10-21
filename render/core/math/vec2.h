#pragma once
#include "vec.h"
namespace krender{
    namespace math{
        template<typename T>
        class Matrix<T, 2, 1> {
            private:
                using value_type = T;
            public:
                value_type x = 0;
                value_type y = 0;
            public:
                Matrix<T, 2, 1>() = default;
                Matrix<T, 2, 1>(value_type const& px, value_type const& py) : x(px), y(py){}
                value_type& operator[](size_t const& index){
                    return index ? y : x;
                }

                value_type operator[](size_t const& index) const{
                    return index ? y : x;
                }

                Matrix<T, 2, 1>& operator+=(Matrix<T, 2, 1> const& rhs){
					for(int i = 0; i < 2; i++){
						this->operator[](i) += rhs[i]; 
					}
					return *this;
				}

				Matrix<T, 2, 1>& operator-=(Matrix<T, 2, 1> const& rhs){
					for(int i = 0; i < 2; i++){
						this->operator[](i) -= rhs[i]; 
					}
					return *this;
				}
	
				Matrix<T, 2, 1>& operator*=(value_type const& rhs){
					for(int i = 0; i < 2; i++){
						this->operator[](i) *= rhs;
					}
					return *this;
				}

				Matrix<T, 2, 1>& operator/=(value_type const& rhs){
					if(rhs == 0)
						return *this;
					for(int i = 0; i < 2; i++){
						this->operator[](i) /= rhs;
					}
					return *this;
				}
				

                value_type Norm() const{
                    return std::sqrt((*this) * (*this));
                }

                Matrix<T, 2, 1>& Normalize(){
                    *this /= Norm();
                    return *this;
                }
        };

        using Vec2f = Matrix<float, 2, 1>;
        using Vec2ui = Matrix<unsigned char, 2, 1>; 
    }
}