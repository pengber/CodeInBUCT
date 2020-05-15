#pragma once

#include "BBSTree.h"
using namespace std;

template <class KeyType, class ValueType>
class MapNode {
protected:
	KeyType key;
	ValueType value;
public:
	MapNode() {};
	MapNode(KeyType k, ValueType v) :key(k), value(v) {}
	MapNode(ValueType v) :key(KeyType(v)), value(v) {}//用字符本身构造
	bool operator < (const MapNode& b) const {
		return this->key < b.key;
	}
	bool operator > (const MapNode& b) const {
		return this->key > b.key;
	}
	bool operator == (const MapNode& b) const {
		return this->key == b.key;
	}
	void setValue(const ValueType& v) { this->value = v; }
	KeyType getKey() const { return this->key; }
	MapNode& operator = (const MapNode& b) {
		if (&b == this) { return *this; }
		else {
			this->key = b.key;
			this->value = b.value;
			return *this;
		}
	}
};