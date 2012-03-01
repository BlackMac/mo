#include "oclint/RuleSet.h"
#include "oclint/Rule.h"
#include "oclint/helper/CursorHelper.h"

#include <clang/AST/DeclBase.h>
#include <clang/AST/Stmt.h>

using namespace clang;

vector<Rule*>* RuleSet::_rules = NULL;
map<string, vector<Rule*> >* RuleSet::_registry = NULL;

RuleSet::RuleSet(Rule* rule) {
  if (_rules == NULL) {
    _rules = new vector<Rule*>();
    _registry = new map<string, vector<Rule*> >();
  }
  map<string, vector<Rule*> >::iterator it;
  for (int i = 0, e = rule->nodes().size(); i < e; i++) {
    string nodeType = rule->nodes().at(i);
    it = _registry->find(nodeType);
    if (it == _registry->end()) {
      vector<Rule*> v;
      v.push_back(rule);
      _registry->insert( pair<string, vector<Rule*> >(nodeType, v) );
    }
    else {
      it->second.push_back(rule);
    }
  }
  _rules->push_back(rule);
}

int RuleSet::numberOfRules() {
  return _rules == NULL ? 0 : _rules->size();
}

void RuleSet::apply(string nodeType, CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  map<string, vector<Rule*> >::iterator it = _registry->find(nodeType);
  if (it != _registry->end()) {
    for (int i = 0, e = it->second.size(); i < e; i++) {
      it->second.at(i)->apply(node, parentNode, violationSet);
    }
  }
}

void RuleSet::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorHelper::getStmt(node);
  if (stmt) {
    apply(stmt->getStmtClassName(), node, parentNode, violationSet);
    return;
  }
  Decl *decl = CursorHelper::getDecl(node);
  if (decl) {
    apply(decl->getDeclKindName(), node, parentNode, violationSet);
  }
}
