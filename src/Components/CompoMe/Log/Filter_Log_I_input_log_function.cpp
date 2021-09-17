#include "Components/CompoMe/Log/Filter.hpp"
#include "Components/CompoMe/Log/Filter_Log_I_input_log.hpp"
#include <iostream>

namespace CompoMe {

namespace Log {
namespace {

bool tag_is_fitred(const CompoMe::String &tags,
                   const Vec<CompoMe::String> &p_tag) {

  if(p_tag.size() == 0 ) {
    return true;
  }

  for (auto i_r : p_tag) {
    if (tags.str.find(i_r.str) != std::string::npos) {
      return true;
    }
  }
  return false;
}

} // namespace

void Filter_Log_I_input_log::error(CompoMe::String mess,
                                   CompoMe::Log::Log_Info i) {
  this->log(Kind_e::ERROR, mess, i);
  return;
}

void Filter_Log_I_input_log::warning(CompoMe::String mess,
                                     CompoMe::Log::Log_Info i) {
  this->log(Kind_e::WARNING, mess, i);
  return;
}

void Filter_Log_I_input_log::debug(CompoMe::String mess,
                                   CompoMe::Log::Log_Info i) {
  this->log(Kind_e::DEBUG, mess, i);
  return;
}

void Filter_Log_I_input_log::info(CompoMe::String mess,
                                  CompoMe::Log::Log_Info i) {
  this->log(Kind_e::INFO, mess, i);
  return;
}

void Filter_Log_I_input_log::log(CompoMe::Log::Kind_e k, CompoMe::String mess,
                                 CompoMe::Log::Log_Info i) {

  std::cout << static_cast<std::uint64_t>(this->get_c().get_filter() & k) << "\n";
  if (((this->get_c().get_filter() & k) != CompoMe::Log::Kind_e::NONE) &&
      tag_is_fitred(i.get_Tag(), this->get_c().get_filter_tag())) {

    // ref connected
    if (this->get_c().pass_log.connected()) {
      this->get_c().pass_log->log(k, mess, i);
    }
  } else {

    // ref connected
    if (this->get_c().refused_log.connected()) {
      this->get_c().refused_log->log(k, mess, i);
    }
  }

  return;
}

} // namespace Log

} // namespace CompoMe
