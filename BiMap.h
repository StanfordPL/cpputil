#ifndef BI_MAP_H
#define BI_MAP_H

#include <cassert>

#include <map>

namespace cpputil
{

template <class Key, class Val>
class BiMap
{
  public:
    bool containsKey(const Key& key) const;
    bool containsVal(const Val& val) const;

    void clear();

    bool empty() const;

    void eraseKey(const Key& key);
    void eraseVal(const Val& val);

    const Val& getVal(const Key& key) const;
    const Key& getKey(const Val& val) const;

    void insert(const Key& key, const Val& val);

    unsigned int size() const;

  private:
    std::map<const Key, const Val*> keyToVal_;
    std::map<const Val, const Key*> valToKey_;
};

template <class Key, class Val>
void BiMap<Key, Val>::clear()
{
  keyToVal_.clear();
  valToKey_.clear();
}

template <class Key, class Val>
bool BiMap<Key, Val>::containsKey(const Key& key) const
{
  return keyToVal_.find(key) != keyToVal_.end();
}

template <class Key, class Val>
bool BiMap<Key, Val>::containsVal(const Val& val) const
{
  return valToKey_.find(val) != valToKey_.end();
}

template <class Key, class Val>
bool BiMap<Key, Val>::empty() const
{
  return size() == 0;
}

template <class Key, class Val>
void BiMap<Key, Val>::eraseKey(const Key& key)
{
  assert(containsKey(key) && "Unrecognized key!");

  valToKey_.erase(getVal(key));
  keyToVal_.erase(key);
}

template <class Key, class Val>
void BiMap<Key, Val>::eraseVal(const Val& val) 
{
  assert(containsVal(val) && "Unrecognized val!");

  keyToVal_.erase(getKey(val));
  valToKey_.erase(val);
}

template <class Key, class Val>
const Val& BiMap<Key, Val>::getVal(const Key& key) const
{
  assert(containsKey(key) && "Unrecognized key!");

  auto itr = keyToVal_.find(key);
  return *(itr->second);
}

template <class Key, class Val>
const Key& BiMap<Key, Val>::getKey(const Val& val) const
{
  assert(containsVal(val) && "Unrecognized val!");

  auto itr = valToKey_.find(val);
  return *(itr->second);
}

template <class Key, class Val>
void BiMap<Key, Val>::insert(const Key& key, const Val& val)
{
  assert(!containsKey(key) && "Duplicate key!");
  assert(!containsVal(val) && "Duplicate val!");

  keyToVal_[key] = 0;
  valToKey_[val] = 0;

  auto keyitr = keyToVal_.find(key);
  auto valitr = valToKey_.find(val);

  keyToVal_[key] = &valitr->first;
  valToKey_[val] = &keyitr->first;
}

template <class Key, class Val>
unsigned int BiMap<Key, Val>::size() const
{
  return keyToVal_.size();
}

}

#endif
