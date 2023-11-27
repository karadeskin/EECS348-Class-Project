#include "logger.hpp"

Logger::Logger() {}

std::string priority(Logger::Priority p) {
    switch (p) {
    case Logger::Priority::ERROR:
    }
}

Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}

void Logger::log(Logger::Priority p, const std::string &message) const {

}
