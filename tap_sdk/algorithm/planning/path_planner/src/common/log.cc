

#include "common/log.h"

std::string const_prefix(const char *file_name, int line_no) {
    return std::string(std::string(file_name) + ":" + std::to_string(line_no));
}

std::string const_prefix(char const *module_name,
                         char const *file_name,
                         int line_no) {
    return std::string(std::string(module_name) + ":" + std::string(file_name) +
                       ":" + std::to_string(line_no));
}

std::string lcformat(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    va_list args_copy;
    va_copy(args_copy, args);
    int size = std::vsnprintf(nullptr, 0, fmt, args_copy);
    va_end(args_copy);

    if (size < 0) {
        va_end(args);
        return "";
    }

    std::vector<char> buffer(static_cast<std::size_t>(size) + 1U);

    std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
    va_end(args);

    return std::string{buffer.data()};
}
