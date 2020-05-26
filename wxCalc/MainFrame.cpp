/***************************************************************
 * Name:      Proiect_PCLPIIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alex (palexandru2000@gmail.com)
 * Created:   2020-04-09
 * Copyright: Alex ()
 * License:
 **************************************************************/

#include <string>
#include <fstream>

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#include "MainFrame.h"

char* e;
wxString nr[] = { "7","8","9","/","<-","4","5","6","*","C","1","2","3","-","(","0",".","=","+",")" };
std::string allowedChar = "1234567890/*-+().";

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame((wxFrame*)NULL, -1, title, pos, size, wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER ^ wxMAXIMIZE_BOX)
{
    mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    stack = new wxBoxSizer(wxVERTICAL);

    m_textCtrl = new wxTextCtrl(mainPanel, INPUTTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    wxFont myFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    m_textCtrl->SetFont(myFont);

    history = new wxListCtrl(mainPanel, RESTORE, wxDefaultPosition, wxSize(-1, 100), wxLC_NO_HEADER | wxLC_REPORT);

    wxFont myFont1(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    history->InsertColumn(0, "Equation", wxLIST_FORMAT_LEFT, 300);
    history->InsertColumn(1, "Result", wxLIST_FORMAT_RIGHT, 110);
    history->SetFont(myFont1);

    stack->Add(history, 0, wxALL | wxEXPAND, 5);
    stack->Add(m_textCtrl, 0, wxALL | wxEXPAND, 5);

    wxBoxSizer* btnLine;
    for (int i = 0; i < 4; ++i) {
        btnLine = new wxBoxSizer(wxHORIZONTAL);
        for (int j = 0; j < 5; ++j) {
            int id = BUTTONS;
            if (nr[i * 5 + j] == "<-")
                id = BACKSPACE;
            else if (nr[i * 5 + j] == "C")
                id = CLEAR;
            else if (nr[i * 5 + j] == "=")
                id = CALCULATE;
            btnLine->Add(new wxButton(mainPanel, id, nr[i * 5 + j]), 1, wxALL | wxEXPAND, 5);
        }
        stack->Add(btnLine);
    }

    mainPanel->SetSizer(stack);

    CreateStatusBar();
    SetStatusText("Welcome to Calculator!");
}

void MainFrame::putText(wxCommandEvent& event)
{
    wxButton* pButton = wxDynamicCast(event.GetEventObject(), wxButton);
    wxString sLabel = pButton->GetLabel();
    *m_textCtrl << sLabel;
}

void MainFrame::putBackspace(wxCommandEvent& event)
{
    if (m_textCtrl->GetLineLength(0))
        m_textCtrl->Remove(m_textCtrl->GetLineLength(0) - 1, m_textCtrl->GetLineLength(0));
}

void MainFrame::clear(wxCommandEvent& event)
{
    m_textCtrl->Clear();
}

double operatie(char op, double st, double dr) {
    if (op == '+')
        return st + dr;
    else if (op == '-')
        return st - dr;
    else if (op == '*')
        return st * dr;
    return st / dr;
}

int caut(int st, int dr, char s1, char s2) {
    int p = 0;
    for (int i = dr;i >= st;--i) {
        if (e[i] == ')')
            --p;
        else if (e[i] == '(')
            ++p;
        else if ((e[i] == s1 || e[i] == s2) && p == 0)
            return i;
    }
    return -1;
}

double numar(int st, int dr) {
    wxString val;
    double ret;
    for (int i = st;i <= dr;++i)
        val += e[i];
    val.ToDouble(&ret);
    return ret;
}

double evaluare(int st, int dr) {
    if (st > dr)
        return 0;
    int p = caut(st, dr, '+', '-');
    if (p != -1)
        return operatie(e[p], evaluare(st, p - 1), evaluare(p + 1, dr));
    p = caut(st, dr, '*', '/');
    if (p != -1)
        return operatie(e[p], evaluare(st, p - 1), evaluare(p + 1, dr));
    if (e[st] == '(' && e[dr] == ')')
        return evaluare(st + 1, dr - 1);
    return numar(st, dr);
}

void MainFrame::calc(wxCommandEvent& event) {
    if (!m_textCtrl->GetLineLength(0))
        return;

    e = new char[m_textCtrl->GetLineLength(0)];
    wxString loc = m_textCtrl->GetLineText(0);

    if (loc[0] == '*' || loc[0] == '/') {
        SetStatusText("Wrong input format");
        return;
    }

    int k = 0, p = 0;
    for (int i = 0; i < loc.length(); ++i) {
        if (allowedChar.find(loc[i]) == -1) {
            SetStatusText("Wrong input format");
            return;
        }
        if (loc[i] != ' ')
            e[k++] = loc[i];
        if (loc[i] == '(')
            p++;
        else if (loc[i] == ')')
            p--;
    }
    if (p != 0) {
        SetStatusText("Wrong input format");
        return;
    }
    else if (loc.Last() == '+' || loc.Last() == '-' || loc.Last() == '*' || loc.Last() == '/') {
        SetStatusText("Wrong input format");
        return;
    }

    double rez = evaluare(0, loc.length() - 1);
    delete[] e;

    wxString val = "Result is: ";
    val << rez;
    SetStatusText(val);

    wxString sRez;
    sRez << rez;
    m_textCtrl->Clear();
    *m_textCtrl << sRez;

    sRez = "=" + sRez;
    long itemIndex = history->InsertItem(0, loc);
    history->SetItem(itemIndex, 1, sRez);
}

void MainFrame::restore(wxListEvent& event) {
    m_textCtrl->Clear();
    *m_textCtrl << event.GetText();
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(BUTTONS, MainFrame::putText)
EVT_BUTTON(BACKSPACE, MainFrame::putBackspace)
EVT_BUTTON(CLEAR, MainFrame::clear)
EVT_BUTTON(CALCULATE, MainFrame::calc)
EVT_TEXT_ENTER(INPUTTEXT, MainFrame::calc)
EVT_LIST_ITEM_SELECTED(RESTORE, MainFrame::restore)
wxEND_EVENT_TABLE()

