#include "vihtmllink.hpp"
#include <sstream>

namespace vihtmlformatter {

  std::string Link::EnumToStr(Link::StringAttributes enm){
    switch (enm) {
      case Link::StringAttributes::href: return "href";
      case Link::StringAttributes::rel: return "rel";
      case Link::StringAttributes::type: return "type";
      case Link::StringAttributes::media: return "media";
      case Link::StringAttributes::hreflang: return "hreflang";
      case Link::StringAttributes::sizes: return "sizes";
      case Link::StringAttributes::as: return "as";
      case Link::StringAttributes::crossorigin: return "crossorigin";
      case Link::StringAttributes::integrity: return "integrity";
      case Link::StringAttributes::title: return "title";
      case Link::StringAttributes::referrerpolicy: return "referrerpolicy";
      case Link::StringAttributes::disabled: return "disabled";
      case Link::StringAttributes::charset: return "charset";
      case Link::StringAttributes::rev: return "rev";
      default: return "";
    }
  }

  std::string Link::EnumToStr(Link::EventAttributes enm) {
    switch (enm) {
      case Link::EventAttributes::onload: return "onload";
      case Link::EventAttributes::onerror: return "onerror";
      default: return "";
    }
  }

  std::string Link::EnumToStr(Link::Rel enm) {
    switch (enm) {
      case Link::Rel::stylesheet: return "stylesheet";
      case Link::Rel::icon: return "icon";
      case Link::Rel::alternate: return "alternate";
      case Link::Rel::author: return "author";
      case Link::Rel::dnsprefetch: return "dns-prefetch";
      case Link::Rel::preconnect: return "preconnect";
      case Link::Rel::prefetch: return "prefetch";
      case Link::Rel::preload: return "preload";
      case Link::Rel::prerender: return "prerender";
      case Link::Rel::manifest: return "manifest";
      case Link::Rel::license: return "license";
      case Link::Rel::modulepreload: return "modulepreload";
      case Link::Rel::next: return "next";
      case Link::Rel::prev: return "prev";
      case Link::Rel::bookmark: return "bookmark";
      case Link::Rel::nofollow: return "nofollow";
      case Link::Rel::noopener: return "noopener";
      case Link::Rel::noreferrer: return "noreferrer";
      case Link::Rel::ugc: return "ugc";
      case Link::Rel::sponsored: return "sponsored";
      case Link::Rel::canonical: return "canonical";
      case Link::Rel::shortcuticon: return "shortcut icon";
      case Link::Rel::alternatestylesheet: return "alternate stylesheet";
      case Link::Rel::pingback: return "pingback";
      case Link::Rel::import: return "import";
      default: return "";
    }
  }

  std::string Link::EnumToStr(Link::Type enm) {
    switch (enm) {
      case Link::Type::textcss: return "text/css";
      case Link::Type::texthtml: return "text/html";
      case Link::Type::applicationjson: return "application/json";
      case Link::Type::applicationldjson: return "application/ld+json";
      case Link::Type::applicationxml: return "application/xml";
      case Link::Type::imagepng: return "image/png";
      case Link::Type::imagesvgxml: return "image/svg+xml";
      case Link::Type::applicationjavascript: return "application/javascript";
      case Link::Type::applicationxfontwoff: return "application/x-font-woff";
      case Link::Type::applicationfontwoff: return "application/font-woff";
      case Link::Type::applicationfontwoff2: return "application/font-woff2";
      case Link::Type::fontwoff: return "font/woff";
      case Link::Type::fontwoff2: return "font/woff2";
      case Link::Type::fontttf: return "font/ttf";
      case Link::Type::fontotf: return "font/otf";
      case Link::Type::fonteot: return "font/eot";
      default: return "";
    }
  }

  std::string Link::EnumToStr(Link::ReferrerPolicy enm) {
    switch (enm) {
      case Link::ReferrerPolicy::noreferrer: return "no-referrer";
      case Link::ReferrerPolicy::noreferrerwhendowngrade: return "no-referrer-when-downgrade";
      case Link::ReferrerPolicy::origin: return "origin";
      case Link::ReferrerPolicy::originwhencrossorigin: return "origin-when-cross-origin";
      case Link::ReferrerPolicy::sameorigin: return "same-origin";
      case Link::ReferrerPolicy::strictorigin: return "strict-origin";
      case Link::ReferrerPolicy::strictoriginwhencrossorigin: return "strict-origin-when-cross-origin";
      case Link::ReferrerPolicy::unsafeurl: return "unsafe-url";
      default: return "";
    }
  }

  std::string Link::EnumToStr(Link::CrossOrigin enm) {
    switch (enm) {
      case Link::CrossOrigin::anonymous: return "anonymous";
      case Link::CrossOrigin::usecredentials: return "use-credentials";
      default: return "";
    }
  }

