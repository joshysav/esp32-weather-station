/** The MIT License (MIT)
    Copyright (c) 2015 by Daniel Eichhorn
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
    See more at http://blog.squix.ch
*/

#include <simpleDSTadjust.h>

#define UPDATE_INTERVAL_SECS  300 // Update interval in seconds
#define SDS30_SETTLE_SECS 30 // SDS30 settle time in seconds

#define UPDATE_TURN_SDS30_ON    0
#define UPDATE_SENSORS          1
#define UPDATE_FORECAST         2

const uint8_t MAX_FORECASTS = 9; // must be >= 9

// Adjust according to your language
const String WDAY_NAMES[] = {"SO", "MO", "DI", "MI", "DO", "FR", "SA"};
const String MONTH_NAMES[] = {"JAN", "FEB", "MÄR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEZ"};
const String SUN_MOON_TEXT[] = {"Sonne", "Auf", "Unter", "Mond", "Age", "Illum"};
const String MOON_PHASES[] = {"Neumond", "erstes Viertel", "zunehmender Halbmond", "zweites Viertel",
                              "Vollmond", "drittes Viertel", "abnehmender Halbmond", "letztes Viertel"
                             };

#define UTC_OFFSET +1
struct dstRule StartRule = {"CEST", Last, Sun, Mar, 2, 3600}; // Central European Summer Time = UTC/GMT +2 hours
struct dstRule EndRule = {"CET", Last, Sun, Oct, 2, 0};       // Central European Time = UTC/GMT +1 hour

// Settings for Boston
// #define UTC_OFFSET -5
// struct dstRule StartRule = {"EDT", Second, Sun, Mar, 2, 3600}; // Eastern Daylight time = UTC/GMT -4 hours
// struct dstRule EndRule = {"EST", First, Sun, Nov, 1, 0};       // Eastern Standard time = UTC/GMT -5 hour

// values in metric or imperial system?
const boolean IS_METRIC = true;

// Change for 12 Hour/ 24 hour style clock
bool IS_STYLE_12HR = false;

// change for different ntp (time servers)
#define NTP_SERVERS "0.ch.pool.ntp.org", "1.ch.pool.ntp.org", "2.ch.pool.ntp.org"

// Feather Huzzah32 + 2.4" TFT wing
// Pins for the ILI9341 + Touch
#define TFT_DC 33
#define TFT_CS 15
#define TFT_LED 27

/***************************
    End Settings
 **************************/
