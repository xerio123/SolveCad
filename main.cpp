
//glib-compile-resources --target=resources.c --generate-source toolbar.gresource.xml

#include "application.h"
#include "resources.c"
#include <glm/glm.hpp>
#include "canvas/selectable_ref.hpp"
//#include <gtkmm/glarea.h>

using namespace Gtk;


namespace
{
std::map<unsigned int, Glib::ustring> mouse_buttons
{
  {0, "No button"},
  {GDK_BUTTON_PRIMARY, "Primary"},
  {GDK_BUTTON_MIDDLE, "Middle"},
  {GDK_BUTTON_SECONDARY, "Secondary"},
};
}




MyWindow::MyWindow(BaseObjectType* cobject,  const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::ApplicationWindow(cobject), m_refBuilder(refBuilder){

  Gtk::ApplicationWindow();

  //m_Box(Gtk::Orientation::VERTICAL);


  std::cout << "Windows init " << "bof"
    << ", "  << std::endl;
  Gtk::Label *lab = refBuilder->get_widget<Gtk::Label>("bap");
  lab->set_label("vroom");


  Gtk::Button *bip = refBuilder->get_widget<Gtk::Button>("bip");
  //connect à la methode d'un object (qui est moi même)
  bip->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::create));

  //glarea.set_transient_for(*this);
  //glarea.set_modal();
  //glarea.set_hide_on_close();

  //glwin = Gtk::Builder::get_widget_derived<dune3d::Canvas>(refBuilder, "GLArea");
  glwin = Gtk::make_managed<dune3d::Canvas>();
  Gtk::Box * modelisation_view = refBuilder->get_widget<Gtk::Box>("modelisation_view");
 



  modelisation_view->insert_child_at_start(*glwin);
  glwin->set_vexpand(true);
  glwin->set_hexpand(true);
  glwin->setup_controllers();


  glwin->set_chunk(0);

  glm::vec3 a(0.0f, 0.0f, 0.0f);
  glm::vec3 b(10.0f, 0.0f, 0.0f);
  glm::vec3 c(10.0f, 10.0f, 0.0f);
  glm::vec3 d(0.0f, 10.0f, 0.0f);


  glwin->draw_line(a,b);

  glwin->draw_line(b,c);

  glwin->draw_line(c,d);

  glwin->draw_line(d,a);


  //RESOURCE SHADER!!!!!
}



void MyWindow::create()
{
  std::cout << "Windows created " << "bof-----------"
    << ", "  << std::endl;
  
  dune3d::UUID pepe;
  pepe.random();
  float millis = 0.0;
  clock_t start, end;

  glm::vec3 a(0.0f, 0.0f, 0.0f);
  glm::vec3 b(10.0f, 0.0f, 0.0f);
  glm::vec3 c(10.0f, 10.0f, 0.0f);
  glm::vec3 d(0.0f, 10.0f, 0.0f);
  unsigned int i,e;
  start = clock();
  dune3d::Canvas::VertexRef tmp;
  dune3d::SelectableRef select;
  dune3d::SelectableRef2 select2;
  glwin->select_table_counter =0;
  for(i=0;i<1000;i++){

    for(e=0;e<1000;e++){
      a.x = a.x +15;
      b.x = b.x +15;
      c.x = c.x +15;
      d.x = d.x +15;
      //glwin->draw_line(a,b);

      //glwin->draw_line(b,c);

      //glwin->draw_line(c,d);

      //glwin->draw_line(d,a);

      
      tmp = glwin->draw_line(a,b);
      select = {dune3d::SelectableRef::Type::ENTITY, pepe, 0};


      //tmp = glwin->draw_line(b,c);
      //tmp = glwin->draw_line(c,d);
      //tmp = glwin->draw_line(d,a);
      //select2 = {dune3d::SelectableRef2::Type::ENTITY, pepe, &tmp};
      //glwin->add_selectable2(select2);

      //tmp = glwin->draw_line(b,c);
      //select = {dune3d::SelectableRef::Type::ENTITY, pepe, {tmp}};
      //glwin->add_selectable(select);

      //tmp = glwin->draw_line(c,d);
      //select = {dune3d::SelectableRef::Type::ENTITY, pepe, {tmp}};
      //glwin->add_selectable(select);

      //tmp = glwin->draw_line(d,a);
      //select = {dune3d::SelectableRef::Type::ENTITY, pepe, {tmp}};
      //glwin->add_selectable(select);
      //glwin->add_selectable(glwin->draw_point(a), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 0 });
      //glwin->add_selectable(glwin->draw_point(b), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 0 });

      //glwin->add_selectable(glwin->draw_line(b,c), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 1 });
      //glwin->add_selectable(glwin->draw_point(c), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 1 });

     //glwin->add_selectable(glwin->draw_line(c,d), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 2 });
      //glwin->add_selectable(glwin->draw_point(d), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 2 });

      //glwin->add_selectable(glwin->draw_line(d,a), dune3d::SelectableRef{dune3d::SelectableRef::Type::ENTITY, pepe, (i*4000)+e*4 + 3 });

    }
    a.x = 0;
    b.x = 10;
    c.x = 10;
    d.x = 0;
    a.y = a.y + 15;
    b.y = b.y +15;
    c.y = c.y +15;
    d.y = d.y +15;

  }
  end = clock();
  millis = (end-start) / 1000;
  printf("temps en millisecond :%f\n", millis);

  glwin->draw_line(d,a);
  glwin->request_push();




  //std::vector<void> er;


  }





