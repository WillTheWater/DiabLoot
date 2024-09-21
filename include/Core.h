#pragma once
#include <map>
#include <unordered_map>
#include <memory>
#include <stdio.h>

namespace core
{
	// ================================================
	//           Macro for consol output 
	// ================================================
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__);

	// ================================================
	//            Alias for smart pointers
	// ================================================
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	// ================================================
	//            Alias for containers
	// ================================================
	template<typename T>
	using list = std::vector<T>;

	template<typename key, typename value, typename predicate = std::less<key>>
	using Omap = std::map<key, value, predicate>;

	template<typename key, typename value, typename hasher = std::hash<key>>
	using Umap = std::unordered_map<key, value, hasher>;
}