  template<>
  Link::StringAttributes Link::StrToEnum<Link::StringAttributes>(const std::string& str) {
    if("href" == str) return StringAttributes::href;
    else if("rel" == str) return StringAttributes::rel;
    else if("type" == str) return StringAttributes::type;
    else if("media" == str) return StringAttributes::media;
    else if("hreflang" == str) return StringAttributes::hreflang;
    else if("sizes" == str) return StringAttributes::sizes;
    else if("as" == str) return StringAttributes::as;
    else if("crossorigin" == str) return StringAttributes::crossorigin;
    else if("integrity" == str) return StringAttributes::integrity;
    else if("title" == str) return StringAttributes::title;
    else if("referrerpolicy" == str) return StringAttributes::referrerpolicy;
    else if("disabled" == str) return StringAttributes::disabled;
    else if("charset" == str) return StringAttributes::charset;
    else if("rev" == str) return StringAttributes::rev;
    return StringAttributes::none;
  }

  template<>
  Link::EventAttributes Link::StrToEnum<Link::EventAttributes>(const std::string& str) {
    if("onload" == str) return EventAttributes::onload;
    else if("onerror" == str) return EventAttributes::onerror;
    return EventAttributes::none;
  }

  template<>
  Link::Rel Link::StrToEnum<Link::Rel>(const std::string& str) {
    if("stylesheet" == str) return Rel::stylesheet;
    else if("icon" == str) return Rel::icon;
    else if("alternate" == str) return Rel::alternate;
    else if("author" == str) return Rel::author;
    else if("dns-prefetch" == str) return Rel::dnsprefetch;
    else if("preconnect" == str) return Rel::preconnect;
    else if("prefetch" == str) return Rel::prefetch;
    else if("preload" == str) return Rel::preload;
    else if("prerender" == str) return Rel::prerender;
    else if("manifest" == str) return Rel::manifest;
    else if("license" == str) return Rel::license;
    else if("modulepreload" == str) return Rel::modulepreload;
    else if("next" == str) return Rel::next;
    else if("prev" == str) return Rel::prev;
    else if("bookmark" == str) return Rel::bookmark;
    else if("nofollow" == str) return Rel::nofollow;
    else if("noopener" == str) return Rel::noopener;
    else if("noreferrer" == str) return Rel::noreferrer;
    else if("ugc" == str) return Rel::ugc;
    else if("sponsored" == str) return Rel::sponsored;
    else if("canonical" == str) return Rel::canonical;
    else if("shortcut icon" == str) return Rel::shortcuticon;
    else if("alternate stylesheet" == str) return Rel::alternatestylesheet;
    else if("pingback" == str) return Rel::pingback;
    else if("import" == str) return Rel::import;
    return Rel::none;
  }

  template<>
  Link::Type Link::StrToEnum<Link::Type>(const std::string& str) {
    if("text/css" == str) return Type::textcss;
    else if("text/html" == str) return Type::texthtml;
    else if("application/json" == str) return Type::applicationjson;
    else if("application/ld+json" == str) return Type::applicationldjson;
    else if("application/xml" == str) return Type::applicationxml;
    else if("image/png" == str) return Type::imagepng;
    else if("image/svg+xml" == str) return Type::imagesvgxml;
    else if("application/javascript" == str) return Type::applicationjavascript;
    else if("application/x-font-woff" == str) return Type::applicationxfontwoff;
    else if("application/font-woff" == str) return Type::applicationfontwoff;
    else if("application/font-woff2" == str) return Type::applicationfontwoff2;
    else if("font/woff" == str) return Type::fontwoff;
    else if("font/woff2" == str) return Type::fontwoff2;
    else if("font/ttf" == str) return Type::fontttf;
    else if("font/otf" == str) return Type::fontotf;
    else if("font/eot" == str) return Type::fonteot;
    return Type::none;
  }

  template<>
  Link::ReferrerPolicy Link::StrToEnum<Link::ReferrerPolicy>(const std::string& str) {
    if("no-referrer" == str) return ReferrerPolicy::noreferrer;
    else if("no-referrer-when-downgrade" == str) return ReferrerPolicy::noreferrerwhendowngrade;
    else if("origin" == str) return ReferrerPolicy::origin;
    else if("origin-when-cross-origin" == str) return ReferrerPolicy::originwhencrossorigin;
    else if("same-origin" == str) return ReferrerPolicy::sameorigin;
    else if("strict-origin" == str) return ReferrerPolicy::strictorigin;
    else if("strict-origin-when-cross-origin" == str) return ReferrerPolicy::strictoriginwhencrossorigin;
    else if("unsafe-url" == str) return ReferrerPolicy::unsafeurl;
    return ReferrerPolicy::none;
  }

  template<>
  Link::CrossOrigin Link::StrToEnum<Link::CrossOrigin>(const std::string& str) {
    if("anonymous" == str) return CrossOrigin::anonymous;
    else if("use-credentials" == str) return CrossOrigin::usecredentials;
    return CrossOrigin::none;
  }

