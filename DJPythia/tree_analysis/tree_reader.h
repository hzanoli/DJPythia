#ifndef DJPYTHIA_TREE_ANALYSIS_TREE_READER_H_
#define DJPYTHIA_TREE_ANALYSIS_TREE_READER_H_
#include <string>

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
  class Iterator {
   private:
    TreeReader* reader_;
    TTreeReader::Iterator_t tree_iteration_;

   public:
    Iterator() = default;
    Iterator(TreeReader& reader, Long64_t entry)
        : reader_(&reader), tree_iteration_(reader.tree_reader_, entry){};

    bool operator==(const Iterator& rhs) const {
      return reader_ == rhs.reader_ && tree_iteration_ == rhs.tree_iteration_;
    }
    bool operator!=(const Iterator& rhs) const { return !(rhs == *this); }

    Iterator& operator++() {
      ++tree_iteration_;
      return *this;
    }

    const Iterator operator++(int) {
      Iterator value = *this;
      ++(*this);
      return value;
    }

    const T& operator*() const { return *(reader_->reader_value_); }
  };

  // Given a file path, the name of the tree and and
  TreeReader(const std::string& file_path, const std::string& tree_name,
             const std::string& branch_name)
      : file_(file_path.c_str()),
        tree_reader_(tree_name.c_str(), &file_),
        reader_value_(tree_reader_, branch_name.c_str()){};

  TreeReader::Iterator begin() {
    tree_reader_.Next();  // Initialize the Tree reading
    return iterator(*this, 0);
  };

  TreeReader::Iterator end() { return iterator(*this, -1); };
};

}  // namespace tree_analysis
}  // namespace djpythia

#endif  // DJPYTHIA_TREE_ANALYSIS_TREE_READER_H_
