
#include "page_drawing_window.h"
#include <gtkmm/adjustment.h>
#include <iostream>

PageDrawingWindow::PageDrawingWindow(BaseObjectType* cobject,
                                     const Glib::RefPtr<Gtk::Builder>& refGlade){
  this->add_events(Gdk::SCROLL_MASK);
  this->add_events(Gdk::KEY_PRESS_MASK);
  auto h = this->get_hadjustment()->get_value();
  std::cout << "---------------------------------------------scroll_value: " << h << std::endl;
}

bool PageDrawingWindow::on_scroll_event(GdkEventScroll* scroll_event) {
//  auto h = get_hadjustment()->gobj();
  auto h = this->get_hadjustment()->get_value();
  std::cout << "---------------------------------------------scroll_value: " << h << std::endl;
//  switch(scroll_event->direction){
//    case GDK_SCROLL_UP:
//      std::cout << "" << std::endl;
//      break;
//    case GDK_SCROLL_DOWN:
//      std::cout << "scroll down" << std::endl;
//      break;
//  }
  return false;
}

bool PageDrawingWindow::on_key_press_event(GdkEventKey* key_event) {
  std::cout << "---------key pressedk------------------" << std::endl;
  return false;
}
