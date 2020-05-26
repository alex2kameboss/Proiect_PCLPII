/***************************************************************
 * Name:      Proiect_PCLPIIMain.h
 * Purpose:   Defines Application Frame
 * Author:    Alex (palexandru2000@gmail.com)
 * Created:   2020-04-09
 * Copyright: Alex ()
 * License:
 **************************************************************/

#ifndef PROIECT_PCLPII_MAINFRAME_H
#define PROIECT_PCLPII_MAINFRAME_H

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/listctrl.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size = wxDefaultSize);
    void putText(wxCommandEvent&);
    void putBackspace(wxCommandEvent&);
    void clear(wxCommandEvent&);
    void calc(wxCommandEvent&);
    void restore(wxListEvent&);

private:
    wxTextCtrl* m_textCtrl;
    wxPanel* mainPanel;
    wxBoxSizer* stack;
    wxListCtrl* history;
    wxDECLARE_EVENT_TABLE();
};

enum
{
    BUTTONS = wxID_HIGHEST + 1,
    BACKSPACE,
    CLEAR,
    CALCULATE,
    INPUTTEXT,
    RESTORE
};

#endif // PROIECT_PCLPIIMAIN_H
