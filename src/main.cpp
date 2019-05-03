#include <gtkmm.h>
#include <iostream>
#include "document/document.h"
#include "widgets/page_drawing_area.h"
#include "widgets/page_window.h"

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "com.github.bon-chi.tower-viewer");

#ifdef RELEASE
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_resource("/com/github/bon-chi/tower-viewer/tower-viewer.glade");
#else
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("../resources/tower-viewer.glade");
#endif

  PageWindow* window = nullptr;
  builder->get_widget_derived("main-window", window, "../rulebook.pdf");

  PageDrawingArea* area = nullptr;
  builder->get_widget_derived("page-drawing-area", area, "../rulebook.pdf");

  return app->run(*window);
}
