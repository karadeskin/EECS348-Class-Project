#ifndef __CALC_LOGGER_HPP__
#define __CALC_LOGGER_HPP__

#include <string>

class Logger {
private:
    Logger();
public:
    enum class Priority {
        ERROR,
        WARN,
        INFO
    };

    static Logger& get_instance();
    void log(Logger::Priority p, const std::string &message) const;
};

#endif // __CALC_LOGGER_HPP__