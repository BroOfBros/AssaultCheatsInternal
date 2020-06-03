// Print messages ingame.

#pragma once

// Print top function prototype
typedef char* (__stdcall* tPrintTop) (char* formatString, ...);
constexpr auto tPrintTopAddr = 0x0046B060;

// Ingame text colors
constexpr auto green = "\x0C\x30";
constexpr auto blue = "\x0C\x31";
constexpr auto yellow = "\x0C\x32";
constexpr auto lightRed = "\x0C\x33";
constexpr auto grey = "\x0C\x34";
constexpr auto white = "\x0C\x35";
constexpr auto darkRed = "\x0C\x36";
constexpr auto red = "\x0C\x37";
constexpr auto purple = "\x0C\x38";
constexpr auto orange = "\x0C\x39";