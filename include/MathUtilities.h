#pragma once
#include <random>
#include <type_traits>

namespace MathU
{
	// ================================================
	//        Random min/max for int and floats        
	// ================================================
	template <typename T>
	static T Random(T min, T max)
	{
		static_assert(std::is_arithmetic<T>::value, "Template args must be int or float");
		std::random_device rd;
		std::mt19937 gen(rd(), rd(), rd(), rd(), rd());
		if constexpr (std::is_integral<T>::value)
		{
			std::uniform_int_distribution<T> dis(min, max);
			return dis(gen);
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			std::uniform_real_distribution<T> dis(min, max);
			return dis(gen);
		}
	}
	
	// ================================================
	//         Discrete Probability function           
	// ================================================
	int DiscreteProbability(const std::vector<float>& probabilities)
	{
		std::random_device rd;
		std::mt19937 gen(rd(), rd(), rd(), rd(), rd());
		std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
		return dist(gen);
	}
}