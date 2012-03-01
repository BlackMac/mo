#ifndef OCLINT_RULESET_H
#define OCLINT_RULESET_H

#include <vector>
#include <map>
#include <string>

using namespace std;

#include <clang-c/Index.h>

class Rule;
class ViolationSet;

class RuleSet {
private:
  static vector<Rule*>* _rules;
  static map<string, vector<Rule*> >* _registry;
  
  static void apply(string nodeType, CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  
public:
  RuleSet(Rule* rule);
  static int numberOfRules();
  static void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
};

#endif
