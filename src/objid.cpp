#include "objid.h"

std::string ObjId::get_time_created() {
    std::string mytime(ctime(&timecreated));
    mytime.erase(mytime.size()-1);
    return mytime;
}
std::string ObjId::get_time_modified() {
    std::string mytime(ctime(&timemodified));
    mytime.erase(mytime.size()-1);
    return mytime;
}
std::string ObjId::get_accountId () {
    return accountId;
}
