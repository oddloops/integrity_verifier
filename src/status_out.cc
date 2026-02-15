#include "../include/status_out.h"

Status normalizeInput(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  if (s == "1" || s == "RECORD") return Status::RECORD;
  if (s == "2" || s == "READ") return Status::READ;
  if (s == "3" || s  == "VERIFY") return Status::VERIFY;
  if (s == "4" || s  == "EXIT") return Status::EXIT;
  return Status::INVALID;
}

void print_status (Status status) {
  if (status == Status::RECORD) {
    std::cout << "Entering Record Mode..." << std::endl;
  }
  else if (status == Status::READ) {
    std::cout << "Entering Read Mode..." << std::endl;
  }
  else if (status == Status::VERIFY) {
    std::cout << "Entering Verify Mode..." << std::endl;
  }
  else {
    std::cout << "Exiting..." << std::endl;
  }
  return;
}
