#include <gtkmm.h>
#include <iostream>
#include "document/document.h"

class MyArea : public Gtk::DrawingArea {
 public:
  MyArea() = default;
  MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath);
  ~MyArea() override = default;

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_focus_in_event(GdkEventFocus* focus_event) override;
  bool on_focus_out_event(GdkEventFocus* focus_event) override;
  bool on_key_press_event(GdkEventKey* key_event) override;
  Glib::RefPtr<Gtk::Builder> m_refGlade;
  Document *m_document;
};

MyArea::MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::DrawingArea(cobject), m_refGlade(refGlade) {}
MyArea::MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath)
    : Gtk::DrawingArea(cobject), m_refGlade(refGlade) {
  this->m_document = new Document(filepath);
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
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

bool MyArea::on_focus_in_event(GdkEventFocus* focus_event) {
  std::cout << "focus on" << std::endl;
  return true;
}
bool MyArea::on_focus_out_event(GdkEventFocus* focus_event) {
  std::cout << "focus out" << std::endl;
  return true;
}
bool MyArea::on_key_press_event(GdkEventKey* key_event) {
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

class MyWindow : public Gtk::Window {
 public:
  MyWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
      : Gtk::Window(cobject), m_refGlade(refGlade) {
//    MyArea* area = nullptr;
//    refGlade->get_widget_derived("page-drawing-area", area);
  }
  MyWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath)
      : Gtk::Window(cobject), m_refGlade(refGlade) {
//    MyArea* area = nullptr;
//    refGlade->get_widget_derived("page-drawing-area", area);
    auto path_index = filepath.find_last_of("/") + 1;
    this->set_title(filepath.substr(path_index, filepath.size() - path_index));
  }

 protected:
  Glib::RefPtr<Gtk::Builder> m_refGlade;
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "com.github.bon-chi.tower-viewer");

#ifdef RELEASE
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_resource("/com/github/bon-chi/tower-viewer/tower-viewer.glade");
#else
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("../resources/tower-viewer.glade");
#endif
  //  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../tower-viewer.glade");

//  Gtk::Window* window2 = nullptr;
//  builder->get_widget("main-window", window2);
  MyWindow* window2 = nullptr;
  builder->get_widget_derived("main-window", window2, "../rulebook.pdf");
  MyArea* area = nullptr;
  builder->get_widget_derived("page-drawing-area", area, "../rulebook.pdf");

  //  MyWindow* window2 = nullptr;
  //  builder->get_widget_derived("main-window", window2);

  //  window2->add(*area);

  //  Gtk::Window window;
  //  MyArea drawingArea;
  //
  //  window.set_default_size(600, 900);
  //  window.add(drawingArea);
  //  drawingArea.show();

  //  return app->run(window);
  return app->run(*window2);
}
