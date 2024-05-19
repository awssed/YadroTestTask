#pragma once
#include "utils.h"

void utils::print_time(int time) {
    std::string output_hours, output_minutes;
    output_hours = std::to_string(time / 60);
    if (time / 60 < 10) output_hours = "0" + output_hours;
    output_minutes = std::to_string(time % 60);
    if (time % 60 < 10) output_minutes = "0" + output_minutes;
    std::cout << output_hours << ":" << output_minutes;
}