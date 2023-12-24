//
// Created by TaxMachine on 2023-12-24.
//

#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <string>
#include <vector>
#include <chrono>

using std::chrono::year, std::chrono::year_month, std::chrono::month;

struct Language {
    std::string name;
    year_month start_date;
};

const std::vector<Language> LANGUAGES = {
    {"C++", year_month{year{2023}, month{9}}},
    {"C", year_month{year{2023}, month{9}}},
    {"Python", year_month{year{2021}, month{6}}},
    {"Java", year_month{year{2022}, month{1}}},
    {"JavaScript", year_month{year{2021}, month{6}}},
    {"Typescript", year_month{year{2023}, month{3}}},
    {"Nim", year_month{year{2022}, month{9}}}
};

#endif //DETAILS_HPP
