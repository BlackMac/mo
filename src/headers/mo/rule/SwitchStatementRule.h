#ifndef MO_SWITCHSTATEMENTRULE_H
#define MO_SWITCHSTATEMENTRULE_H

#include "mo/Rule.h"

class SwitchStatementRule : public Rule {
private:
  string _name;
  
public:
  SwitchStatementRule();
  
  virtual void apply(CXCursor& node, CXCursor& parentNode, RuleData& data);
  virtual const string& name() const;
};

#endif
