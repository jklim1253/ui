#include "control/colorbutton.hpp"
#include "util/util.hpp"

namespace ui
{

wxBEGIN_EVENT_TABLE(ColorButton, wxWindow)
  EVT_PAINT(ColorButton::OnPaint)
  EVT_ENTER_WINDOW(ColorButton::OnEnterMouse)
  EVT_LEAVE_WINDOW(ColorButton::OnLeaveMouse)
  EVT_LEFT_DOWN(ColorButton::OnLeftDown)
  EVT_LEFT_UP(ColorButton::OnLeftUp)
wxEND_EVENT_TABLE()

ColorButton::ColorButton()
{
  Init();
}
ColorButton::ColorButton(wxWindow* parent,
                         wxWindowID id,
                         wxString const& label,
                         wxColour const& color,
                         wxPoint const& pos,
                         wxSize const& size)
{
  Init();
  Create(parent, id, label, color, pos, size);
}
bool ColorButton::Create(wxWindow* parent,
                         wxWindowID id,
                         wxString const& label,
                         wxColour const& color,
                         wxPoint const& pos,
                         wxSize const& size)
{
  wxWindow::Create(parent, id, pos, size);
  SetLabel(label);
  SetBackgroundColour(color);

  return true;
}

bool ColorButton::SetBackgroundColour(wxColour const& colour)
{
  bool ret = wxWindow::SetBackgroundColour(colour);
  m_hoverBackColour = colour + 20;

  return ret;
}
bool ColorButton::SetForegroundColour(wxColour const& colour)
{
  bool ret =  wxWindow::SetForegroundColour(colour);
  m_hoverForeColour = colour;

  return ret;
}
bool ColorButton::SetHoverBackgroundColour(wxColour const& colour)
{
  m_hoverBackColour = colour;
  return true;
}
bool ColorButton::SetHoverForegroundColour(wxColour const& colour)
{
  m_hoverForeColour = colour;
  return true;
}
void ColorButton::Init()
{
  m_hover = false;
}
wxSize ColorButton::DoGetBestSize() const
{
  return wxWindow::DoGetBestSize();
}
void ColorButton::OnPaint(wxPaintEvent& e)
{
  wxPaintDC dc(this);
  DoPaint(dc);
}
void ColorButton::OnEnterMouse(wxMouseEvent& e)
{
  if (IsEnabled() && !m_hover)
  {
    m_hover = true;
    Refresh();
  }
}
void ColorButton::OnLeaveMouse(wxMouseEvent& e)
{
  if (m_hover)
  {
    m_hover = false;
    Refresh();
  }
}
void ColorButton::OnLeftDown(wxMouseEvent& e)
{
  SetFocus();
}
void ColorButton::OnLeftUp(wxMouseEvent& e)
{
  if (HasFocus())
  {
    wxCommandEvent clickEvent(wxEVT_BUTTON, GetId());
    clickEvent.SetEventObject(this);
    wxPostEvent(this, clickEvent);
  }
}
void ColorButton::DoPaint(wxDC& dc)
{
  if (m_hover)
  {
    dc.SetBackground(wxBrush(m_hoverBackColour));
    dc.SetTextForeground(m_hoverForeColour);
  }
  else
  {
    dc.SetBackground(wxBrush(GetBackgroundColour()));
    dc.SetTextForeground(GetForegroundColour());
  }
  dc.Clear();
  dc.SetFont(GetFont());

  wxPoint pt;
  wxSize client = GetClientSize();

  wxSize size = dc.GetTextExtent(GetLabel());
  dc.DrawText(GetLabel(), (client.x - size.x)/2, (client.y - size.y)/2);
}

} // namespace ui