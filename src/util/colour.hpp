#ifndef __UTIL_COLOUR_HPP__
#define __UTIL_COLOUR_HPP__

#include <wx/wx.h>

#ifdef UTIL_EXPORTS
# define UTIL_API __declspec(dllexport)
#else
# define UTIL_API __declspec(dllimport)
#endif // UTIL_EXPORTS

// namespace util
// {
// namespace colour
// {

// prefix increment operator overloading
// all rgb elements of specific colour will be increased by 0x10.
// if each rgb value of increased colour is over 255, will be cutted off.
//
// ex)
//  case #1
//  wxColour baseColour("#555555");
//  ++baseColour;
//  => baseColour will be #656565.
//
//  case #2
//  wxColour lightRed("#F0A0A0");
//  ++lightRed;
//  => lightRed will be #FFB0B0. red was cutted off.
UTIL_API wxColour& operator++(wxColour& color);

// postfix increment operator overloading
// all rgb elements of specifi colour will be increased by 0x10.
// if each rgb value of increased colour is over 255, will be cutted off.
//
// ex)
//  case #1
//  wxColour baseColour("#555555");
//  baseColour++;
//  => baseColour will be #656565.
//
//  case #2
//  wxColour lightBlue("#A0A0F0");
//  ++lightBlue;
//  => lightBlue will be #B0B0FF. blue was cutted off.
UTIL_API wxColour operator++(wxColour& color, int/*not used*/);

// prefix decrement operator overloading
// all rgb elements of specific colour will be decreased by 0x10.
// if each rgb value of decreased colour is below 0, will be cutted off.
//
// ex)
//  case #1
//  wxColour baseColour("#555555");
//  --baseColour;
//  => baseColour will be #454545.
//
//  case #2
//  wxColour darkRed("#500C0C");
//  --darkRed;
//  => darkRed will be #400000. green, blue was cutted off.
UTIL_API wxColour& operator--(wxColour& color);

// postfix decrement operator overloading
// all rgb elements of specific colour will be decreased by 0x10.
// if each rgb value of decreased colour is below 0, will be cutted off.
//
// ex)
//  case #1
//  wxColour baseColour("#555555");
//  baseColour--;
//  => baseColour will be #454545.
//
//  case #2
//  wxColour darkRed("#500C0C");
//  darkRed--;
//  => darkRed will be #400000. green, blue was cutted off.
UTIL_API wxColour operator--(wxColour& color, int/*not used*/);

// addition operator overloading
//
// ex)
//  wxColour baseColour("#555555");
//  wxColour whitenedBase = baseColour + 1;
UTIL_API wxColour operator+(wxColour const& color, int n);
UTIL_API wxColour operator-(wxColour const& color, int n);

// } // namespace colour
// } // namespace util

#endif // __UTIL_COLOUR_HPP__