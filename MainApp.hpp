#pragma once

#include <wx/app.h>

#include "Window.hpp"

class MainApp : public wxApp
{
public:
    MainApp();
    ~MainApp();

    virtual bool OnInit();

    static void Start(int argc, char** argv);

private:
    Window* window_;
};
