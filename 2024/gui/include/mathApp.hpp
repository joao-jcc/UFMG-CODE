#ifndef MATH_APP_HPP
#define MATH_APP_HPP

#include "wx/wx.h"
#include "main.hpp"


class mathApp : public wxApp {
    public:
        mathApp();
        ~mathApp();
    
    public:
        virtual bool OnInit();

    private:
        Main* frame1_;

};


#endif