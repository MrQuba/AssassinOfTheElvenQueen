#include <iostream>
#include <cmath>
#include <type_traits>
#include <limits>
#pragma once
template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Math{
	public:
		static T InRange(T min, T current, T max){
			if(current > max) return max;
			if(current < min) return min;
			return current;
		}
		static T InvertVarIfConditionMet(bool condition, T& varToInvert){
			if(condition){
				varToInvert *= -1;
			}
			return varToInvert;
		}
		static T switchVarIfConditionMet(bool condition, T& varToInvert){
			if(condition){
				varToInvert = !varToInvert;
			}
			return varToInvert;
		}
		static T CalculateFunctionValueForX(T x, T(*func)(T), T multiplier = 1, T minRange = -std::numeric_limits<T>::max() , T maxRange = std::numeric_limits<T>::max()){
				T y = func(x) * multiplier;
				y = InRange(minRange, y, maxRange);	
				return y;
		}
		static float degreesToRadians(float angle){
			return angle * M_PI/180;
		}
		static sf::Vector2<T> calculateEndpoint(sf::Vector2<T> vec, T length, Angle angle){
			    T x = dynamic_cast<T>(vec.x + length * std::cos(degreesToRadians(angle)));
    			T y = dynamic_cast<T>(vec.y + length  * std::sin(degreesToRadians(angle)));
				return sf::Vector2<T>(x, y);
		}
		static	T sec(T x){
			return (T)(1 / std::cos(x));
		}
};
