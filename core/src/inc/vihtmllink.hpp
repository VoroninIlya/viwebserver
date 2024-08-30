/**
 * @file vihtmllink.hpp
 * @author Ilia Voronin (www.linkedin.com/in/ilia-voronin-7a169122a)
 * @brief 
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
#include <stdbool.h>
#include <cstddef>
#include <map>

namespace vihtmlformatter {

class Link : public IBaseHtmlElement {

public:

  enum class StringAttributes {
    none = 0,
    href,
    rel,
    type,
    media,
    hreflang,
    sizes,
    as,
    crossorigin,
    integrity,
    title,
    referrerpolicy,
    disabled,
    charset,
    rev,

    sizeofenum
  };

  enum class EventAttributes {
    none = 0,
    onload,
    onerror,

    sizeofenum
  };

  enum class Rel {
    none = 0,
    stylesheet,
    icon,
    alternate,
    author,
    dnsprefetch,
    preconnect,
    prefetch,
    preload,
    prerender,
    manifest,
    license,
    modulepreload,
    next,
    prev,
    bookmark,
    nofollow,
    noopener,
    noreferrer,
    ugc,
    sponsored,
    canonical,
    shortcuticon,
    alternatestylesheet,
    pingback,
    import,

    sizeofenum
};

  enum class Type {
    none = 0,
    textcss,
    texthtml,
    applicationjson,
    applicationldjson,
    applicationxml,
    imagepng,
    imagesvgxml,
    applicationjavascript,
    applicationxfontwoff,
    applicationfontwoff,
    applicationfontwoff2,
    fontwoff,
    fontwoff2,
    fontttf,
    fontotf,
    fonteot
};

  enum class ReferrerPolicy {
    none = 0,
    noreferrer,
    noreferrerwhendowngrade,
    origin,
    originwhencrossorigin,
    sameorigin,
    strictorigin,
    strictoriginwhencrossorigin,
    unsafeurl,

    sizeofenum
};

  enum class CrossOrigin {
    none = 0,
    anonymous,
    usecredentials
};

  static std::string EnumToStr(Link::StringAttributes enm);
  static std::string EnumToStr(Link::EventAttributes enm);
  static std::string EnumToStr(Link::Rel enm);
  static std::string EnumToStr(Link::Type enm);
  static std::string EnumToStr(Link::ReferrerPolicy enm);
  static std::string EnumToStr(Link::CrossOrigin enm);

  template<class T>
  static T StrToEnum(const std::string& str);

  void SetAttribute(const std::string& attr, const std::string& val);
  void SetAttribute(Link::StringAttributes attr, const std::string& val);
  void SetAttribute(Link::EventAttributes attr, const std::string& val);
  void SetAttribute(Link::Rel val);
  void SetAttribute(Link::Type val);
  void SetAttribute(Link::ReferrerPolicy val);
  void SetAttribute(Link::CrossOrigin val);

  template <class T>
  T GetAttribute();

  std::string GetAttribute(const std::string& attr);
  std::string GetAttribute(Link::StringAttributes attr);
  std::string GetAttribute(Link::EventAttributes attr);

  std::string GetHtml() const override;

private:
  std::map<std::string, std::string> m_strAttr{};
  std::map<std::string, std::string> m_eventsAttr{};
  std::pair<const std::string, Rel> m_relAttr{ "rel", Link::Rel::none };
  std::pair<const std::string, Type> m_typeAttr{ "type", Link::Type::none };
  std::pair<const std::string, ReferrerPolicy> m_refPolicyAttr{ "referrerpolicy", Link::ReferrerPolicy::none };
  std::pair<const std::string, CrossOrigin> m_crossorigAttr{ "crossorigin", Link::CrossOrigin::none };

  std::string m_custom;
};

}