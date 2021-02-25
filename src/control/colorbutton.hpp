#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <wx/wx.h>

#ifdef CONTROL_EXPORTS
# define CONTROL_API __declspec(dllexport)
#else
# define CONTROL_API __declspec(dllimport)
#endif // CONTROL_EXPORTS

namespace ui
{

class CONTROL_API ColorButton
  : public wxWindow
{
public:
  ColorButton();
  ColorButton(wxWindow* parent,
              wxWindowID id,
              wxString const& label,
              wxColour const& color,
              wxPoint const& pos = wxDefaultPosition,
              wxSize const& size = wxDefaultSize);

  bool Create(wxWindow* parent,
              wxWindowID id,
              wxString const& label,
              wxColour const& color,
              wxPoint const& pos = wxDefaultPosition,
              wxSize const& size = wxDefaultSize);

  virtual bool SetBackgroundColour(wxColour const& colour) override;
  virtual bool SetForegroundColour(wxColour const& colour) override;

  virtual bool SetHoverBackgroundColour(wxColour const& colour);
  virtual bool SetHoverForegroundColour(wxColour const& colour);
protected:
  void Init();

  virtual wxSize DoGetBestSize() const;

  void OnPaint(wxPaintEvent&);
  void OnEnterMouse(wxMouseEvent&);
  void OnLeaveMouse(wxMouseEvent&);
  void OnLeftDown(wxMouseEvent&);
  void OnLeftUp(wxMouseEvent&);

  void DoPaint(wxDC& dc);
private:
  wxColour m_hoverForeColour;
  wxColour m_hoverBackColour;
  bool m_hover;
private:
  wxDECLARE_EVENT_TABLE();
};

} // namespace ui

#endif // __BUTTON_HPP__