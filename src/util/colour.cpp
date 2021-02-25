#include "util/colour.hpp"

// namespace util
// {
// namespace colour
// {

wxColour& operator++(wxColour& color)
{
  int r = std::min(int(color.Red()) + 0x10, 255);
  int g = std::min(int(color.Green()) + 0x10, 255);
  int b = std::min(int(color.Blue()) + 0x10, 255);
  color.Set(r, g, b);
  return color;
}
wxColour operator++(wxColour& color, int/*not used*/)
{
  wxColour temp = color;
  ++color;
  return temp;
}
wxColour& operator--(wxColour& color)
{
  int r = std::max(int(color.Red()) - 0x10, 0);
  int g = std::max(int(color.Green()) - 0x10, 0);
  int b = std::max(int(color.Blue()) - 0x10, 0);
  color.Set(r, g, b);
  return color;
}
wxColour operator--(wxColour& color, int/*not used*/)
{
  wxColour temp = color;
  ++color;
  return temp;
}
wxColour operator+(wxColour const& color, int n)
{
  wxColour temp = color;
  int r = std::min(int(temp.Red()) + n, 255);
  int g = std::min(int(temp.Green()) + n, 255);
  int b = std::min(int(temp.Blue()) + n, 255);
  temp.Set(r, g, b);
  return temp;
}
wxColour operator-(wxColour const& color, int n)
{
  wxColour temp = color;
  int r = std::min(int(temp.Red()) - n, 255);
  int g = std::min(int(temp.Green()) - n, 255);
  int b = std::min(int(temp.Blue()) - n, 255);
  temp.Set(r, g, b);
  return temp;
}

// } // namespace colour
// } // namespace util
