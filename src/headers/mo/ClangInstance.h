#ifndef MO_CLANGINSTANCE_H
#define MO_CLANGINSTANCE_H

#include <string>
#include <vector>

using namespace std;

#include <clang-c/Index.h>

class Reporter;

class ClangInstance {
private:
  CXIndex _index;
  CXTranslationUnit _translationUnit;
  
  ClangInstance(const ClangInstance&);
  ClangInstance& operator=(const ClangInstance&);

public:
  ClangInstance();
  virtual ~ClangInstance();
  
  void compileSourceFileToTranslationUnit(const char * const * argv, int argc);
  bool hasDiagnostics() const;
  bool hasWarnings() const;
  const vector<CXDiagnostic> warnings() const;
  const string reportDiagnostics(const Reporter& reporter);
  const CXTranslationUnit& getTranslationUnit() const;
};

#endif
