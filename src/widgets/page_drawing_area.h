#ifndef TOWER_VIEWER_PAGE_DRAWING_AREA_H
#define TOWER_VIEWER_PAGE_DRAWING_AREA_H

#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include "../document/document.h"

class PageDrawingArea : public Gtk::DrawingArea {
 public:
  PageDrawingArea() = default;
  PageDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  PageDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, std::string filepath);
  ~PageDrawingArea() override = default;

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_focus_in_event(GdkEventFocus* focus_event) override;
  bool on_focus_out_event(GdkEventFocus* focus_event) override;
  bool on_key_press_event(GdkEventKey* key_event) override;
  Glib::RefPtr<Gtk::Builder> m_refGlade;
  Document *m_document;
};
#endif //TOWER_VIEWER_PAGE_DRAWING_AREA_H
