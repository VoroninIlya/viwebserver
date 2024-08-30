#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "vihtmllink.hpp"

using namespace vihtmlformatter;

class Test_vihtmllink : public ::testing::Test {};

TEST_F(Test_vihtmllink, Test_TextInput_GetHtml)
{
  Link testLink{};

  ASSERT_EQ("<link>", testLink.GetHtml());

  testLink.SetAttribute(Link::StringAttributes::as, "test-as");
  testLink.SetAttribute(Link::StringAttributes::href, "test-heref");
  testLink.SetAttribute("media", "test-media");
  testLink.SetAttribute("title", "test-title");
  testLink.SetAttribute("onerror", "test-event-onerror");

  ASSERT_EQ("<link as='test-as' href='test-heref' media='test-media' title='test-title' \
onerror='test-event-onerror'>", testLink.GetHtml());

  testLink.SetAttribute(Link::EventAttributes::onload, "test-event-onload");
  testLink.SetAttribute(Link::Rel::author);
  testLink.SetAttribute(Link::Type::applicationxfontwoff);
  testLink.SetAttribute(Link::ReferrerPolicy::strictoriginwhencrossorigin);
  testLink.SetAttribute(Link::CrossOrigin::usecredentials);

  ASSERT_EQ("<link rel='author' type='application/x-font-woff' as='test-as' href='test-heref' \
media='test-media' title='test-title' referrerpolicy='strict-origin-when-cross-origin' \
crossorigin='use-credentials' onerror='test-event-onerror' \
onload='test-event-onload'>", testLink.GetHtml());

  for(int32_t i = 1; i < static_cast<int32_t>(Link::StringAttributes::sizeofenum); i++) {
    Link::StringAttributes attr = static_cast<Link::StringAttributes>(i);
    std::string attrValue = "test-" + Link::EnumToStr(attr);
    testLink.SetAttribute(attr, attrValue);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Link::EventAttributes::sizeofenum); i++) {
    Link::EventAttributes attr = static_cast<Link::EventAttributes>(i);
    std::string attrValue = "test-event-" + Link::EnumToStr(attr);
    testLink.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<link as='test-as' charset='test-charset' disabled='test-disabled' href='test-href' \
hreflang='test-hreflang' integrity='test-integrity' media='test-media' rev='test-rev' \
sizes='test-sizes' title='test-title' onerror='test-event-onerror' \
onload='test-event-onload'>", testLink.GetHtml());

  testLink.SetAttribute(Link::StringAttributes::as, "");
  testLink.SetAttribute(Link::StringAttributes::href, "");
  testLink.SetAttribute("media", "");
  testLink.SetAttribute("title", "");
  testLink.SetAttribute("onerror", "");

  testLink.SetAttribute("rel", "");
  testLink.SetAttribute(Link::Type::none);
  testLink.SetAttribute(Link::StringAttributes::referrerpolicy, "");
  testLink.SetAttribute(Link::CrossOrigin::none);

  ASSERT_EQ("<link charset='test-charset' disabled='test-disabled' hreflang='test-hreflang' \
integrity='test-integrity' rev='test-rev' sizes='test-sizes' \
onload='test-event-onload'>", testLink.GetHtml());
}

