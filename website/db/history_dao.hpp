#ifndef __CALC_HISTORY_DAO_HPP
#define __CALC_HISTORY_DAO_HPP

#include "../user_history.hpp"

class HistoryDatabaseAccessObject {
protected:
    HistoryDatabaseAccessObject() {}
    virtual ~HistoryDatabaseAccessObject() noexcept {}
public:
};

#endif // __CALC_HISTORY_DAO_HPP