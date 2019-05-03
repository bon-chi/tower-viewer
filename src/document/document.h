#ifndef TOWER_VIEWER_DOCUMENT_H
#define TOWER_VIEWER_DOCUMENT_H

#include <poppler-document.h>
#include <poppler-image.h>
#include <poppler-page-renderer.h>
class Document {
 public:
  Document(std::string filepath);
  virtual ~Document() = default;
  void increment_page();
  void decrement_page();
  poppler::image image();
  std::string file_name();

 private:
  std::string m_filepath;
  poppler::document *m_document;
  poppler::page_renderer *m_renderer;
  unsigned int m_page_num;
};
#endif  // TOWER_VIEWER_DOCUMENT_H
