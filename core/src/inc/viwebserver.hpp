/**
 * @file viwebserver.hpp
 * @author Ilia Voronin (www.linkedin.com/in/ilia-voronin-7a169122a)
 * @brief Header file of web-server
 *
 * @copyright Copyright (c) 2024 Ilia Voronin
 * 
 * This software is licensed under GNU GENERAL PUBLIC LICENSE 
 * The terms can be found in the LICENSE file in
 * the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS,
 * Without warranty of any kind, express or implied, 
 * including but not limited to the warranties of merchantability, 
 * fitness for a particular purpose and noninfringement. 
 * In no event shall the authors or copyright holders be liable for any claim, 
 * damages or other liability, whether in an action of contract, tort or otherwise, 
 * arising from, out of or in connection with the software 
 * or the use or other dealings in the software.
 * 
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string>
#include <vector>
#include <map>
#include <climits>

namespace vivebserver {

  typedef enum {
    DEBUG_DISABLED = 0,  
    DEBUG_INFO
  } DebugLvl_t;

  typedef enum {
    ONESHOT_MEASURE = 0,  
    CONTINUOUS_MEASURE
  } MeasureMode_t;

  typedef int (*Printf_t) (const char *__format, ...);

  class WebServer 
  {
  public:
    WebServer();

    void SetPrintfCb(const Printf_t printfCb);

    void SetDebugLvl(const DebugLvl_t lvl);

  private:
    
    //std::string m_s;
    bool m_isInitialized{false};

    DebugLvl_t m_debugLvl{};
    Printf_t m_printfCb{};
  };
}

