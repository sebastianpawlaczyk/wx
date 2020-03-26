# pragma once

#include <wx/menu.h>
#include <wx/mdi.h>

#include "LogNotebook.hpp"

class Window : public wxMDIParentFrame
{
public:
    Window();
    ~Window();

private:
    void initializeNotebook();

    void OnMenuOpen(wxCommandEvent& event);
    void OnMenuSave(wxCommandEvent& event);
    void OnMenuExit(wxCommandEvent& event);

    void OnMenuGrep(wxCommandEvent& event);

    void OnMenuHelp(wxCommandEvent& event);

    void OnTabChanged(wxNotebookEvent& event);

    wxMenuBar* menuBar_;
    LogNotebook* notebook_;
    uint32_t tab_;
};
