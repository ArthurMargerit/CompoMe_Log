#pragma once

#include "Components/Component.hpp"

#include "CompoMe/Log.hpp"
// TYPE
#include "Data/CompoMe_Log.hpp"

// STRUCT

// INTERFACES
// provide

#include "Components/CompoMe/Log/Match_Log_I_input_log.hpp"

// require

#include "Interfaces/CompoMe/Log/Log_I/Log_I.hpp"

#include "Interfaces/CompoMe/Log/Log_I/Log_I.hpp"

// require multi

// SUB COMPONENT  ////////////////////////////////////////////////////////////

// SUB CONNECTOR ////////////////////////////////////////////////////////////

namespace CompoMe {

namespace Log {

class Match : public CompoMe::Component {

public:
  // Contructor / Destructor
  Match();
  virtual ~Match() noexcept;

  // composant initialisation
  void configuration() override;
  void connection() override;
  void start() override;
  void stop() override;
  void step() override;
  void status() override;

  // GET/SET //////////////////////////////////////////////////////////////////
  // regex
  CompoMe::String get_regex() const;
  CompoMe::String& a_regex();
  void set_regex(const CompoMe::String &regex);

  // PROVIDES

  Match_Log_I_input_log &get_input_log();

  // RECEIVERS

  // FUNCTIONS

  // SUB COMPONENTS

private:
  std::ostream &to_stream_data(std::ostream &,
                               CompoMe::Serialization_context_export &) const;
  std::ostream &to_stream_sc(std::ostream &,
                             CompoMe::Serialization_context_export &) const;
  std::ostream &
  to_stream_provide(std::ostream &,
                    CompoMe::Serialization_context_export &) const;

  std::istream &from_stream_data(std::istream &,
                                 CompoMe::Serialization_context_import &);
  std::istream &from_stream_sc(std::istream &,
                               CompoMe::Serialization_context_import &);
  std::istream &from_stream_provide(std::istream &,
                                    CompoMe::Serialization_context_import &);

public:
  void to_stream(std::ostream &os,
                 CompoMe::Serialization_context_export &p_ctx) const override;
  void from_stream(std::istream &is,
                   CompoMe::Serialization_context_import &p_ctx) override;

  // INTERFACE ////////////////////////////////////////////////////////////////
  // PROVIDE
  Match_Log_I_input_log input_log;

  // RECEIVER

public:
  CompoMe::Require_helper_t<CompoMe::Log::Log_I> match_log;

  CompoMe::Require_helper_t<CompoMe::Log::Log_I> unmatch_log;

  // REQUIRE MULTI

  // EMITTER
  // /////////////////////////////////////////////////////////////////////

  // DATA /////////////////////////////////////////////////////////////////////
  CompoMe::String regex;

  // SUB COMPONENT ////////////////////////////////////////////////////////////

  // SUB CONNECTOR ////////////////////////////////////////////////////////////
};

std::ostream &operator<<(std::ostream &os, const Match &c);
std::istream &operator>>(std::istream &is, Match &c);

} // namespace Log

} // namespace CompoMe
