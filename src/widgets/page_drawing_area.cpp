#include "page_drawing_area.h"
#include <gdkmm.h>
#include <poppler-image.h>
#include <iostream>

PageDrawingArea::PageDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::DrawingArea(cobject), m_refGlade(refGlade) {}

PageDrawingArea::PageDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath)
    : Gtk::DrawingArea(cobject), m_refGlade(refGlade) {
  this->m_document = new Document(filepath);
  this->add_events(Gdk::SCROLL_MASK);
}

bool PageDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  std::cout << "redraw" << std::endl;
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

  return true;
}

bool PageDrawingArea::on_scroll_event(GdkEventScroll* scroll_event) {
  switch(scroll_event->direction){
    case GDK_SCROLL_UP:
      std::cout << "scroll up" << std::endl;
      break;
    case GDK_SCROLL_DOWN:
      std::cout << "scroll down" << std::endl;
      break;
  }
  return true;
}

bool PageDrawingArea::on_focus_in_event(GdkEventFocus* focus_event) {
  std::cout << "focus on" << std::endl;
  return true;
}
bool PageDrawingArea::on_focus_out_event(GdkEventFocus* focus_event) {
  std::cout << "focus out" << std::endl;
  return true;
}
bool PageDrawingArea::on_key_press_event(GdkEventKey* key_event) {
  switch (key_event->keyval) {
    case GDK_KEY_Up:
      std::cout << "up" << std::endl;
      this->m_document->decrement_page();
      break;
    case GDK_KEY_Down:
      std::cout << "down" << std::endl;
      this->m_document->increment_page();
      break;
    case GDK_KEY_Right:
      std::cout << "right" << std::endl;
      break;
    case GDK_KEY_Left:
      std::cout << "left" << std::endl;
      break;
    default:
      std::cout << "other" << std::endl;
  }
  this->queue_draw();
  return true;
}

