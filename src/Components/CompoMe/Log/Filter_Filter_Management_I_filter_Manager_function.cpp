#include "Components/CompoMe/Log/Filter.hpp"
#include "Components/CompoMe/Log/Filter_Filter_Management_I_filter_Manager.hpp"

namespace CompoMe {

namespace Log {

void Filter_Filter_Management_I_filter_Manager::add(CompoMe::Log::Kind_e k) {
  this->get_c().set_filter(this->get_c().get_filter() | k);
  return;
}
void Filter_Filter_Management_I_filter_Manager::del(CompoMe::Log::Kind_e k) {
  this->get_c().set_filter(this->get_c().get_filter() & ~k);
  return;
}

} // namespace Log

} // namespace CompoMe
