// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// This crashes if we try to emit debug info for TEMPLATE_DECL members.
template <class T> class K2PtrVectorBase {};
template <class T> class K2Vector {};
template <class U > class K2Vector<U*> : public K2PtrVectorBase<U*> {};
class ScriptInfoManager {
  void PostRegister() ;
  template <class SI> short ReplaceExistingElement(K2Vector<SI*>& v);
};
void ScriptInfoManager::PostRegister() {}