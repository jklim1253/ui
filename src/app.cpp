#include <wx/wx.h>
#include "control/colorbutton.hpp"
#include "util/util.hpp"

namespace App
{

enum timer_id
{
  timer_clock = 1,
};

class Main
  : public wxApp
{
public:
  bool OnInit() override;
};

} // namespace App

DECLARE_APP(App::Main);

namespace Theme
{

enum order
{
  workspace = 0,
  sidebar,
  titlebar,
  button_fg,
  button_bg,
};

namespace basic
{
static const char* const color[] = {
  "#193549",
  "#122738",
  "#15232D",
  "#FFFFFF",
  "#000000"
};
} // namespace basic

} // namespace Theme

namespace Panel
{

class Titlebar
  : public wxPanel
{
  wxButton* button_max;
  wxTimer timer;
public:
  Titlebar(wxWindow* parent,
           wxWindowID id = wxID_ANY,
           wxSize const& size = wxDefaultSize)
    : wxPanel(parent, id, wxDefaultPosition, size)
    , timer(this, App::timer_clock)
  {
    SetBackgroundColour(Theme::basic::color[Theme::titlebar]);

    wxFont iconFont(10,
                    wxFONTFAMILY_DEFAULT,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_NORMAL,
                    false,
                    wxT("Segoe MDL2 Assets"));

    wxFont textFont(12,
                    wxFONTFAMILY_DEFAULT,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_NORMAL,
                    false,
                    wxT("Consolas"));

    wxStaticText* text_where = new wxStaticText(this, wxID_ANY, wxT("/"),
                                                wxDefaultPosition,
                                                wxSize(150, -1),
                                                wxCLIP_CHILDREN | wxALIGN_LEFT
#ifdef _DEBUG
                                                 | wxBORDER
#endif // _DEBUG                                                 
                                                 );
    text_where->SetFont(textFont);
    text_where->SetForegroundColour(Theme::basic::color[Theme::button_fg]);
    text_where->SetBackgroundColour(Theme::basic::color[Theme::titlebar]);
    // wxStaticText* text_title = new wxStaticText(this, wxID_ANY, wxT("UI"),
    //                                               wxDefaultPosition,
    //                                               wxSize(-1, -1),
    //                                               wxCLIP_CHILDREN | wxALIGN_CENTER_HORIZONTAL | wxBORDER);
    // text_title->SetFont(textFont);
    // text_title->SetForegroundColour(Theme::basic::color[Theme::button_fg]);
    // text_title->SetBackgroundColour(Theme::basic::color[Theme::titlebar]);
    wxButton* button_min = new wxButton(this, wxID_ANY, L"\uE921", wxDefaultPosition, wxSize{50, 50}, wxNO_BORDER | wxCLIP_CHILDREN);
    button_min->SetFont(iconFont);
    button_min->SetForegroundColour(Theme::basic::color[Theme::button_fg]);
    button_min->SetBackgroundColour(Theme::basic::color[Theme::titlebar]);
    button_max = new wxButton(this, wxID_ANY, L"\uE922", wxDefaultPosition, wxSize{50, 50}, wxNO_BORDER | wxCLIP_CHILDREN);
    button_max->SetFont(iconFont);
    button_max->SetForegroundColour(Theme::basic::color[Theme::button_fg]);
    button_max->SetBackgroundColour(Theme::basic::color[Theme::titlebar]);
    wxButton* button_close = new wxButton(this, wxID_ANY, L"\uE8BB", wxDefaultPosition, wxSize{50, 50}, wxNO_BORDER | wxCLIP_CHILDREN);
    button_close->SetFont(iconFont);
    button_close->SetForegroundColour(Theme::basic::color[Theme::button_fg]);
    button_close->SetBackgroundColour(Theme::basic::color[Theme::titlebar]);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    {
      wxBoxSizer* where_sizer = new wxBoxSizer(wxVERTICAL);
      {
        where_sizer->AddStretchSpacer();
        where_sizer->Add(text_where);
        where_sizer->AddStretchSpacer();
      }
      sizer->Add(where_sizer, 0, wxEXPAND);
      sizer->AddStretchSpacer(1);
      sizer->Add(button_min);
      sizer->Add(button_max);
      sizer->Add(button_close);
    }
    SetSizer(sizer);
    Layout();

    Bind(wxEVT_BUTTON, &Titlebar::OnMinimize, this, button_min->GetId());
    Bind(wxEVT_BUTTON, &Titlebar::OnMaximize, this, button_max->GetId());
    Bind(wxEVT_BUTTON, &Titlebar::OnClose, this, button_close->GetId());
    Bind(wxEVT_LEFT_DOWN, &Titlebar::OnLeftDown, this, GetId());
    Bind(wxEVT_LEFT_UP, &Titlebar::OnLeftUp, this, GetId());
    Bind(wxEVT_MOTION, &Titlebar::OnMotion, this, GetId());
    Bind(wxEVT_PAINT, &Titlebar::OnPaint, this, GetId());
    Bind(wxEVT_TIMER, &Titlebar::OnTimer, this);

    timer.Start(500);
  }
  void OnMinimize(wxCommandEvent& e)
  {
    wxFrame* frame = (wxFrame*)wxGetApp().GetTopWindow();
    if (frame->IsIconized())
    {
      frame->Restore();
    }
    else
    {
      frame->Iconize();
    }
  }
  void OnMaximize(wxCommandEvent& e)
  {
    wxFrame* frame = (wxFrame*)wxGetApp().GetTopWindow();
    if (frame->IsMaximized())
    {
      button_max->SetLabel(L"\uE922");
      frame->Restore();
    }
    else
    {
      button_max->SetLabel(L"\uE923");
      frame->Maximize();
    }
  }
  void OnClose(wxCommandEvent& e)
  {
    ((wxFrame*)wxGetApp().GetTopWindow())->Close();
  }

  //////////////////////////////////////////////////////////////////////////////
  // Windows Movement
  //////////////////////////////////////////////////////////////////////////////
  wxPoint ptDiff;
  void OnLeftDown(wxMouseEvent& e)
  {
    wxFrame* frame = (wxFrame*)wxGetApp().GetTopWindow();
    if (frame->IsMaximized())
      return;

    CaptureMouse();
    ptDiff = (wxGetMousePosition() - frame->GetPosition());
  }
  void OnLeftUp(wxMouseEvent& e)
  {
    if (HasCapture())
      ReleaseMouse();
  }
  void OnMotion(wxMouseEvent& e)
  {
    if (!HasCapture())
      return;

    wxFrame* frame = (wxFrame*)wxGetApp().GetTopWindow();
    frame->Move(wxGetMousePosition() - ptDiff);
  }
  //////////////////////////////////////////////////////////////////////////////
  // Title Paint
  //////////////////////////////////////////////////////////////////////////////
  void OnPaint(wxPaintEvent& e)
  {
    wxPaintDC dc(this);
    render(dc);
  }
  void OnTimer(wxTimerEvent& e)
  {
    paint();
  }
  void paint()
  {
    wxClientDC dc(this);
    render(dc);
  }
  void render(wxDC& dc)
  {
    wxFont textFont(13,
                    wxFONTFAMILY_DEFAULT,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_NORMAL,
                    false,
                    wxT("Consolas"));

    dc.SetBackground(wxBrush(Theme::basic::color[Theme::titlebar]));
    dc.SetTextForeground(Theme::basic::color[Theme::button_fg]);
    dc.Clear();
    wxString now = wxString::Format(wxT("UI [%s]"), wxDateTime::Now().Format("%F %T"));
    wxSize client = GetClientSize();
    wxSize size{0,0};
    dc.GetTextExtent(now, &size.x, &size.y, nullptr, nullptr, &textFont);
    dc.DrawText(now, (client.x - size.x)/2, (client.y - size.y)/2);
  }
};

class Sidebar
  : public wxPanel
{
public:
  Sidebar(wxWindow* parent,
          wxWindowID id = wxID_ANY,
          wxSize const& size = wxDefaultSize)
    : wxPanel(parent, id, wxDefaultPosition, size)
  {
    SetBackgroundColour(Theme::basic::color[Theme::sidebar]);

    ui::ColorButton* button = new ui::ColorButton(this, wxID_ANY, wxT("Hello"), Theme::basic::color[Theme::sidebar], wxDefaultPosition, wxSize{-1, 50});
    button->SetForegroundColour("#717D88");
    button->SetHoverBackgroundColour(wxColour(Theme::basic::color[Theme::sidebar]) - 10);
    button->SetHoverForegroundColour("#FFFFFF");
    ui::ColorButton* button2 = new ui::ColorButton(this, wxID_ANY, wxT("World"), Theme::basic::color[Theme::sidebar], wxDefaultPosition, wxSize{-1, 50});
    button2->SetForegroundColour("#717D88");
    button2->SetHoverBackgroundColour(wxColour(Theme::basic::color[Theme::sidebar]) - 10);
    button2->SetHoverForegroundColour("#FFFFFF");

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    {
      sizer->Add(button, 0, wxEXPAND | wxALL, 1);
      sizer->Add(button2, 0, wxEXPAND | wxALL, 1);
    }

    SetSizer(sizer);
    Layout();

    Bind(wxEVT_BUTTON, &Sidebar::OnButton, this, button->GetId());
    Bind(wxEVT_BUTTON, &Sidebar::OnButton, this, button2->GetId());
  }
  void OnButton(wxCommandEvent& e)
  {
    wxString msg = wxString::Format(wxT("%s is clicked"), ((wxWindow*)e.GetEventObject())->GetLabel());
    wxMessageBox(msg, wxT("Check"));
  }
};

class Workspace
  : public wxPanel
{
public:
  Workspace(wxWindow* parent,
            wxWindowID id = wxID_ANY,
            wxSize const& size = wxDefaultSize)
    : wxPanel(parent, id, wxDefaultPosition, size)
  {
    SetBackgroundColour(Theme::basic::color[Theme::workspace]);
  }
};

} // namespace Panel

