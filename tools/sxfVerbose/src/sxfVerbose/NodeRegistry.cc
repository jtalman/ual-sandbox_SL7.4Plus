#include "sxfVerbose/NodeRegistry.hh"

// #include <iostream.h>
#include "sxfVerbose/Perfect_Hash.hh"

// Constructor.
SXF::NodeRegistry::NodeRegistry(SXF::OStream& out) 
  : 
  m_refOStream(out),
  m_iSize(0),
  m_aElements(0),  
  m_pErrorElement(0), 
  m_pSequence(0)
{
std::cerr << "File " << __FILE__ << " line " << __LINE__ << " enter SXF::NodeRegistry::NodeRegistry(SXF::OStream& out) CONSTRUCTOR\n";
std::cerr << "File " << __FILE__ << " line " << __LINE__ << " leave SXF::NodeRegistry::NodeRegistry(SXF::OStream& out) CONSTRUCTOR\n";
}

// Destructor.
SXF::NodeRegistry::~NodeRegistry() 
{
std::cerr << "File " << __FILE__ << " line " << __LINE__ << " enter SXF::NodeRegistry::~NodeRegistry() DESTRUCTOR\n";
std::cerr << "File " << __FILE__ << " line " << __LINE__ << " leave SXF::NodeRegistry::~NodeRegistry() DESTRUCTOR\n";
}

// Register a particular element reader.
SXF::Element* SXF::NodeRegistry::bind(const char* type, SXF::Element* element)
{
std::cerr << "File " << __FILE__ << " line " << __LINE__ << " enter SXF::Element* SXF::NodeRegistry::bind(const char* type, SXF::Element* element)\n";
  int index  = hash(type);

  if(!element) {
    m_refOStream.cfe_error() 
      << "\n *** CFE Error: SXF::NodeRegistry::bind : element (" 
      << type << ") is NULL" << endl;
    return 0;
  }

  if(index < 0) {
    m_refOStream.cfe_error() 
      << "\n *** CFE Error: SXF::NodeRegistry::bind : element (" 
      << type << ") is not recognized" << endl;
    return 0;
  }

  if(m_aElements[index]){
    m_refOStream.cfe_error() 
      << "\n *** CFE Error: SXF::NodeRegistry::bind : element (" 
      << type << ") has been defined" << endl;
    return 0;
  }    
std::cerr << "File " << __FILE__ << " line " << __LINE__ << " leave SXF::Element* SXF::NodeRegistry::bind(const char* type, SXF::Element* element). index " << index << "\n";
  return m_aElements[index] = element;
}


// Return an element reader.
SXF::Element* SXF::NodeRegistry::getElement(const char* type)
{
  int index =  hash(type);

  SXF::Element* result = 0;
  if(index >= 0) { result = m_aElements[index]; }

  return result;
}

// Return a error element reader.
SXF::Element* SXF::NodeRegistry::getErrorElement()
{
  return m_pErrorElement;
}

// Return a sequence reader.
SXF::Sequence* SXF::NodeRegistry::getSequence()
{
  return m_pSequence;
}

// Map an element type to its index in the array of element readers.
int SXF::NodeRegistry::hash(const char* str) const
{
  SXF_Key* index = SXF_Perfect_Hash::sxf_elements_gperf(str, strlen(str));

  if(index) { return index->number; }
  else return -1;
}

// Allocate an array of element readers.
void SXF::NodeRegistry::allocateRegistry()
{
  m_iSize = SXF_Perfect_Hash::sxf_elements_gperf("$$$", 3)->number;
  m_aElements = new SXF::Element*[m_iSize];
  for(int i=0; i < m_iSize; i++){ m_aElements[i] = 0; }
}
