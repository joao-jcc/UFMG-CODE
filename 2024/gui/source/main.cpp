#include "main.hpp"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
    EVT_BUTTON(0, Main::OnButtonClicked)
wxEND_EVENT_TABLE()

Main::Main() 
: wxFrame(nullptr, wxID_ANY, "The First Window", wxPoint(50, 50), wxSize(700, 500)),
  mbutton1_( new wxButton(this, 0, "Click Me", wxPoint(20, 20), wxSize(150, 50)) ), 
  mtext1_( new wxTextCtrl(this, wxID_ANY, "Search", wxPoint(20, 90), wxSize(300, 30)) ), 
  mlist1_( new wxListBox(this, wxID_ANY, wxPoint(20, 140), wxSize(300, 300) ) ) {

}

Main::~Main() {
}

void Main::OnButtonClicked(wxCommandEvent& evt) {
    mlist1_->AppendString(mtext1_->GetValue());
    evt.Skip();
}