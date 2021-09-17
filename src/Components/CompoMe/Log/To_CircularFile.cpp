
#include "Components/CompoMe/Log/To_CircularFile.hpp"
#include "CompoMe/Log.hpp"
#include <algorithm>

namespace CompoMe {

namespace Log {

To_CircularFile::To_CircularFile()
    : CompoMe::Component() /* PROVIDE */, log(this) /* DATA */,
      path(
          /*WARNING NO DEFAULT VALUE FOR THIS TYPE*/),
      ligne_buff_size(50),
      current_position(0) {
  C_INFO_TAG("CONST: To_CircularFile", "Component,To_CircularFile");
  return;
}

//! Destructor
To_CircularFile::~To_CircularFile() noexcept {
  C_INFO_TAG("DEST: To_CircularFile", "Component,To_CircularFile");
  return;
}

/////////////////////////////////////////////////////////////////////////////
//                           COMPONENT_FUNCTIONS                           //
/////////////////////////////////////////////////////////////////////////////

void To_CircularFile::configuration() {
  Component::configuration();
  C_INFO_TAG("CONF: To_CircularFile", "Component,To_CircularFile");

  // configuration: sub_componentreturn;
}

void To_CircularFile::connection() {
  // connect: parent
  Component::connection();
  C_INFO_TAG("CONNECT: To_CircularFile", "Component,To_CircularFile");

  // connect: intern

  // connect: sub componentreturn;
}

void To_CircularFile::start() {
  // start: parent
  Component::start();
  C_INFO_TAG("START: To_CircularFile", "Component,To_CircularFile");
  if (this->get_path() == "") {
    char c[] = "/tmp/CompoMe_log_XXXXXX";
    this->set_path(mktemp(c));
  }

  C_INFO_TAG("LOG,FILE", "open file log: ", this->get_path());
  this->output.open(this->get_path());
  if (!this->output.is_open()) {
    C_ERROR_TAG("LOG,FILE", "Fail to open file");
    return;
  }

  C_TO_INFO(CompoMe::Require_helper<CompoMe::Log::Log_I>(this->get_lgo()),
            "Log open");
  // start: sub componentreturn;
}

void To_CircularFile::step() {
  // step: parent
  Component::step();
  C_INFO_TAG("STEP: To_CircularFile", "Component,To_CircularFile");
  this->output.flush();
  // step: receiver process// step: sub_componentreturn;
}

void To_CircularFile::stop() {
  // stop: parent
  Component::stop();
  // stop: sub_component
  C_INFO_TAG("STOP: To_CircularFile", "Component,To_CircularFile");

  this->output.close();
  return;
}

void To_CircularFile::status() {
  // status: parent
  Component::status();
  // status: sub_component
  C_INFO_TAG("STATUS: To_CircularFile", "Component,To_CircularFile");
  return;
}

/////////////////////////////////////////////////////////////////////////////
//                                INTERFACES                               //
/////////////////////////////////////////////////////////////////////////////

// // REQUIRE_LIST /////////////////////////////////////////////////////////////
//

} // namespace Log

} // namespace CompoMe
