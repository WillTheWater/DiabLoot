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
		std::mt19937 gen(rd());
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
	static int DiscreteProbability(const std::vector<float>& probabilities)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
		return dist(gen);
	}
	/*
	// Define the probability distribution

	std::vector<float> probabilities = { 0.1, 0.2, 0.4, 0.3 };  // Sum should be 1 but can be any non-negative numbers

	// Use the DiscreteProbability function

	int randomIndex = DiscreteProbability(probabilities);
	*/
}