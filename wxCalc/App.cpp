/***************************************************************
 * Name:      Proiect_PCLPIIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Alex (palexandru2000@gmail.com)
 * Created:   2020-04-09
 * Copyright: Alex ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#include "App.h"
#include "MainFrame.h"

#define xx 450

#if defined(unix) || defined(__unix__) || defined(__unix)
#define yy 370
#endif

#ifndef yy
#define yy 350
#endif

IMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* frame = new MainFrame("wxCalculator", wxPoint(50, 50), wxSize(xx, yy));
    frame->Show(true);

    return true;
}
