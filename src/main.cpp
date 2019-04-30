#include <gtkmm.h>

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "com.github.bon-chi.tower-viewer");

  Gtk::Window window;

  window.set_default_size(600, 900);

  return app->run(window);
}

