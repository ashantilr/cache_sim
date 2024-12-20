#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  address_type newAdd =  address<< (32 - (cache->block_bits + cache->set_bits));
  return (newAdd>>(cache->block_bits + (32 - (cache->block_bits + cache->set_bits))));
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  return (address>>(cache->block_bits + cache->set_bits));
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  address_type newAdd = address<<(32-cache->block_bits);
  return newAdd>>(32-cache->block_bits);
}
