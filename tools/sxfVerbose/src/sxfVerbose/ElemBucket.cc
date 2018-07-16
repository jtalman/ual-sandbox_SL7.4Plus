#include "sxfVerbose/ElemBucket.hh"

// Constructor.
SXF::ElemBucket::ElemBucket(SXF::OStream& out, const char* type, SXF::ElemBucketHash* hash) 
  : m_refOStream(out), m_iAttribID(-1) 
{
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " enter SXF::ElemBucket::ElemBucket CONSTRUCTOR\n";
  setType(type);
  m_pHash = hash;
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " leave SXF::ElemBucket::ElemBucket CONSTRUCTOR\n";
}

// Destructor.
SXF::ElemBucket::~ElemBucket() 
{
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " enter SXF::ElemBucket::~ElemBucket() DESTRUCTOR\n";
  if(m_sType) { delete [] m_sType; }
  if(m_pHash) { delete m_pHash; }
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " leave SXF::ElemBucket::~ElemBucket() DESTRUCTOR\n";
}

// Select a bucket attribute and make it current. 
int SXF::ElemBucket::openAttribute(const char* name)
{
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " enter int SXF::ElemBucket::openAttribute(const char* name)\n";
  m_iAttribID = m_pHash->index(name);
std::cerr << "JDT2018 - File " << __FILE__ << " line " << __LINE__ << " leave int SXF::ElemBucket::openAttribute(const char* name). m_iAttribID " << m_iAttribID << "\n";
  return (m_iAttribID >= 0);
}

// Close a current attribute.
void SXF::ElemBucket::closeAttribute()
{
  m_iAttribID = -1;
}

// Set bucket type.
void SXF::ElemBucket::setType(const char* type)
{
  m_sType = new char[strlen((char*) type) + 1];
  strcpy(m_sType, (char*)  type);
}

