#pragma once
#include <fstream>

#include "Components/Component.hpp"

#include "CompoMe/Log.hpp"
// TYPE
#include "Data/CompoMe_Log.hpp"

// STRUCT

// INTERFACES
// provide

#include "Components/CompoMe/Log/To_CircularFile_Log_I_log.hpp"

// require

// require multi

// SUB COMPONENT  ////////////////////////////////////////////////////////////

// SUB CONNECTOR ////////////////////////////////////////////////////////////

namespace CompoMe {

namespace Log {

class To_CircularFile : public CompoMe::Component {

public:
  // Contructor / Destructor
  To_CircularFile();
  virtual ~To_CircularFile() noexcept;

  CompoMe::Log::To_CircularFile &
  operator=(const CompoMe::Log::To_CircularFile &i) {
    this->set_path(i.get_path());
    this->set_current_position(0);
    this->set_ligne_buff_size(i.get_ligne_buff_size());
    return *this;
  }

  // composant initialisation
  void configuration() override;
  void connection() override;
  void start() override;
  void stop() override;
  void step() override;
  void status() override;

  // GET/SET //////////////////////////////////////////////////////////////////
  // path
  CompoMe::String get_path() const;
  void set_path(const CompoMe::String &path);
  // ligne_buff_size
  ui64 get_ligne_buff_size() const;
  void set_ligne_buff_size(const ui64 &ligne_buff_size);
  // current_position
  ui64 get_current_position() const;
  void set_current_position(const ui64 &current_position);

  // PROVIDES

  To_CircularFile_Log_I_log &get_log();

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
  To_CircularFile_Log_I_log log;

  // RECEIVER

public:
  // REQUIRE MULTI

  // EMITTER
  // /////////////////////////////////////////////////////////////////////

  // DATA /////////////////////////////////////////////////////////////////////
  CompoMe::String path;
  ui64 ligne_buff_size;
  ui64 current_position;

  // SUB COMPONENT ////////////////////////////////////////////////////////////

  // SUB CONNECTOR ////////////////////////////////////////////////////////////
private:
  std::ofstream output;
  
public:
  std::ostream &get_output() {
    this->current_position ++;
    if (this->current_position % this->ligne_buff_size == 0) {
      this->current_position = 0;
      this->output.seekp(0);
    }
    return this->output;
  }
};

// std::ostream& operator<<(std::ostream& os, const
// CompoMe::Log::To_CircularFile& c); std::istream& operator>>(std::istream& is,
// CompoMe::Log::To_CircularFile& c);

} // namespace Log

} // namespace CompoMe
