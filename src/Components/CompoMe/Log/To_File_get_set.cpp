#include "Components/CompoMe/Log/To_File.hpp"

namespace CompoMe {

namespace Log {

/////////////////////////////////////////////////////////////////////////////
//                                   PROVIDE                               //
/////////////////////////////////////////////////////////////////////////////

To_File_Log_I_log &To_File::get_log() { return this->log; }

/////////////////////////////////////////////////////////////////////////////
//                                   DATA                                  //
/////////////////////////////////////////////////////////////////////////////

// path
CompoMe::String To_File::get_path() const { return this->path; }

void To_File::set_path(const CompoMe::String &path) { this->path = path; }

/////////////////////////////////////////////////////////////////////////////
//                            SUB COMPONENT                                //
/////////////////////////////////////////////////////////////////////////////

} // namespace Log

} // namespace CompoMe
