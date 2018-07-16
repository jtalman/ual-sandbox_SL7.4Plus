#include<iostream>
#include "sxfVerbose/hashes/ElemBendHash.hh"

// Constructor
SXF::ElemBendHash::ElemBendHash() 
  : SXF::ElemBucketHash()
{
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " enter SXF::ElemBendHash::ElemBendHash() : SXF::ElemBucketHash()\n";
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " leave SXF::ElemBendHash::ElemBendHash() : SXF::ElemBucketHash()\n";
}

// Map an attribute key to its enum value
int SXF::ElemBendHash::index(const char* str) const
{
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " enter int SXF::ElemBendHash::index(const char* str) const. str " << str << "\n";
  static const struct SXF_Key keys[] =          // JDT2018
  {
    {"klE",   KLE},
    {"klM",   KLM},
    {"fint",  FINT},
    {"hgap",  HGAP},
    {"e1",    E1},
    {"e2",    E2},
  };
/*
  static const struct SXF_Key keys[] =
  {
    {"kl",    KL},
    {"kls",   KLS},
    {"fint",  FINT},
    {"hgap",  HGAP},
    {"e1",    E1},
    {"e2",    E2},
  };
*/

  int index, result = -1;

  if(!str) return result;

  if(strlen(str) > 2){
    switch (str[2]) {
    case 'E':
      index = KLE;
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " KLE setting index " << index << "\n";
      break;      
    case 'M':
      index = KLM;
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " KLM setting index " << index << "\n";
      break;      
    case 'n':
      index = FINT;
      break;  
    case 'a':
      index = HGAP;
      break; 
    default:
    return result;
    }
  }
  else {
    switch (str[1]) {
    case '1':
      index = E1;
      break;
    case '2':
      index = E2;
      break;
    default:
      return result;
    }
  }

  char *s = keys[index].name;
  if(!strcmp(str, s)) result = keys[index].number;

std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " leave int SXF::ElemBendHash::index(const char* str) const. result " << result << "\n";
  return result;
}
