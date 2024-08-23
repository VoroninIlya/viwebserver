/**
 * @file vihtmlformatter.hpp
 * @author Ilia Voronin (www.linkedin.com/in/ilia-voronin-7a169122a)
 * @brief Header file of htmlformatter
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

#include <vihtmlbase.hpp>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <vector>
#include <map>
#include <climits>

namespace vihtmlformatter {

class Label : public IHtmlElement {
public:
  Label(std::string forVal = "", std::string value = "");
  void SetFor(const std::string& forVal);
  void SetValue(const std::string& value);
  std::string GetHtml() const override;
private:
  std::string m_for{""};
  std::string m_value{""};
};

class HtmlGroup : public IHtmlElement {
public:
  std::string GetHtml() const override;
  std::string GetStyle() const override;
  std::string GetScript() const override;

private:
  std::map<std::string, IHtmlElement> elements;
  std::map<std::string, HtmlGroup> groups;
};

typedef struct {
  std::string charset{""};
  std::map<std::string,std::string> attr;
} Meta_t;

class Head : IBaseHtmlElement {
public:

  Head();
  std::string GetHtml() const;

private:
  std::string base;
  std::string title;
  Meta_t m_meta;

  std::map<std::string, IHtmlElement> elements;
  std::map<std::string, HtmlGroup> groups;
};

}