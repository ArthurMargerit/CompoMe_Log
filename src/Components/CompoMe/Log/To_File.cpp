
#include "Components/CompoMe/Log/To_File.hpp"
#include "CompoMe/Log.hpp"
#include <algorithm>
#include <cstdio>

namespace CompoMe {

namespace Log {

To_File::To_File()
    : CompoMe::Component() /* PROVIDE */, log(this) /* DATA */,
      path(
          /*WARNING NO DEFAULT VALUE FOR THIS TYPE*/) {
  C_INFO_TAG("CONST: To_File", "Component,To_File");
  return;
}

//! Destructor
To_File::~To_File() noexcept {
  C_INFO_TAG("DEST: To_File", "Component,To_File");
  return;
}

/////////////////////////////////////////////////////////////////////////////
//                           COMPONENT_FUNCTIONS                           //
/////////////////////////////////////////////////////////////////////////////

void To_File::configuration() {
  Component::configuration();
  C_INFO_TAG("CONF: To_File", "Component,To_File");

  // configuration: sub_componentreturn;
}

void To_File::connection() {
  // connect: parent
  Component::connection();
  C_INFO_TAG("CONNECT: To_File", "Component,To_File");

  // connect: intern

  // connect: sub componentreturn;
}

void To_File::start() {
  // start: parent
  Component::start();
  C_INFO_TAG("START: To_File", "Component,To_File");
  if (this->get_path() == "") {
    this->set_path(std::tmpnam(nullptr));
  }

  C_INFO_TAG("LOG,FILE", "open file log: ", this->get_path());
  this->output.open(this->get_path());
  if (!this->output.is_open()) {
    C_ERROR_TAG("LOG,FILE", "Fail to open file");
    return;
  }

  C_TO_INFO(CompoMe::Require_helper<CompoMe::Log::Log_I>(this->get_lgo()),
            "Log open");
  return;
  // start: sub componentreturn;
}

void To_File::step() {
  // step: parent
  Component::step();
  C_INFO_TAG("STEP: To_File", "Component,To_File");

  this->output.flush();
  // step: receiver process// step: sub_componentreturn;
}

void To_File::stop() {
  // stop: parent
  Component::stop();
  // stop: sub_component
  C_INFO_TAG("STOP: To_File", "Component,To_File");

  this->output.close();
  return;
}

void To_File::status() {
  // status: parent
  Component::status();
  // status: sub_component
  C_INFO_TAG("STATUS: To_File", "Component,To_File");
  return;
}

/////////////////////////////////////////////////////////////////////////////
//                                INTERFACES                               //
/////////////////////////////////////////////////////////////////////////////

// // REQUIRE_LIST /////////////////////////////////////////////////////////////
//

} // namespace Log

} // namespace CompoMe
