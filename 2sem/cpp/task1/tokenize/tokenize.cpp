#include <iostream>
#include "tokenize.h"

bool IsNumeric(std::string_view str) {
  auto it = str.begin();
  int count = 0;
  while (it != str.end() && (std::isdigit(*it) || (count == 0 && (*it == '+' || *it == '-')))) {
    it++;
    count++;
  }
  return !str.empty() && it == str.end();
}

Token Type(std::string_view column) {
  if (column == "+") {
    PlusToken t;
    return t;
  }
  if (column == "-") {
    MinusToken t;
    return t;
  }
  if (column == "*") {
    MultiplyToken t;
    return t;
  }

  if (column == "/") {
    DivideToken t;
    return t;
  }

  if (column == "%") {
    ResidualToken t;
    return t;
  }

  if (column == "(") {
    OpeningBracketToken t;
    return t;
  }
  if (column == ")") {
    ClosingBracketToken t;
    return t;
  }

  if (column == "sqr") {
    SqrToken t;
    return t;
  }

  if (column == "max") {
    MaxToken t;
    return t;
  }

  if (column == "min") {
    MinToken t;
    return t;
  }

  if (column == "abs") {
    AbsToken t;
    return t;
  }

  if (IsNumeric(column)) {
    NumberToken t;
    t.value = atoi(column.data());
    return t;
  }

  UnknownToken t;
  t.value = column;
  return t;
}

std::vector<Token> Split(const std::string_view str, const char delim = ' ') {
  std::vector<Token> result;
  size_t l = 0;
  size_t r = -1;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == delim) {
      l = r;
      r = i;
      size_t index = l + 1;
      size_t length = r - index;
      std::string_view column(str.data() + index, length);
      if (column != "") {
        result.push_back(Type(column));
      }
    }
  }
  std::string_view column(str.data() + r + 1, str.size() - r - 1);
  if (column != "") {
    result.push_back(Type(column));
  }
  return result;
}

std::vector<Token> Tokenize(const std::string_view& input) {
  std::vector<Token> splitted = Split(input);
  return splitted;
}
