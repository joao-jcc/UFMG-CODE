# ifndef MAIN_HPP
# define MAIN_HPP

#include "wx/wx.h"

class Main : public wxFrame {
    public:
        Main();
        ~Main();
    
    private:
        wxButton* mbutton1_;
        wxTextCtrl* mtext1_;
        wxListBox* mlist1_;

        void OnButtonClicked(wxCommandEvent& evt);

        wxDECLARE_EVENT_TABLE();
};


#endif