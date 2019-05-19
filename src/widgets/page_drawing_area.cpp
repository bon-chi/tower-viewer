#include "page_drawing_area.h"
#include <gdkmm.h>
#include <poppler-image.h>
#include <iostream>

PageDrawingArea::PageDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::DrawingArea(cobject), m_refGlade(refGlade) {}

PageDrawingArea::PageDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath)
    : Gtk::DrawingArea(cobject), m_refGlade(refGlade) {
  this->m_document = new Document(filepath);
  this->add_events(Gdk::KEY_PRESS_MASK);
  this->add_events(Gdk::SCROLL_MASK);
  this->set_size_request(1000, 1000);
}

bool PageDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
#ifdef DEBUG
  std::cout << "redraw" << std::endl;
#endif
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  poppler::image img = this->m_document->image();
  auto* bar = (unsigned char*)(img.data());
  auto m_image = Gdk::Pixbuf::create_from_data(bar, Gdk::Colorspace::COLORSPACE_RGB, true, 8,
                                               img.width(), img.height(), img.bytes_per_row());
  Gdk::Cairo::set_source_pixbuf(cr, m_image, (width - m_image->get_width()) / 2.0,
                                (height - m_image->get_height()) / 2.0);
  cr->paint();

  std::cout << "pageDrawingArea width: " <<  this->get_allocation().get_width() << " height: " << this->get_allocation().get_height()  << std::endl;
  return true;
}

bool PageDrawingArea::on_scroll_event(GdkEventScroll* scroll_event) {
  switch(scroll_event->direction){
    case GDK_SCROLL_UP:
#ifdef DEBUG
      std::cout << "scroll up" << std::endl;
#endif
      break;
    case GDK_SCROLL_DOWN:
#ifdef DEBUG
      std::cout << "scroll down" << std::endl;
#endif
      break;
  }
  return false;
}

bool PageDrawingArea::on_focus_in_event(GdkEventFocus* focus_event) {
#ifdef DEBUG
  std::cout << "focus on" << std::endl;
#endif
  return true;
}
bool PageDrawingArea::on_focus_out_event(GdkEventFocus* focus_event) {
#ifdef DEBUG
  std::cout << "focus out" << std::endl;
#endif
  return true;
}
bool PageDrawingArea::on_key_press_event(GdkEventKey* key_event) {
  switch (key_event->keyval) {
    case GDK_KEY_Up:
#ifdef DEBUG
      std::cout << "up" << std::endl;
#endif
      this->m_document->decrement_page();
      break;
    case GDK_KEY_Down:
#ifdef DEBUG
      std::cout << "down" << std::endl;
#endif
      this->m_document->increment_page();
      break;
    case GDK_KEY_Right:
#ifdef DEBUG
      std::cout << "right" << std::endl;
#endif
      break;
    case GDK_KEY_Left:
#ifdef DEBUG
      std::cout << "left" << std::endl;
#endif
      break;
#ifdef DEBUG
    default:
      std::cout << "other" << std::endl;
#endif
  }
  this->queue_draw();
  return false;
}

