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

#include <string>
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

#endif
