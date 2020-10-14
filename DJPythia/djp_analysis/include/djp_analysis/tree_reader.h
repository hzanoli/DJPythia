#ifndef DJPYTHIA_TREE_ANALYSIS_TREE_READER_H_
#define DJPYTHIA_TREE_ANALYSIS_TREE_READER_H_
#include <string>
#include <iostream>
#include <iterator>

#include "TFile.h"
#include "TTreeReader.h"

namespace djpythia {
namespace tree_analysis {
template <class T>
/* Reads the tree containing the events using a simple interface.
 * You can create it using:
 * TreeReader events<EventClass>("file.root", "my_tree_name", "branch_name");
 * and then loop using:
 * for (const EventClass& event: events) { ... your work here ... } */
class TreeReader {
 private:
  TFile file_;
  TTreeReader tree_reader_;
  TTreeReaderValue<T> reader_value_;

 public:
  class Iterator : public std::iterator<std::input_iterator_tag, const T> {
   private:
    TreeReader* reader_;
    bool is_valid_;

   public:
    Iterator(TreeReader& reader, bool is_valid)
        : reader_(&reader), is_valid_(is_valid) {};

    bool operator==(const Iterator& rhs) const {
      return (reader_ == rhs.reader_) && (is_valid_ == rhs.is_valid_);
    }
    bool operator!=(const Iterator& rhs) const { return !(rhs == *this); }

    Iterator& operator++() {
      is_valid_ = reader_->tree_reader_.Next();
      return *this;
    }

    Iterator operator++(int) {
      Iterator value = *this;
      ++(*this);
      return value;
    }

    const T& operator*() const { return *(reader_->reader_value_); }
  };

  // Given a file path, the name of the tree and and the branch name, creates a
  // tree reader.
  TreeReader(const std::string& file_path, const std::string& tree_name,
             const std::string& branch_name)
      : file_(file_path.c_str()),
        tree_reader_(tree_name.c_str(), &file_),
        reader_value_(tree_reader_, branch_name.c_str()){};

  TreeReader::Iterator begin() {
    tree_reader_.Next();  // Initialize the Tree reading
    return Iterator(*this, true);
  };

  TreeReader::Iterator end() { return Iterator(*this, false); };
};

}  // namespace tree_analysis
}  // namespace djpythia

#endif  // DJPYTHIA_TREE_ANALYSIS_TREE_READER_H_
