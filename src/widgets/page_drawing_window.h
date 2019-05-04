#ifndef TOWER_VIEWER_PAGEDRAWINGWINDOW_H
#define TOWER_VIEWER_PAGEDRAWINGWINDOW_H

#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>

class PageDrawingWindow : public Gtk::ScrolledWindow {
 public:
  PageDrawingWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

 protected:
  bool on_scroll_event(GdkEventScroll* scroll_event);
  bool on_key_press_event(GdkEventKey* key_event);
};



#endif //TOWER_VIEWER_PAGEDRAWINGWINDOW_H
