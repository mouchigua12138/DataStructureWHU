#include "HuffChar.h"
bool HuffChar::operator < (HuffChar const& hc) {
	return this->weight > hc.weight;//此处故意大小颠倒
}
bool HuffChar::operator > (HuffChar const& hc) {
	return this->weight < hc.weight;//此处故意大小颠倒
}
bool HuffChar::operator == (HuffChar const& hc) {
	return this->weight == hc.weight;
}