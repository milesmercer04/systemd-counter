#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <csignal>
#include <ctime>

using namespace std;

// Global file stream, opened by main, closed by signal handler
ofstream file;

// User's name, defined globally so signal handler can access
string name = "Miles";

void signal_handler(int signum);

int main() {
  // Register signal handler for SIGTERM signal
  signal(SIGTERM, signal_handler);

  // Open output file stream
  file.open("/tmp/currentCount.out");

  // Make a counter variable
  int count = 0;

  // Define variables for date and time
  time_t current_time;
  char* date_time;

  // Until program is terminated, print name, date-time, and counter every second
  while (true) {
    file << name << ": ";
    current_time = time(nullptr);
    date_time = ctime(&current_time);
    date_time[strcspn(date_time, "\n")] = '\0';
    file << date_time << " #" << count++ << endl;
    sleep(1);
  }

  return 0;
}

// ***************************************************************
// Function: signal_handler()
// Description: User-defined function to handle the SIGTERM signal
// Input: Signal number, never used
// ***************************************************************
void signal_handler(int signum) {
  // Print SIGTERM message
  file << name << ": ";
  time_t current_time = time(nullptr);
  char* date_time = ctime(&current_time);
  date_time[strcspn(date_time, "\n")] = '\0';
  file << date_time << " Received SIGTERM, exiting" << endl << flush; // Force STDOUT flush

  // Close the output file and exit the program
  file.close();
  exit(143); // Exit status for SIGTERM
}