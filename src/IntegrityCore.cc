#include "../include/IntegrityCore.h"

ValidateMessage IntegrityCore::validateDirectory(const std::filesystem::path& targetDirectory)
{
  try {
    std::filesystem::file_status tDirectory = std::filesystem::status(targetDirectory);
    if (!std::filesystem::is_directory(tDirectory)) {
      return ValidateMessage{false, "invalid directory path"};
    }
    
    return ValidateMessage{true, "valid directory path"};
  }
  catch (std::filesystem::filesystem_error const& e) {
    std::cout << "Filesystem error: " << e.what() << std::endl;
    return ValidateMessage{false, e.what()};
  }
}
