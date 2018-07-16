#include<iostream>
#include "sxfVerbose/hashes/ElemMultipoleHash.hh"

// Constructor
SXF::ElemMultipoleHash::ElemMultipoleHash() 
  : SXF::ElemBucketHash()
{}

// Map an attribute key to its enum value
int SXF::ElemMultipoleHash::index(const char* str) const
{
  static const struct SXF_Key keys[] =
  {
    {"klE",   KLE},
    {"klM",   KLM},
    {"lrad",  LRAD},
  };

  int index, result = -1;

  if(!str) return result;

  switch (str[2]) {
  case 'E':
    index = KLE;
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " KLE setting index " << index << "\n";
    break; 
  case 'M':
    index = KLM;
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " KLM setting index " << index << "\n";
    break; 
  case 'a':
    index = LRAD;
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " LRAD setting index " << index << "\n";
    break; 
  default:
    return result;   
  };

/*
  switch (strlen(str)) {
  case 2: 
    index = 0;
    break;
  case 3:
    index = 1;
    break;
  case 4:
    index = 2;
    break;
  default:
    return result;   
  };
*/

  char *s = keys[index].name;
  if(!strcmp(str, s)) result = keys[index].number;

  return result;
}