  void Link::SetAttribute(const std::string& attr, const std::string& val) {
    Link::StringAttributes strAttr = StrToEnum<Link::StringAttributes>(attr);
    if(Link::StringAttributes::none != strAttr)
      return SetAttribute(strAttr, val);

    Link::EventAttributes evtAttr = StrToEnum<Link::EventAttributes>(attr);
    if(Link::EventAttributes::none != evtAttr)
      return SetAttribute(evtAttr, val);
  }

  void Link::SetAttribute(Link::StringAttributes attr, const std::string& val) {

    if (Link::StringAttributes::rel == attr) {
      auto relVal = StrToEnum<Link::Rel>(val);
      return SetAttribute(relVal);
    }
    else if (Link::StringAttributes::type == attr) {
      auto typeVal = StrToEnum<Link::Type>(val);
      return SetAttribute(typeVal);
    }
    else if (Link::StringAttributes::referrerpolicy == attr) {
      auto refpolVal = StrToEnum<Link::ReferrerPolicy>(val);
      return SetAttribute(refpolVal);
    }
    else if (Link::StringAttributes::crossorigin == attr) {
      auto crosOrigVal = StrToEnum<Link::CrossOrigin>(val);
      return SetAttribute(crosOrigVal);
    }else {
      std::string key = EnumToStr(attr);
      if(val.empty() && m_strAttr.contains(key)) {
        m_strAttr.erase(key);
        return;
      }
      m_strAttr[key] = val;
    }
  }

  void Link::SetAttribute(Link::EventAttributes attr, const std::string& val) {
    std::string key = EnumToStr(attr);
      if(val.empty() && m_eventsAttr.contains(key)) {
        m_eventsAttr.erase(key);
        return;
      }
      m_eventsAttr[key] = val;
  }

  void Link::SetAttribute(Link::Rel val) {
    m_relAttr.second = val;
  }

  void Link::SetAttribute(Link::Type val) {
    m_typeAttr.second = val;
  }

  void Link::SetAttribute(Link::ReferrerPolicy val) {
    m_refPolicyAttr.second = val;
  }

  void Link::SetAttribute(Link::CrossOrigin val) {
    m_crossorigAttr.second = val;
  }

  template <>
  Link::Rel Link::GetAttribute<Link::Rel>() {
    return m_relAttr.second;
  }

  template <>
  Link::Type Link::GetAttribute<Link::Type>() {
    return m_typeAttr.second;
  }

  template <>
  Link::ReferrerPolicy Link::GetAttribute<Link::ReferrerPolicy>() {
    return m_refPolicyAttr.second;
  }

  template <>
  Link::CrossOrigin Link::GetAttribute<Link::CrossOrigin>() {
    return m_crossorigAttr.second;
  }

  std::string Link::GetAttribute(const std::string& attr) {
    Link::StringAttributes strAttr = StrToEnum<Link::StringAttributes>(attr);
    if(Link::StringAttributes::none != strAttr)
      return GetAttribute(strAttr);

    Link::EventAttributes evtAttr = StrToEnum<Link::EventAttributes>(attr);
    if(Link::EventAttributes::none != evtAttr)
      return GetAttribute(evtAttr);

    return "";
  }

  std::string Link::GetAttribute(Link::StringAttributes attr) {
    if(StringAttributes::rel == attr)
      return EnumToStr(m_relAttr.second);
    else if(Link::StringAttributes::type == attr)
      return EnumToStr(m_typeAttr.second);
    else if(Link::StringAttributes::referrerpolicy == attr)
      return EnumToStr(m_refPolicyAttr.second);
    else if(Link::StringAttributes::crossorigin == attr)
      return EnumToStr(m_crossorigAttr.second);

    return m_strAttr.find(EnumToStr(attr)) != m_strAttr.end() ? m_strAttr[EnumToStr(attr)] : "";
  }

  std::string Link::GetAttribute(Link::EventAttributes attr) {
    return m_eventsAttr.find(EnumToStr(attr)) != m_eventsAttr.end() ? m_eventsAttr[EnumToStr(attr)] : "";
  }

  std::string Link::GetHtml() const {
    std::stringstream res; 
    res << "<link";
    if(m_relAttr.second != Link::Rel::none)
      res << " " << "rel='" << EnumToStr(m_relAttr.second) << "'";
    
    if(m_typeAttr.second != Link::Type::none)
      res << " " << "type='" << EnumToStr(m_typeAttr.second) << "'";

    for(const auto& att : m_strAttr) {
      res << " " << att.first << "='" << att.second << "'";
    }

    if(m_typeAttr.second != Link::Type::none)
      res << " " << "referrerpolicy='" << EnumToStr(m_refPolicyAttr.second) << "'";

    if(m_typeAttr.second != Link::Type::none)
      res << " " << "crossorigin='" << EnumToStr(m_crossorigAttr.second) << "'";

    for(const auto& att : m_eventsAttr) {
      res << " " << att.first << "='" << att.second << "'";
    }

    res << m_custom;

    res << ">";
    return res.str();
  }

}