void GtkApp::pressed(int n_press, double x, double y){
  const auto current_button = mouse_buttons[winclick->get_current_button()];
  std::cout << "Mouse pressed in app: " << current_button
    << ", " << n_press << ", " << x << ", " << y << std::endl;
}


void GtkApp::bipclick(){
  std::cout << "Mouse pressed in app: " << "bof"
    << ", "  << std::endl;
  

  
  
  

}

Glib::RefPtr<GtkApp> GtkApp::create(){
  return Glib::make_refptr_for_instance<GtkApp>(new GtkApp());
}

void GtkApp::on_startup(){
  Gtk::Application::on_startup();

  auto cssp = Gtk::CssProvider::create();
  cssp->load_from_resource("/org/SolveCad/SolveCad/window.css");
  Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), cssp, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  // Gtk::IconTheme::get_default()->add_resource_path("/org/horizon-eda/horizon/icons");
  Gtk::IconTheme::get_for_display(Gdk::Display::get_default())->add_resource_path("/org/SolveCad/SolveCad/icons");
  Gtk::Window::set_default_icon_name("dune3d");


}



GtkApp::GtkApp() : Gtk::Application("org.SolveCad.SolveCad") {
  
  Glib::set_application_name("SolveCad");
}

void GtkApp::on_activate(){
  
  //load la resource ui principale
  auto refBuilder = Gtk::Builder::create_from_resource("/org/SolveCad/SolveCad/window.ui");
  //cree windows depuis la windows dans le fichier UI puis fait derie cette windows vers mywindow
  auto window = Gtk::Builder::get_widget_derived<MyWindow>(refBuilder, "window");
 

  
 
  




  //winclick = Gtk::GestureClick::create();
  //winclick->set_button(0);
  //winclick->signal_pressed().connect( sigc::mem_fun(*this, &GtkApp::pressed));
  //window->add_controller(winclick);

  //Make sure that the application runs for as long this window is still open:
  add_window(*window);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  window->signal_hide().connect([window]() { delete window; });

  window->set_visible(true);
  window->show();
  //Gtk::Application::on_startup();
    Gtk::IconTheme::get_for_display(Gdk::Display::get_default())->add_resource_path("/org/SolveCad/icons");
    Gtk::Window::set_default_icon_name("dune3d");

  std::cout << "SolveCad loaded"<< std::endl;
}



int main(int argc, char* argv[])
{

auto app = GtkApp::create();

app->run(argc, argv);
  
//while(1){}
  return 0;
}