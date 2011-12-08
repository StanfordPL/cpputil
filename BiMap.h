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
    unsigned int size() const;

    bool containsKey(const Key& key) const;
    bool containsVal(const Val& val) const;

    void clear();

    void insert(const Key& key, const Val& val);

    Val getVal(const Key& key) const;
    Key getKey(const Val& val) const;

    typedef typename std::map<Key, Val>::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

  private:
    std::map<Key, Val> keyToVal_;
    std::map<Val, Key> valToKey_;
};

template <class Key, class Val>
unsigned int BiMap<Key, Val>::size() const
{
  return keyToVal_.size();
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
void BiMap<Key, Val>::clear()
{
  keyToVal_.clear();
  valToKey_.clear();
}

template <class Key, class Val>
void BiMap<Key, Val>::insert(const Key& key, const Val& val)
{
  assert(!containsKey(key) && "Duplicate key!");
  assert(!containsVal(val) && "Duplicate val!");

  keyToVal_[key] = val;
  valToKey_[val] = key;
}

template <class Key, class Val>
Val BiMap<Key, Val>::getVal(const Key& key) const
{
  assert(containsKey(key) && "Unrecognized key!");

  auto itr = keyToVal_.find(key);
  return (*itr).second;
}

template <class Key, class Val>
Key BiMap<Key, Val>::getKey(const Val& val) const
{
  assert(containsVal(val) && "Unrecognized val!");

  auto itr = valToKey_.find(val);
  return (*itr).second;
}

template <class Key, class Val>
inline typename BiMap<Key, Val>::const_iterator BiMap<Key, Val>::begin() const
{
  return keyToVal_.begin();
}

template <class Key, class Val>
inline typename BiMap<Key, Val>::const_iterator BiMap<Key, Val>::end() const
{
  return keyToVal_.end();
}

}

#endif
