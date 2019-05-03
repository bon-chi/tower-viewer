//
// Created by koji on 5/3/19.
//

#ifndef TOWER_VIEWER_PAGE_WINDOW_H
#define TOWER_VIEWER_PAGE_WINDOW_H

#include <gtkmm/builder.h>
#include <gtkmm/window.h>

class PageWindow : public Gtk::Window {
 public:
  PageWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  PageWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,
             std::string filepath);

 protected:
  Glib::RefPtr<Gtk::Builder> m_refGlade;
};

#endif  // TOWER_VIEWER_PAGE_WINDOW_H
