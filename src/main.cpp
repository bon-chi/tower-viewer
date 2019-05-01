#include <gtkmm.h>
#include <poppler-document.h>
#include <poppler-page-renderer.h>

class MyArea : public Gtk::DrawingArea {
 public:
  MyArea();
  virtual ~MyArea();

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

MyArea::MyArea() {}

MyArea::~MyArea() {}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  auto document = poppler::document::load_from_file("../rulebook.pdf");
  auto page = document->create_page(0);
  poppler::page_renderer renderer;
  poppler::image img = renderer.render_page(page);
  auto* bar = (guint8*)(unsigned char*)(img.data());
  auto m_image = Gdk::Pixbuf::create_from_data(bar, Gdk::Colorspace::COLORSPACE_RGB, true, 8,
                                               img.width(), img.height(), img.bytes_per_row());
  Gdk::Cairo::set_source_pixbuf(cr, m_image, (width - m_image->get_width()) / 2,
                                (height - m_image->get_height()) / 2);
  cr->paint();

  return true;
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "com.github.bon-chi.tower-viewer");

  Gtk::Window window;
  MyArea drawingArea;

  window.set_default_size(600, 900);
  window.add(drawingArea);
  drawingArea.show();

  return app->run(window);
}

