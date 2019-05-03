#include "page_window.h"

PageWindow::PageWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject), m_refGlade(refGlade) {
}

PageWindow::PageWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath)
: Gtk::Window(cobject), m_refGlade(refGlade) {
  auto path_index = filepath.find_last_of("/") + 1;
  this->set_title(filepath.substr(path_index, filepath.size() - path_index));
}
