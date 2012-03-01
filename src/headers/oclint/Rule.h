#ifndef OCLINT_RULE_H
#define OCLINT_RULE_H

#include <string>
#include <vector>

using namespace std;

#include <clang-c/Index.h>

class ViolationSet;
class RuleSet;

class Rule {
public:
  virtual ~Rule() {}
  virtual vector<string> nodes() = 0;
  
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) = 0;
  
  virtual const string name() const = 0;
};

#endif