TEST_F(Test_vihtmllink, Test_TextInput_GetAtribute)
{
  Link testLink{};

  for(int32_t i = 1; i < static_cast<int32_t>(Link::StringAttributes::sizeofenum); i++) {
    Link::StringAttributes attr = static_cast<Link::StringAttributes>(i);
    ASSERT_EQ("", testLink.GetAttribute(attr));
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Link::EventAttributes::sizeofenum); i++) {
    Link::EventAttributes attr = static_cast<Link::EventAttributes>(i);
    ASSERT_EQ("", testLink.GetAttribute(attr));
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Link::StringAttributes::sizeofenum); i++) {
    Link::StringAttributes attr = static_cast<Link::StringAttributes>(i);
    std::string attrValue = "test-" + Link::EnumToStr(attr);
    testLink.SetAttribute(attr, attrValue);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Link::EventAttributes::sizeofenum); i++) {
    Link::EventAttributes attr = static_cast<Link::EventAttributes>(i);
    std::string attrValue = "test-event-" + Link::EnumToStr(attr);
    testLink.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<link as='test-as' charset='test-charset' disabled='test-disabled' href='test-href' \
hreflang='test-hreflang' integrity='test-integrity' media='test-media' rev='test-rev' \
sizes='test-sizes' title='test-title' onerror='test-event-onerror' \
onload='test-event-onload'>", testLink.GetHtml());

  testLink.SetAttribute(Link::Rel::canonical);
  testLink.SetAttribute(Link::Type::fontwoff2);
  testLink.SetAttribute(Link::ReferrerPolicy::originwhencrossorigin);
  testLink.SetAttribute(Link::CrossOrigin::anonymous);

  ASSERT_EQ("<link rel='canonical' type='font/woff2' as='test-as' charset='test-charset' \
disabled='test-disabled' href='test-href' hreflang='test-hreflang' integrity='test-integrity' \
media='test-media' rev='test-rev' sizes='test-sizes' title='test-title' \
referrerpolicy='origin-when-cross-origin' crossorigin='anonymous' onerror='test-event-onerror' \
onload='test-event-onload'>", testLink.GetHtml());

  ASSERT_EQ(Link::EnumToStr(Link::Rel::canonical), testLink.GetAttribute("rel"));
  ASSERT_EQ(Link::EnumToStr(Link::Rel::canonical), testLink.GetAttribute(Link::StringAttributes::rel));
  ASSERT_EQ(Link::Rel::canonical, testLink.GetAttribute<Link::Rel>());

  ASSERT_EQ(Link::EnumToStr(Link::Type::fontwoff2), testLink.GetAttribute("type"));
  ASSERT_EQ(Link::EnumToStr(Link::Type::fontwoff2), testLink.GetAttribute(Link::StringAttributes::type));
  ASSERT_EQ(Link::Type::fontwoff2, testLink.GetAttribute<Link::Type>());

  ASSERT_EQ(Link::EnumToStr(Link::ReferrerPolicy::originwhencrossorigin), testLink.GetAttribute("referrerpolicy"));
  ASSERT_EQ(Link::EnumToStr(Link::ReferrerPolicy::originwhencrossorigin), testLink.GetAttribute(Link::StringAttributes::referrerpolicy));
  ASSERT_EQ(Link::ReferrerPolicy::originwhencrossorigin, testLink.GetAttribute<Link::ReferrerPolicy>());

  ASSERT_EQ(Link::EnumToStr(Link::CrossOrigin::anonymous), testLink.GetAttribute("crossorigin"));
  ASSERT_EQ(Link::EnumToStr(Link::CrossOrigin::anonymous), testLink.GetAttribute(Link::StringAttributes::crossorigin));
  ASSERT_EQ(Link::CrossOrigin::anonymous, testLink.GetAttribute<Link::CrossOrigin>());

  for(int32_t i = 1; i < static_cast<int32_t>(Link::StringAttributes::sizeofenum); i++) {
    Link::StringAttributes attr = static_cast<Link::StringAttributes>(i);
    if(Link::StringAttributes::rel != attr && Link::StringAttributes::type != attr &&
      Link::StringAttributes::referrerpolicy != attr && Link::StringAttributes::crossorigin != attr) {
      ASSERT_EQ("test-" + Link::EnumToStr(attr), testLink.GetAttribute(attr));
    }
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Link::EventAttributes::sizeofenum); i++) {
    Link::EventAttributes attr = static_cast<Link::EventAttributes>(i);
      ASSERT_EQ("test-event-" + Link::EnumToStr(attr), testLink.GetAttribute(Link::EnumToStr(attr)));
  }
}

