#ifndef OBJID_H_
#define OBJID_H_

#include <string>
#include <ctime>

class ObjId {
    std::string accountId;
    time_t timecreated;
    public:
        ObjId() : timecreated(time(0)) {}
        ObjId(std::string aid) : accountId(aid), timecreated(time(0)) {}
        ObjId(std::string aid, time_t mytime) : accountId(aid), timecreated(mytime) {}
        std::string get_time_created (); 
        std::string get_accountId ();

};

#endif
