/*! 
 *      @file utils.h
 *      @brief This header file contains some general purpose
 *      utility functions. 
 *
 *      @author Mr. Juha Ylioinas
 *
 *      @date 17/3/2019
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>



/*!
 *
 *
 */
int checkDepositAndCollectCents(std::string& deposit, std::string& cents);
/*!
 *
 *
 */
int collectToken(std::string&, std::string&);
/*!
 *
 *
 */
void Pause();
/*!
 *
 *
 */
bool containsOnlyDigits(std::string&);

//! A utility function to check that an accountId is of a valid form (ruled by templateId)
/*!
 *
 *  @param accountId a string reference of an accountId std::string
 *  @param templateId a string reference of an templateId std::string
 *  @return A boolean to flag is valid (true) or not (false)
 *
 */
bool isValidAccountId(std::string& accountId, std::string& templateId);

int get_month_index(std::string name);

time_t convertTimeString2time_t(std::string timecreated);




#endif
