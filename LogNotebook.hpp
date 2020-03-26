#pragma once

#include <wx/notebook.h>

class LogNotebook : public wxNotebook
{
public:
    explicit LogNotebook(wxWindow* parent);
    ~LogNotebook();

private:
    void OnMouseEvent(wxMouseEvent &event);
};
