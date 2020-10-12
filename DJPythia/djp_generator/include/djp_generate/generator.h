#ifndef DJPYTHIA_GENERATOR_GENERATOR_H_
#define DJPYTHIA_GENERATOR_GENERATOR_H_
#include <iterator>

#include "Pythia8/Pythia.h"
namespace djpythia {
namespace generator {

/* Class used to generate the events with pythia. You can use it by creating
 * an instance of it and iterate over the events with a for loop.
 * PythiaGenerator gen("config.cgf", 13, 10);
 * for (const Pythia8::Event& event : pythia) { ...do some work... } */
class PythiaGenerator {
 public:
  /* Given a configuration file, a seed for the random number generation and a
   * number of events to be generated, creates a generator. */
  PythiaGenerator(std::string config_file, int seed, int n_events );

  Pythia8::Pythia& Pythia() { return pythia_; }

  const std::string& ConfigFile() const { return config_file_; }
  int Seed() const { return seed_; }
  int NEvents() const { return n_events_; }

  /* The iterator allows you to loop for the total number of events. After that
   * number is reached, the iterator will move the position to -1 (end). */
  class Iterator
      : public std::iterator<std::input_iterator_tag, const Pythia8::Event> {
    PythiaGenerator* generator_{nullptr};
    long int position_{0};

   public:
    Iterator() = default;
    Iterator(PythiaGenerator& generator, long int position);

    bool IsValid() const {
      return (position_ >= 0) && (position_ < generator_->NEvents());
    }

    bool operator==(const Iterator& lhs) const {
      return (generator_ == lhs.generator_) && (position_ == lhs.position_);
    }

    bool operator!=(const Iterator& lhs) const { return !(*this == lhs); }

    // Operator for it++ (postfix).
    const Iterator operator++(int) {
      const auto value_before_increase = *this;
      this->operator++();
      return value_before_increase;
    }

    // Operator for it (postfix).
    Iterator& operator++() {
      if (IsValid()) {
        position_++;
        generator_->Pythia().next();
      }
      else {
        position_ = -1;
      }
      return *this;
    }

    // Return the current Pythia event
    const Pythia8::Event& operator*() const {
      return generator_->Pythia().event;
    }
  };

  Iterator begin() { return {*this, 0}; }
  Iterator end() { return {*this, -1}; }

 private:
  Pythia8::Pythia pythia_;
  const std::string config_file_;
  const int seed_;
  const int n_events_;
};

}  // namespace generator
}  // namespace djpythia

#endif  // DJPYTHIA_GENERATOR_GENERATOR_H_
