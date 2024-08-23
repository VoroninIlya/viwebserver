/**
 * @file vihtmlbase.hpp
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

#include <string>

namespace vihtmlformatter {

struct IBaseHtmlElement {
public:
  virtual std::string GetHtml() const = 0;
};

struct IHtmlElement : public IBaseHtmlElement {
public:
  virtual std::string GetStyle() const = 0;
  virtual std::string GetScript() const = 0;
};

}