namespace Frame
{

class Main
  : public wxFrame
{
public:
  Main(wxString const& title,
          wxPoint const& pos = wxDefaultPosition,
          wxSize const& size = wxDefaultSize,
          long style = wxDEFAULT_FRAME_STYLE)
    : wxFrame(nullptr, wxID_ANY, title, pos, size, style)
  {
    wxBoxSizer* side_sizer = new wxBoxSizer(wxHORIZONTAL);
    {
      wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
      {
        top_sizer->Add(new Panel::Titlebar(this, wxID_ANY, wxSize{-1, 35}), 0, wxEXPAND);
        top_sizer->Add(new Panel::Workspace(this, wxID_ANY), 1, wxEXPAND);
      }

      side_sizer->Add(new Panel::Sidebar(this, wxID_ANY, wxSize{50, -1}), 0, wxEXPAND);
      side_sizer->Add(top_sizer, 1, wxEXPAND);
    }
    SetSizer(side_sizer);
    Layout();

    Bind(wxEVT_CLOSE_WINDOW, &Main::OnClose, this);
  }
  void OnClose(wxCloseEvent& e)
  {
    e.Skip();
  }
};

} // namespace Frame

// wxGetApp()
IMPLEMENT_APP(App::Main);
namespace App
{

bool Main::OnInit()
{
  wxInitAllImageHandlers();

  Frame::Main* frame = new Frame::Main("UI",
                                       wxPoint{100, 100},
                                       wxSize{800, 600},
                                       wxCLIP_CHILDREN | wxBORDER);
  frame->SetMinSize(wxSize{800, 600});
  frame->Show();
  return true;
}

} // namespace App
