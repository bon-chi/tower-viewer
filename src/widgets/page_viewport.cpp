//
// Created by koji on 5/4/19.
//

#include "page_viewport.h"
#include <iostream>

PageViewPort::PageViewPort(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Viewport(cobject), m_refGlade(refGlade) {
  this->add_events(Gdk::SCROLL_MASK);
  this->add_events(Gdk::KEY_PRESS_MASK);
}

bool PageViewPort::on_scroll_event(GdkEventScroll* scroll_event) {
  auto h = this->get_hadjustment()->get_value();
  std::cout << "----------------------viewprot scroll " << h <<std::endl;
  return false;
}

bool PageViewPort::on_key_press_event(GdkEventKey* key_event) {
  auto adj = this->get_hadjustment();
  auto step = adj->get_step_increment();
  std::cout << "viewport key pressed, increment: " << step << std::endl;
  switch (key_event->keyval) {
    case GDK_KEY_Right:
      adj->set_value(adj->get_value() + step);
      std::cout << "right" << std::endl;
      break;
    case GDK_KEY_Left:
      if (adj->get_value() < step) {
        adj->set_value(0);
      } else {
        adj->set_value(adj->get_value() - step);
      }
      std::cout << "left" << std::endl;
      break;
    default:
      std::cout << "other" << std::endl;
  }
  return false;
}
