
//#include "utils/resource.h"
#include <math.h>

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>
#include <cmath>
#include <csetjmp>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <functional>
#include <locale>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <time.h>

#include <unordered_map>
#include <unordered_set>

#include "canvas/canvas.hpp"

#include <gtkmm.h>
#include <epoxy/gl.h>
#include "canvas/selectable_ref.hpp"








class ExampleAppWindow;

class MyWindow : public Gtk::ApplicationWindow{

    public:
        MyWindow(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& refBuilder);

        void on_mouse_pressed(int n_press, double x, double y);
        void create();
        dune3d::Canvas *glwin= nullptr;


    protected:
        Glib::RefPtr<Gtk::Builder> m_refBuilder;
        Gtk::Box m_Box;
        //Example_GLArea glarea;

    private:
        Glib::RefPtr<Gtk::GestureClick> winclick;


};

class GtkApp : public Gtk::Application{

    protected:
        GtkApp();
        void on_startup() override;
        void on_activate() override;
        void pressed(int n_press, double x, double y);
        void bipclick();

    public:
        static Glib::RefPtr<GtkApp> create();
        dune3d::Canvas *glwin= nullptr;

    private:
        void create_window();
        Glib::RefPtr<Gtk::Builder> m_refBuilder;
        Glib::RefPtr<Gtk::GestureClick> winclick;
};