//
// Created by Vitaliy on 9/6/20.
//
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <chrono>

class FileReader {
public:
    explicit FileReader(const std::string &fileName) {
      this->file.open(fileName, std::ios::in); //open a file to perform read operation using file object
      if (!this->file.is_open())
        throw "Something wrong!!!";
    }

    std::string getLine() {
      std::string tp;
      while (true) {
        if (!getline(this->file, tp)) {
          return "";
        }
        if (!tp.empty()) {
          break;
        }
      }

      return tp;
    }

    ~FileReader() {
      this->file.close();
    }

private:
    std::fstream file;
};

class LineParser {
public:
    static std::pair<std::string, int> getNextWord(const std::string &line, int pos = 0) {
      std::string word;

      while(pos < line.length() && !std::isalnum(line[pos])) {
        ++pos;
      }

      while (pos < line.length() && std::isalnum(line[pos])) {
          word += line[pos++];
      }

      while(pos < line.length() && !std::isalnum(line[pos])) {
        ++pos;
      }

      return std::make_pair(word, pos);
    }
};

class BiGramsSmalltalk {
public:
    explicit BiGramsSmalltalk (std::string _filename): filename(std::move(_filename)) {
      this->lineParser = std::make_unique<LineParser>();
    }

    void print() {
      this->createMap();
      for(const auto& item : this->getSortedList()) {
        //std::cout << item.first << ": " << item.second << std::endl;
      }
    }

private:
    const std::string filename;
    std::unique_ptr<LineParser> lineParser;

    std::unordered_map<std::string, int> biRideMap;

    std::unordered_map<std::string, int> createMap() {
      std::unique_ptr<FileReader> fileReader = std::make_unique<FileReader>(this->filename);
      std::string line = fileReader->getLine();
      auto currentWord = this->lineParser->getNextWord(line);
      while (true) {
        if (line.empty()) { break; }
        while (currentWord.second < line.length()) {
          auto nextWord = this->lineParser->getNextWord(line, currentWord.second);
          if (auto idx = biRideMap.insert({currentWord.first + ' ' + nextWord.first, 1});
              !idx.second
          ) {
            idx.first->second++;
          }
          currentWord = nextWord;
        }
        line = fileReader->getLine();
        currentWord.second = 0;
      }

      return biRideMap;
    }

    std::vector<std::pair<std::string, int>> getSortedList() {
      std::vector<std::pair<std::string, int>> tmp;
      for (auto& item : biRideMap){ tmp.emplace_back(item); }

      sort(tmp.begin(), tmp.end(), [](const auto &a, const auto &b) { return a.second < b.second; });

      return tmp;
    }
};

class BiGramsFortran {
public:
    explicit BiGramsFortran (std::string _filename): filename(std::move(_filename)) {
      this->lineParser = std::make_unique<LineParser>();
    }

    void print() {
      this->createMap();
      this->makeUnique();
      for(const auto& item : this->getSortedList()) {
        //std::cout << item.first << ": " << item.second << std::endl;
      }
    }

private:
    const std::string filename;
    std::unique_ptr<LineParser> lineParser;

    std::vector<std::pair<std::string, int>> biRideMap;

    std::vector<std::pair<std::string, int>> createMap() {
      std::unique_ptr<FileReader> fileReader = std::make_unique<FileReader>(this->filename);
      std::string line = fileReader->getLine();
      auto currentWord = this->lineParser->getNextWord(line);

      while (true) {
        if (line.empty()) { break; }
        while (currentWord.second < line.length()) {
          auto nextWord = this->lineParser->getNextWord(line, currentWord.second);
          biRideMap.emplace_back(std::make_pair<std::string, int>(currentWord.first + ' ' + nextWord.first, 1));
          currentWord = nextWord;
        }
        line = fileReader->getLine();
        currentWord.second = 0;
      }

      return biRideMap;
    }

    std::vector<std::pair<std::string, int>> getSortedList() {
      sort(biRideMap.begin(), biRideMap.end(), [](const auto &a, const auto &b) { return a.second < b.second; });

      return biRideMap;
    }

    std::vector<std::pair<std::string, int>> makeUnique() {
      sort(biRideMap.begin(), biRideMap.end(), [](const auto &a, const auto &b) { return a.first < b.first; });

      auto leftPosition = biRideMap.begin();
      for (auto rightPosition=biRideMap.begin() + 1; rightPosition != biRideMap.end(); rightPosition++) {
        if (leftPosition->first == rightPosition->first) {
          leftPosition->second++;
        } else{
          leftPosition++;
          leftPosition->first = move(rightPosition->first);
          leftPosition->second = rightPosition->second;
        }
      }
      biRideMap.erase(leftPosition + 1, biRideMap.end());

      return biRideMap;
    }
};

template <typename Callable>
void measure(Callable f) {
  auto start = std::chrono::high_resolution_clock::now();
  f();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "\n\nTime taken by function: "
       << duration.count() << " microseconds" << std::endl;
}


void testBiGrams() {
  std::string FILE_NAME = "/magento/cpp/stepanov-conversations-course/data/shakespe.are";
  std::shared_ptr<BiGramsSmalltalk> smalltalkWay = std::make_shared<BiGramsSmalltalk>(FILE_NAME);

  measure([smalltalkWay] { smalltalkWay->print(); });

  std::shared_ptr<BiGramsFortran> fortranWay = std::make_shared<BiGramsFortran>(FILE_NAME);
  measure([fortranWay] { fortranWay->print(); });
}