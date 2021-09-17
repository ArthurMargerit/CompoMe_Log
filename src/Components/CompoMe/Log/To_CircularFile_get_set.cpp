#include "Components/CompoMe/Log/To_CircularFile.hpp"

namespace CompoMe {

namespace Log {

/////////////////////////////////////////////////////////////////////////////
//                                   PROVIDE                               //
/////////////////////////////////////////////////////////////////////////////

To_CircularFile_Log_I_log &To_CircularFile::get_log() { return this->log; }

/////////////////////////////////////////////////////////////////////////////
//                                   DATA                                  //
/////////////////////////////////////////////////////////////////////////////

// path
CompoMe::String To_CircularFile::get_path() const { return this->path; }

void To_CircularFile::set_path(const CompoMe::String &path) {
  this->path = path;
}

// ligne_buff_size
ui64 To_CircularFile::get_ligne_buff_size() const {
  return this->ligne_buff_size;
}

void To_CircularFile::set_ligne_buff_size(const ui64 &ligne_buff_size) {
  this->ligne_buff_size = ligne_buff_size;
}

// current_position
ui64 To_CircularFile::get_current_position() const {
  return this->current_position;
}

void To_CircularFile::set_current_position(const ui64 &current_position) {
  this->current_position = current_position;
}

/////////////////////////////////////////////////////////////////////////////
//                            SUB COMPONENT                                //
/////////////////////////////////////////////////////////////////////////////

} // namespace Log

} // namespace CompoMe
