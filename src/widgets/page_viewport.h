//
// Created by koji on 5/4/19.
//

#ifndef TOWER_VIEWER_PAGE_VIEWPORT_H
#define TOWER_VIEWER_PAGE_VIEWPORT_H

#include <gtkmm/viewport.h>
#include <gtkmm/builder.h>

class PageViewPort : public Gtk::Viewport {
 public:
  PageViewPort(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

 protected:
  Glib::RefPtr<Gtk::Builder> m_refGlade;
  bool on_scroll_event(GdkEventScroll* scroll_event);
  bool on_key_press_event(GdkEventKey* key_event);
};



#endif //TOWER_VIEWER_PAGE_VIEWPORT_H
