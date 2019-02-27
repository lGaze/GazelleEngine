/**************************************************************************/
/* @filename gzException.h
/* @author Victor Flores 
/* @date 2019/02/26
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"

namespace gzEngineSDK {

#if GZ_COMPILER == GZ_COMPILER_MSVC
# pragma warning( push )
# pragma warning( disable : 4275 )
#endif

  class Exception : public std::exception
  {
   public:
     /**
      * @brief 
      */
    Exception(const char * type, const String& description, const String& source)
      : m_typeName(type),
      m_description(description),
      m_source(source) {}

    /**
     * @brief 
     */
    Exception(const char* type,
              const String& description,
              const String& source,
              const char* file,
              long line)
      : m_line(line),
        m_typeName(type),
        m_description(description),
        m_source(source),
        m_file(file),
        m_fullDesc("") {}

    /**
     * @brief 
     */
    Exception(const Exception& rhs)
      : m_line(rhs.m_line),
      m_typeName(rhs.m_typeName),
      m_description(rhs.m_description),
      m_source(rhs.m_source),
      m_file(rhs.m_file),
      m_fullDesc(rhs.m_fullDesc) {}

    /**
     * @brief 
     */
    ~Exception() _NOEXCEPT = default;

    /************************************************************************/
    /* Overladed Operators                                                  */
    /************************************************************************/

    /**
     * @brief 
     */
    Exception&
      operator=(const Exception& rhs) {
      m_description = rhs.m_description;
      m_source = rhs.m_source;
      m_file = rhs.m_file;
      m_line = rhs.m_line;
      m_typeName = rhs.m_typeName;
      m_fullDesc = rhs.m_fullDesc;
      return *this;
    }

    /************************************************************************/
    /* exception functions                                                  */
    /************************************************************************/

    /**
     * @brief 
     */
    virtual const String&
      getSource() const {
      return m_source;
    }

    /**
     * @brief 
     */
    virtual const String&
      getFile() const {
      return m_file;
    }

    /**
     * @brief 
     */
    virtual long
      getLine() const {
      return m_line;
    }

    /**
     * @brief 
     */
    virtual const String&
      getDescription(void) const {
      return m_description;
    }


    /************************************************************************/
    /* Member functions                                                     */
    /************************************************************************/

   protected:

     /**
      * @brief 
      */
     long m_line = 0;

     /**
      * @brief 
      */
     String m_typeName;

     /**
      * @brief 
      */
     String m_description;

     /**
      * @brief 
      */
     String m_source;

     /**
      * @brief 
      */
     String m_file;

     /**
      * @brief 
      */
     mutable String m_fullDesc;
  };
  
}