TEST_F(Test_vihtmllink, Test_EnumToStr_GetHtml)
{
  ASSERT_EQ("stylesheet",           Link::EnumToStr(Link::Rel::stylesheet));
  ASSERT_EQ("icon",                 Link::EnumToStr(Link::Rel::icon));
  ASSERT_EQ("alternate",            Link::EnumToStr(Link::Rel::alternate));
  ASSERT_EQ("author",               Link::EnumToStr(Link::Rel::author));
  ASSERT_EQ("dns-prefetch",         Link::EnumToStr(Link::Rel::dnsprefetch));
  ASSERT_EQ("preconnect",           Link::EnumToStr(Link::Rel::preconnect));
  ASSERT_EQ("prefetch",             Link::EnumToStr(Link::Rel::prefetch));
  ASSERT_EQ("preload",              Link::EnumToStr(Link::Rel::preload));
  ASSERT_EQ("prerender",            Link::EnumToStr(Link::Rel::prerender));
  ASSERT_EQ("manifest",             Link::EnumToStr(Link::Rel::manifest));
  ASSERT_EQ("license",              Link::EnumToStr(Link::Rel::license));
  ASSERT_EQ("modulepreload",        Link::EnumToStr(Link::Rel::modulepreload));
  ASSERT_EQ("next",                 Link::EnumToStr(Link::Rel::next));
  ASSERT_EQ("prev",                 Link::EnumToStr(Link::Rel::prev));
  ASSERT_EQ("bookmark",             Link::EnumToStr(Link::Rel::bookmark));
  ASSERT_EQ("nofollow",             Link::EnumToStr(Link::Rel::nofollow));
  ASSERT_EQ("noopener",             Link::EnumToStr(Link::Rel::noopener));
  ASSERT_EQ("noreferrer",           Link::EnumToStr(Link::Rel::noreferrer));
  ASSERT_EQ("ugc",                  Link::EnumToStr(Link::Rel::ugc));
  ASSERT_EQ("sponsored",            Link::EnumToStr(Link::Rel::sponsored));
  ASSERT_EQ("canonical",            Link::EnumToStr(Link::Rel::canonical));
  ASSERT_EQ("shortcut icon",        Link::EnumToStr(Link::Rel::shortcuticon));
  ASSERT_EQ("alternate stylesheet", Link::EnumToStr(Link::Rel::alternatestylesheet));
  ASSERT_EQ("pingback",             Link::EnumToStr(Link::Rel::pingback));
  ASSERT_EQ("import",               Link::EnumToStr(Link::Rel::import));
  ASSERT_EQ("",                     Link::EnumToStr(Link::Rel::none));

  ASSERT_EQ("text/css",                Link::EnumToStr(Link::Type::textcss));
  ASSERT_EQ("text/html",               Link::EnumToStr(Link::Type::texthtml));
  ASSERT_EQ("application/json",        Link::EnumToStr(Link::Type::applicationjson));
  ASSERT_EQ("application/ld+json",     Link::EnumToStr(Link::Type::applicationldjson));
  ASSERT_EQ("application/xml",         Link::EnumToStr(Link::Type::applicationxml));
  ASSERT_EQ("image/png",               Link::EnumToStr(Link::Type::imagepng));
  ASSERT_EQ("image/svg+xml",           Link::EnumToStr(Link::Type::imagesvgxml));
  ASSERT_EQ("application/javascript",  Link::EnumToStr(Link::Type::applicationjavascript));
  ASSERT_EQ("application/x-font-woff", Link::EnumToStr(Link::Type::applicationxfontwoff));
  ASSERT_EQ("application/font-woff",   Link::EnumToStr(Link::Type::applicationfontwoff));
  ASSERT_EQ("application/font-woff2",  Link::EnumToStr(Link::Type::applicationfontwoff2));
  ASSERT_EQ("font/woff",               Link::EnumToStr(Link::Type::fontwoff));
  ASSERT_EQ("font/woff2",              Link::EnumToStr(Link::Type::fontwoff2));
  ASSERT_EQ("font/ttf",                Link::EnumToStr(Link::Type::fontttf));
  ASSERT_EQ("font/otf",                Link::EnumToStr(Link::Type::fontotf));
  ASSERT_EQ("font/eot",                Link::EnumToStr(Link::Type::fonteot));
  ASSERT_EQ("",                        Link::EnumToStr(Link::Type::none));

  ASSERT_EQ("no-referrer",                     Link::EnumToStr(Link::ReferrerPolicy::noreferrer));
  ASSERT_EQ("no-referrer-when-downgrade",      Link::EnumToStr(Link::ReferrerPolicy::noreferrerwhendowngrade));
  ASSERT_EQ("origin",                          Link::EnumToStr(Link::ReferrerPolicy::origin));
  ASSERT_EQ("origin-when-cross-origin",        Link::EnumToStr(Link::ReferrerPolicy::originwhencrossorigin));
  ASSERT_EQ("same-origin",                     Link::EnumToStr(Link::ReferrerPolicy::sameorigin));
  ASSERT_EQ("strict-origin",                   Link::EnumToStr(Link::ReferrerPolicy::strictorigin));
  ASSERT_EQ("strict-origin-when-cross-origin", Link::EnumToStr(Link::ReferrerPolicy::strictoriginwhencrossorigin));
  ASSERT_EQ("unsafe-url",                      Link::EnumToStr(Link::ReferrerPolicy::unsafeurl));
}

