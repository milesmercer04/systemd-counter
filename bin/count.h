#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <csignal>
#include <ctime>

// Global variables
#define NAME "Miles"
#define OUT_FILE "/tmp/currentCount.out"

// Functions defined in count.cpp
void signal_handler(int signum);
std::string output_time(time_t current_time, int count);
std::string output_termination(time_t current_time);
