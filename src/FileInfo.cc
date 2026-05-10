#include "FileInfo.h"

// Convert chrono time_point -> integer (nanoseconds since epoch)
static std::int64_t toUnixNanos(std::chrono::time_point<std::chrono::system_clock> tp) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count();
}

// Convert integer -> chrono time_point
static std::chrono::time_point<std::chrono::system_clock> fromUnixNanos(std::int64_t nanos) {
    return std::chrono::time_point<std::chrono::system_clock>(std::chrono::nanoseconds(nanos));
}

// Convert filesystem time -> integer
static std::int64_t toFsNanos(std::filesystem::file_time_type tp) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count();
}

// Convert integer -> filesystem time
static std::filesystem::file_time_type fromFsNanos(std::int64_t nanos) {
    return std::filesystem::file_time_type(std::chrono::nanoseconds(nanos));
}

void to_json(nlohmann::json& j, FileInfo const& fi) {
  j = {
    {"fileName", fi.fileName},
    {"filePath", fi.filePath.string()},
    {"fileExtension", fi.fileExtension},
    {"fileSize", fi.fileSize},
    {"permissions", static_cast<std::uint32_t>(fi.permissions)},
    {"fileHash", fi.fileHash},
    {"lastModified", toFsNanos(fi.lastModified)},
    {"recordTimestamp", toUnixNanos(fi.recordTimestamp)}
  };
}

void from_json(nlohmann::json const& j, FileInfo& fi) {
    j.at("fileName").get_to(fi.fileName);

    std::string pathStr;
    j.at("filePath").get_to(pathStr);
    fi.filePath = pathStr;

    j.at("fileExtension").get_to(fi.fileExtension);
    
    j.at("fileSize").get_to(fi.fileSize);

    std::uint32_t permsInt;
    j.at("permissions").get_to(permsInt);
    fi.permissions = static_cast<std::filesystem::perms>(permsInt);

    j.at("fileHash").get_to(fi.fileHash);

    std::int64_t lm;
    j.at("lastModified").get_to(lm);
    fi.lastModified = fromFsNanos(lm);

    std::int64_t rt;
    j.at("recordTimestamp").get_to(rt);
    fi.recordTimestamp = fromUnixNanos(rt);
}
