#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>

std::vector<std::vector<std::string>> readCSV(const std::string& filename);

// becuse the list could be any type of list, we will make it a template function and define it in header
void shuffle_list(auto& list) {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{ rd() };
    std::ranges::shuffle(list, rng);
}