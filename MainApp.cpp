#include "MainApp.hpp"

MainApp::MainApp()
{}

MainApp::~MainApp() = default;

bool MainApp::OnInit()
{
    window_ = new Window();
    window_->Show(true);

    return true;
}

void MainApp::Start(int argc, char **argv)
{
    wxApp::SetInstance(new MainApp());
    wxEntryStart(argc, argv);

    wxTheApp->OnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
}
