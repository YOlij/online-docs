/**
* @file
* @author Yvonne <yvonneIsLeBonAndMore@address.com>
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
* The time class represents a moment of time.
*/
/**
* @brief A sample Time class
* @author Future DB Guru
*
* This is a simple class to demonstrate how Doxygen is used.
* It implements a dummy Time class.
*/
class Time {
 public:
 /**
 * Constructor that sets the time to a given value.
 *
 * @param timemillis Number of milliseconds
 * passed since Jan 1, 1970.
 */
 Time (int timemillis) {
 // the code
 }
 /**
 * Get the current time.
 *
 * @return A time object set to the current time. */
 static Time now () {
 // the code }
};