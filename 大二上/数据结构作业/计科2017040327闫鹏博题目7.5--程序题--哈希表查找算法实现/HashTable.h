#ifndef HASHTABLE_H_INCLUDE
#define HASHTABLE_H_INCLUDE

template <class ElemType, class KeyType>
class HashTable {
private:
	ElemType * elems;
	bool * empty;
	int capacity;
	int divisor;

	int hashHelp(KeyType key);
	int collisionHelp(KeyType & key, int i);
	bool selectHelp( KeyType & key, int & pos);

public:
	HashTable(int capacity, int divisor);
	~HashTable();
	bool insert(ElemType & elem);
	bool select(KeyType & key, ElemType & elem);
	bool deleteElem(ElemType & elem);
};
template<class ElemType, class KeyType>
inline int HashTable<ElemType, KeyType>::hashHelp(KeyType key)
{
	return key % divisor;
}
template<class ElemType, class KeyType>
inline int HashTable<ElemType, KeyType>::collisionHelp(KeyType & key, int i)
{
	return (hashHelp(key) + i) % divisor;
}
template<class ElemType, class KeyType>
inline bool HashTable<ElemType, KeyType>::selectHelp(KeyType & key, int & pos)
{
	int c = 0;								//冲突次数
	pos = hashHelp(key);

	while (c < capacity
		&& !empty[pos]
		&& key != elems[pos]) {
		pos = collisionHelp(key, ++c);
	}

	if (c >= capacity || empty[pos]) {
		return false;
	}
	else {
		return true;
	}
	
}
template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::HashTable(int capacity, int divisor){
	this->capacity = capacity;
	this->divisor = divisor;

	elems = new ElemType[capacity];
	empty = new bool[capacity];
	for (int i = 0; i < capacity; i++) {
		empty[i] = true;
	}
}
template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::~HashTable() {
	delete []elems;
	//delete []empty;这行代码不知道为啥有错误
}
template<class ElemType, class KeyType>
inline bool HashTable<ElemType, KeyType>::insert(ElemType & elem)
{
	int pos;
	if (!selectHelp(elem, pos) && empty[pos]) {
		elems[pos] = elem;
		empty[pos] = false;
		return true;
	}
	else 
	return false;
}
template<class ElemType, class KeyType>
inline bool HashTable<ElemType, KeyType>::select(KeyType & key, ElemType & elem)
{
	int pos;
	if (selectHelp(key, pos)) {
		elem = elems[pos];
		return true;
	}
	else
	return false;
}
template<class ElemType, class KeyType>
inline bool HashTable<ElemType, KeyType>::deleteElem(ElemType & elem)
{
	int pos;
	if (selectHelp(elem, pos)) {
		empty[pos] = true;
		return true;
	}
	else {
		return false;
	}
	return false;
}
#endif // !HASHTABLE_H_INCLUDE
