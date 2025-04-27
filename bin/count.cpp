
#include "count.h"

using namespace std;

// Global file stream, opened by main, closed by signal handler
ofstream file;

#ifndef UNIT_TEST
int main() {
  // Register signal handler for SIGTERM signal
  signal(SIGTERM, signal_handler);

  // Open output file stream
  file.open(OUT_FILE);

  // Verify file open
  if (!file.is_open()) {
    cerr << "Failed to open " << OUT_FILE << endl << flush;
    return 1;
  }

  // Make a counter variable
  int count = 0;

  // Define variables for date and time
  time_t current_time;
  char* date_time;

  // Until program is terminated, print name, date-time, and counter every second
  while (true) {
    current_time = time(nullptr);
    file << output_time(current_time, count++) << endl << flush;
    sleep(1);
  }

  return 0;
}
#endif

// ***************************************************************
// Function: signal_handler()
// Description: User-defined function to handle the SIGTERM signal
// Input: Signal number, never used
// ***************************************************************
void signal_handler(int signum) {
  // Print SIGTERM message
  time_t current_time = time(nullptr);
  file << output_termination(current_time) << endl << flush; // Force STDOUT flush

  // Close the output file and exit the program
  file.close();
  exit(143); // Exit status for SIGTERM
}

// ***********************************************************************
// Function: output_time()
// Description: Returns message to output based on current time and count
// Input: Current time as a time_t type object and current count as an int
// Returns: The string message to print to the output file
// ***********************************************************************
string output_time(time_t current_time, int count) {
  char* date_time = ctime(&current_time);
  date_time[strcspn(date_time, "\n")] = '\0';
  return NAME + string(": ") + date_time + string(" #") + to_string(count);
}

// ***********************************************************************
// Function: output_termination()
// Description: Returns message to print upon receiving termination signal
// Input: The current time as a time_t type object
// Returns: The string message to print to the output file
// ***********************************************************************
string output_termination(time_t current_time) {
  char* date_time = ctime(&current_time);
  date_time[strcspn(date_time, "\n")] = '\0';
  return NAME + string(": ") + date_time + " Received SIGTERM, exiting";
}
