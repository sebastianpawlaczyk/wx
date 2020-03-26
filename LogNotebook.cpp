#include "LogNotebook.hpp"

LogNotebook::LogNotebook(wxWindow* parent)
    : wxNotebook(parent, wxID_ANY)
{
    Bind(wxEVT_MIDDLE_DOWN, &LogNotebook::OnMouseEvent, this);
}

LogNotebook::~LogNotebook() = default;

void LogNotebook::OnMouseEvent(wxMouseEvent &event)
{
    auto tabId = HitTest(event.GetPosition());
    DeletePage(tabId);
    event.Skip();
}
