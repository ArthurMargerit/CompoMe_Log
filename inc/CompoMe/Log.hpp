#pragma once
namespace CompoMe {
template <typename T> class Require_helper_t;
namespace Log {
class Log_I;
}
} // namespace CompoMe

extern CompoMe::Require_helper_t<CompoMe::Log::Log_I> _log_output;

constexpr int c_strcmp(char const *lhs, char const *rhs) {
  return (('\0' == lhs[0]) && ('\0' == rhs[0])) ? 0
         : (lhs[0] != rhs[0])                   ? (lhs[0] - rhs[0])
                                                : c_strcmp(lhs + 1, rhs + 1);
}


#define DO_EXPAND(VAL)  1 ## VAL
#define EXPAND(VAL)     DO_EXPAND(VAL)
#define XSTR(x) STR(x)
#define STR(x) #x

#if defined(COMPOME_LOG) && (EXPAND(COMPOME_LOG) == 1)
#warning COMPOME_LOG not well defined for XSTR(__FILE__)
#undef COMPOME_LOG
#endif

#if defined(COMPOME_LOG) && COMPOME_LOG == 1
#include "Components/CompoMe/Log/To_Stream.hpp"
#include "Interfaces/CompoMe/Log/Log_I/Log_I.hpp"
#include "Structs/CompoMe/Log/Log_Info.hpp"
#include <sstream>
#include <time.h>

#if !defined(COMPOME_LOG_OUTPUT)
#define COMPOME_LOG_OUTPUT _log_output
#warning COMPOME_LOG_OUTPUT not well defined for __FILE__
#endif

extern CompoMe::Require_helper_t<CompoMe::Log::Log_I> COMPOME_LOG_OUTPUT;

namespace {
template <typename V> void M(std::stringstream &s, V v) { s << v; }

template <typename V, typename... T> void M(std::stringstream &s, V v, T... t) {
  s << v;
  ::M(s, t...);
}
template <typename... T> std::string MERGE(T... t) {
  std::stringstream ss;
  ::M(ss, t...);
  return ss.str();
}
} // namespace

#define C_GET_INFO(TAG)                                                        \
  CompoMe::Log::Log_Info _log_info;                                            \
  _log_info.set_File(__FILE__);                                                \
  _log_info.set_Function(__FUNCTION__);                                        \
  _log_info.set_Line(__LINE__);                                                \
  _log_info.set_Tag(TAG);                                                      \
  struct timespec _spec;                                                       \
  clock_gettime(CLOCK_REALTIME, &_spec);                                       \
  CompoMe::Log::time _time_l(_spec.tv_sec,(int)(_spec.tv_nsec / 1000)); \
  _log_info.set_Emitted_on(_time_l);

#define C_INFO(...) C_TO_INFO_TAG(COMPOME_LOG_OUTPUT, "None", __VA_ARGS__)
#define C_TO_INFO(TO, ...) C_TO_INFO_TAG(TO, "None", __VA_ARGS__)
#define C_INFO_TAG(TAG, ...) C_TO_INFO_TAG(COMPOME_LOG_OUTPUT, TAG, __VA_ARGS__)
#define C_TO_INFO_TAG(TO, TAG, ...)                                            \
  do {                                                                         \
    if (!TO.connected())                                                       \
      break;                                                                   \
    C_GET_INFO(TAG);                                                           \
    std::string msg = MERGE(__VA_ARGS__);                                      \
    TO->info(msg, _log_info);                                                  \
  } while (false);

#define C_DEBUG(...) C_TO_DEBUG_TAG(COMPOME_LOG_OUTPUT, "None", __VA_ARGS__)
#define C_TO_DEBUG(TO, ...) C_TO_DEBUG_TAG(TO, "None", __VA_ARGS__)
#define C_DEBUG_TAG(TAG, ...)                                                  \
  C_TO_DEBUG_TAG(COMPOME_LOG_OUTPUT, TAG, __VA_ARGS__)
#define C_TO_DEBUG_TAG(TO, TAG, ...)                                           \
  do {                                                                         \
    if (!TO.connected())                                                       \
      break;                                                                   \
    C_GET_INFO(TAG);                                                           \
    std::string msg = MERGE(__VA_ARGS__);                                      \
    TO->debug(msg, _log_info);                                                 \
  } while (false);

#define C_WARNING(...) C_TO_WARNING_TAG(COMPOME_LOG_OUTPUT, "None", __VA_ARGS__)
#define C_TO_WARNING(TO, ...) C_TO_WARNING_TAG(TO, "None", __VA_ARGS__)
#define C_WARNING_TAG(TAG, ...)                                                \
  C_TO_WARNING_TAG(COMPOME_LOG_OUTPUT, TAG, __VA_ARGS__)
#define C_TO_WARNING_TAG(TO, TAG, ...)                                         \
  do {                                                                         \
    if (!TO.connected())                                                       \
      break;                                                                   \
    C_GET_INFO(TAG);                                                           \
    std::string msg = MERGE(__VA_ARGS__);                                      \
    TO->warning(msg, _log_info);                                               \
  } while (false);

#define C_ERROR(...) C_TO_ERROR_TAG(COMPOME_LOG_OUTPUT, "None", __VA_ARGS__)
#define C_TO_ERROR(TO, ...) C_TO_ERROR_TAG(TO, "None", __VA_ARGS__)
#define C_ERROR_TAG(TAG, ...)                                                  \
  C_TO_ERROR_TAG(COMPOME_LOG_OUTPUT, TAG, __VA_ARGS__)
#define C_TO_ERROR_TAG(TO, TAG, ...)                                           \
  do {                                                                         \
    if (!TO.connected())                                                       \
      break;                                                                   \
    C_GET_INFO(TAG);                                                           \
    std::string msg = MERGE(__VA_ARGS__);                                      \
    TO->error(msg, _log_info);                                                 \
  } while (false);

#else

#define NO_ACTION(...)                                                         \
  do {                                                                         \
  } while (false);

#define C_ERROR(...) NO_ACTION()
#define C_TO_ERROR(...) NO_ACTION()
#define C_ERROR_TAG(...) NO_ACTION()
#define C_TO_ERROR_TAG(...) NO_ACTION()

#define C_WARNING(...) NO_ACTION()
#define C_TO_WARNING(...) NO_ACTION()
#define C_WARNING_TAG(...) NO_ACTION()
#define C_TO_WARNING_TAG(...) NO_ACTION()

#define C_DEBUG(...) NO_ACTION()
#define C_TO_DEBUG(...) NO_ACTION()
#define C_DEBUG_TAG(...) NO_ACTION()
#define C_TO_DEBUG_TAG(...) NO_ACTION()

#define C_INFO(...) NO_ACTION()
#define C_TO_INFO(...) NO_ACTION()
#define C_INFO_TAG(...) NO_ACTION()
#define C_TO_INFO_TAG(...) NO_ACTION()
#endif // COMPOME_LOG
