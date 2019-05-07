#ifndef OBJID_H_
#define OBJID_H_

#include <string>
#include <ctime>

class ObjId {
    std::string accountId;
    time_t timecreated;
    time_t timemodified;
    public:
        ObjId() : timecreated(time(0)) {}
        ObjId(std::string aid) : accountId(aid), timecreated(time(0)), timemodified(time(0)) {}
        ObjId(std::string aid, time_t mytime) : accountId(aid), timecreated(mytime), timemodified(mytime) {}
        void set_timemodified() { timemodified = time(0); }
        std::string get_time_created ();
        std::string get_time_modified (); 
        std::string get_accountId ();

};

#endif
