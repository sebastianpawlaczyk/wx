#include "Window.hpp"

#include <wx/aboutdlg.h>
#include <wx/artprov.h>
#include <wx/icon.h>
#include <wx/menuitem.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/textdlg.h>

#define MY_APP_VERSION_STRING "1.0"

Window::Window()
    : wxMDIParentFrame(nullptr, 20004, "GrepTerminator", wxPoint(30,30), wxSize(800, 600))
    , menuBar_(new wxMenuBar())
{
    this->SetMenuBar(menuBar_);

/////////// FILE MENU ~START ///////////
    auto* menuFile = new wxMenu();

    auto* openItem = new wxMenuItem(menuFile, wxID_OPEN);
    menuFile->Append(openItem);
    Bind(wxEVT_MENU, &Window::OnMenuOpen, this, wxID_OPEN);

    auto* saveItem = new wxMenuItem(menuFile, wxID_SAVE);
    menuFile->Append(saveItem);

    menuFile->AppendSeparator();

    auto* exitItem = new wxMenuItem(menuFile, wxID_EXIT);
    menuFile->Append(exitItem);
    Bind(wxEVT_MENU, &Window::OnMenuExit, this, wxID_EXIT);

    menuBar_->Append(menuFile, "File");
/////////// FILE MENU ~END ///////////

/////////// FIND MENU ~START ///////////
    auto* menuFind = new wxMenu();

    auto* grepItem = new wxMenuItem(menuFind, 20001, wxT("&Grep\tCtrl+G"));
    menuFind->Append(grepItem);
    Bind(wxEVT_MENU, &Window::OnMenuGrep, this, 20001);

    menuBar_->Append(menuFind, "Find");
/////////// FIND MENU ~END ///////////

/////////// HELP MENU ~Start ///////////
    auto* menuHelp = new wxMenu();

    auto* aboutItem = new wxMenuItem(menuHelp, wxID_ABOUT);
    //aboutItem->SetBitmap(wxArtProvider::GetBitmap(wxART_QUESTION)); // Bug in wxWidget
    menuHelp->Append(aboutItem);
    Bind(wxEVT_MENU, &Window::OnMenuHelp, this, wxID_ABOUT);

    menuBar_->Append(menuHelp, "Help");
/////////// HELP MENU ~END ///////////
}

Window::~Window()
{}

void Window::OnMenuOpen(wxCommandEvent &event)
{
    if (notebook_ == nullptr)
    {
        initializeNotebook();
    }

    wxFileDialog fileDialog(this, "Open", "", "", ".txt Files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialog.ShowModal() == wxID_OK)
    {
        auto *textCtrl = new wxTextCtrl(
                notebook_, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                wxTE_MULTILINE | wxTE_READONLY, wxDefaultValidator, wxTextCtrlNameStr);
        textCtrl->SetDefaultStyle(wxTextAttr(*wxWHITE, *wxWHITE));
        textCtrl->SetBackgroundColour((255, 23, 23));
        textCtrl->LoadFile(fileDialog.GetPath());
        notebook_->AddPage(textCtrl, fileDialog.GetFilename());
    }

    event.Skip();
}

void Window::OnMenuSave(wxCommandEvent& event)
{
    event.Skip();
}

void Window::OnMenuExit(wxCommandEvent &event)
{
    Close();
    event.Skip();
}

void Window::OnMenuGrep(wxCommandEvent& event)
{
    std::cout << "DUPSON" << std::endl;
    wxTextEntryDialog dlg(this, "fas");
    dlg.SetTextValidator(wxFILTER_ALPHA);
    if ( dlg.ShowModal() == wxID_OK )
    {
        wxString value = dlg.GetValue();
        std::cout << value << std::endl;
    }
    auto a = system("grep config CMakeCache.txt");
    std::cout << a << std::endl;
    //wxTextCtrl* text = dynamic_cast<wxTextCtrl*>(notebook_->GetPage(tab_));
    //std::cout << text->GetLineText(0) << std::endl;
    event.Skip();
}

void Window::OnMenuHelp(wxCommandEvent &event)
{
    wxAboutDialogInfo aboutInfo;
    wxIcon icon;
    icon.CopyFromBitmap(wxArtProvider::GetBitmap("wxART_QUIT"));

    aboutInfo.SetName("GrepTerminator");
    aboutInfo.SetVersion(MY_APP_VERSION_STRING);
    aboutInfo.SetDescription(_("GrepTerminator is dedicated to handle log floods"));
    aboutInfo.SetCopyright("(C) 2020-now");
    aboutInfo.SetWebSite("https://github.com/sebastianpawlaczyk");
    aboutInfo.AddDeveloper("Sebastian Pawlaczyk");
    aboutInfo.AddDeveloper("spawlaczyk97@gmail.com");
    aboutInfo.SetIcon(icon);

    wxAboutBox(aboutInfo, this);

    event.Skip();
}

void Window::initializeNotebook()
{
    auto* panel = new wxPanel(this, wxID_ANY);
    notebook_ = new LogNotebook(panel);

    notebook_->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &Window::OnTabChanged, this, wxID_ANY);

    auto* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(notebook_, 1, wxEXPAND);
    panel->SetSizer(panelSizer);

    auto* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->SetMinSize(250, 100);
    topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(topSizer);
}

void Window::OnTabChanged(wxNotebookEvent& event)
{
    tab_ = event.GetSelection();
    std::cout << tab_ << std::endl;
    event.Skip();
}
