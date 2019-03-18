#include "objid.h"

std::string ObjId::get_time_created() {
    std::string mytime(ctime(&timecreated));
    return mytime;
}
std::string ObjId::get_accountId () {
    return accountId;
}
