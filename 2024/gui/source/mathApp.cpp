#include "mathApp.hpp"

wxIMPLEMENT_APP(mathApp);


mathApp::mathApp() : frame1_(nullptr) {

}

mathApp::~mathApp() {

}

bool mathApp::OnInit() {
    frame1_ = new Main();
    frame1_->Show();

    return true;
}