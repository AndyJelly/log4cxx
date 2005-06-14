/*
 * Copyright 2003,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOG4CXX_HELPERS_CHARSETENCODER_H
#define _LOG4CXX_HELPERS_CHARSETENCODER_H

#include <log4cxx/helpers/objectimpl.h>
#include <log4cxx/helpers/pool.h>

namespace log4cxx
{

        namespace helpers {
          class CharsetEncoder;
          typedef helpers::ObjectPtrT<CharsetEncoder> CharsetEncoderPtr;
          class ByteBuffer;


          /**
          *   An engine to transform LogStrings into bytes
          *     for the specific character set.
          */
          class LOG4CXX_EXPORT CharsetEncoder : public ObjectImpl
          {
          public:
                  DECLARE_ABSTRACT_LOG4CXX_OBJECT(CharsetEncoder)
                  BEGIN_LOG4CXX_CAST_MAP()
                          LOG4CXX_CAST_ENTRY(CharsetEncoder)
                  END_LOG4CXX_CAST_MAP()

          protected:
               /**
               *  Protected constructor.
               */
                  CharsetEncoder();

          public:
               /**
               * Destructor.
               */
                  virtual ~CharsetEncoder();
              /**
               *  Get encoder for default charset.
               */
                  static CharsetEncoderPtr getDefaultEncoder();

              /**
               *  Get encoder for specified character set.
               *  @param charset, the following values should be recognized:
               *     "US-ASCII", "ISO-8859-1", "UTF-8",
               *     "UTF-16BE", "UTF-16LE".
               *  @return encoder, may be null if charset was not recognized.
               */
                  static CharsetEncoderPtr getEncoder(const std::string& charset);

#if LOG4CXX_HAS_WCHAR_T
              /**
               *  Get encoder for wchar_t type.
               */
                  static CharsetEncoderPtr getWideEncoder();

              /**
               *  Get encoder for specified character set.
               *  @param charset, the following values should be recognized:
               *     "US-ASCII", "ISO-8859-1", "UTF-8",
               *     "UTF-16BE", "UTF-16LE".
               *  @return encoder, may be null if charset was not recognized.
               */
              static CharsetEncoderPtr getEncoder(const std::wstring& charset);
#endif

                  /**
                  * Encodes a string replacing unmappable
                  * characters with escape sequences.
                  *
                  */
                  static void encode(CharsetEncoderPtr& enc,
                      const LogString& src,
                      LogString::const_iterator& iter,
                      ByteBuffer& dst);

              /**
               * Encodes as many characters from the input string as possible
               *   to the output buffer.
                   *  @param in input string
               *  @param iter position in string to start.
               *  @param out output buffer.
               *  @return APR_SUCCESS unless a character can not be represented in
               *    the encoding.
               */
                  virtual log4cxx_status_t encode(const LogString& in,
                        LogString::const_iterator& iter,
                        ByteBuffer& out) = 0;

              /**
               *   Resets any internal state.
               */
                  virtual void reset();

              /**
               *   Flushes the encoder.
               */
                  virtual void flush(ByteBuffer& out);

              /**
               *   Determines if the return value from encode indicates
               *     an unconvertable character.
               */
                  inline static bool isError(log4cxx_status_t stat) {
                     return (stat != 0);
                  }


          private:
               /**
               *   Private copy constructor.
               */
                  CharsetEncoder(const CharsetEncoder&);
              /**
               *   Private assignment operator.
               */
                  CharsetEncoder& operator=(const CharsetEncoder&);

              static CharsetEncoder* createDefaultEncoder();
          };

        } // namespace helpers

}  //namespace log4cxx

#endif //_LOG4CXX_HELPERS_CHARSETENCODER_H