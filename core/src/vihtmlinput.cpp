/**
 * @file vihtmlinput.cpp
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

#include <algorithm>
#include <sstream>
#include "vihtmlinput.hpp"

namespace vihtmlformatter {
  using StrAtt = Input::StringAttributes;
  using NumAtt = Input::NumericAttributes;
  using BooAtt = Input::BooleanAttributes;
  using EvtAtt = Input::EventAttributes;

  static std::map<Input::InputTypes, const std::vector<StrAtt>> allowedStringAttr {
    {Input::InputTypes::text,          {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder, StrAtt::pattern, StrAtt::dir    }},
    {Input::InputTypes::password,      {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                 , StrAtt::value, StrAtt::placeholder, StrAtt::pattern, StrAtt::dir    }},
    {Input::InputTypes::search,        {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder, StrAtt::pattern, StrAtt::dir    }},
    {Input::InputTypes::email,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder, StrAtt::pattern, StrAtt::dir    }},
    {Input::InputTypes::url,           {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder, StrAtt::pattern, StrAtt::dir    }},
    {Input::InputTypes::tel,           {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder, StrAtt::pattern, StrAtt::dir    }},
    {Input::InputTypes::number,        {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder                 , StrAtt::dir    }},
    {Input::InputTypes::range,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list                   , StrAtt::value                                      ,                }},
    {Input::InputTypes::date,          {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder                 ,                }},
    {Input::InputTypes::time,          {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder                 ,                }},
    {Input::InputTypes::month,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder                 ,                }},
    {Input::InputTypes::datetimelocal, {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder                 ,                }},
    {Input::InputTypes::week,          {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list, StrAtt::inputmode, StrAtt::value, StrAtt::placeholder                 ,                }},
    {Input::InputTypes::checkbox,      {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                 , StrAtt::value                                      ,                }},
    {Input::InputTypes::radio,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                 , StrAtt::value                                      ,                }},
    {Input::InputTypes::color,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_, StrAtt::list                   , StrAtt::value                                      ,                }},
    {Input::InputTypes::hidden,        {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                                                                      ,                }},
    {Input::InputTypes::file,          {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                                                                      , StrAtt::accept }},
    {Input::InputTypes::image,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                 , StrAtt::value                     , StrAtt::src    , StrAtt::alt    }},
    {Input::InputTypes::submit,        {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                                                                      ,                }},
    {Input::InputTypes::reset,         {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                                                                      ,                }},
    {Input::InputTypes::button,        {StrAtt::id, StrAtt::name, StrAtt::form, StrAtt::style, StrAtt::title, StrAtt::class_                                                                                      ,                }},
  };

  static std::map<Input::InputTypes, const std::vector<NumAtt>> allowedNumericAttr {
    {Input::InputTypes::text,          {NumAtt::tabindex,                                         NumAtt::maxlength, NumAtt::minlength, NumAtt::size,}},
    {Input::InputTypes::password,      {NumAtt::tabindex,                                         NumAtt::maxlength, NumAtt::minlength, NumAtt::size,}},
    {Input::InputTypes::search,        {NumAtt::tabindex,                                         NumAtt::maxlength, NumAtt::minlength, NumAtt::size,}},
    {Input::InputTypes::email,         {NumAtt::tabindex,                                         NumAtt::maxlength, NumAtt::minlength, NumAtt::size,}},
    {Input::InputTypes::url,           {NumAtt::tabindex,                                         NumAtt::maxlength, NumAtt::minlength, NumAtt::size,}},
    {Input::InputTypes::tel,           {NumAtt::tabindex,                                         NumAtt::maxlength, NumAtt::minlength, NumAtt::size,}},
    {Input::InputTypes::number,        {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::range,         {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::date,          {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::time,          {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::month,         {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::datetimelocal, {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::week,          {NumAtt::tabindex, NumAtt::mim, NumAtt::max, NumAtt::step                                                     }},
    {Input::InputTypes::checkbox,      {NumAtt::tabindex,                                                                                            }},
    {Input::InputTypes::radio,         {NumAtt::tabindex,                                                                                            }},
    {Input::InputTypes::color,         {NumAtt::tabindex,                                                                                            }},
    {Input::InputTypes::hidden,        {                                                                                                             }},
    {Input::InputTypes::file,          {NumAtt::tabindex,                                                                                            }},
    {Input::InputTypes::image,         {NumAtt::tabindex,                                         NumAtt::height   , NumAtt::width                   }},
    {Input::InputTypes::submit,        {NumAtt::tabindex,                                                                                            }},
    {Input::InputTypes::reset,         {NumAtt::tabindex,                                                                                            }},
    {Input::InputTypes::button,        {NumAtt::tabindex,                                                                                            }},
  };

  static std::map<Input::InputTypes, const std::vector<BooAtt>> allowedBooleanAttr {
    {Input::InputTypes::text,          {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly, BooAtt::spellcheck                  , }},
    {Input::InputTypes::password,      {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::search,        {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly, BooAtt::spellcheck                  , }},
    {Input::InputTypes::email,         {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly, BooAtt::spellcheck, BooAtt::multiple, }},
    {Input::InputTypes::url,           {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly, BooAtt::spellcheck                  , }},
    {Input::InputTypes::tel,           {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly, BooAtt::spellcheck                  , }},
    {Input::InputTypes::number,        {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::range,         {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required                                                        , }},
    {Input::InputTypes::date,          {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::time,          {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::month,         {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::datetimelocal, {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::week,          {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required, BooAtt::readonly                                      , }},
    {Input::InputTypes::checkbox,      {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required                                      , BooAtt::checked , }},
    {Input::InputTypes::radio,         {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required                                      , BooAtt::checked , }},
    {Input::InputTypes::color,         {BooAtt::disabled, BooAtt::autocomplete, BooAtt::autofocus, BooAtt::required                                                        , }},
    {Input::InputTypes::hidden,        {                                                                                                                                     }},
    {Input::InputTypes::file,          {BooAtt::disabled, BooAtt::autocomplete                                                                           , BooAtt::multiple, }},
    {Input::InputTypes::image,         {BooAtt::disabled, BooAtt::autocomplete                                                                                             , }},
    {Input::InputTypes::submit,        {BooAtt::disabled                                                                                                                   , }},
    {Input::InputTypes::reset,         {BooAtt::disabled                                                                                                                   , }},
    {Input::InputTypes::button,        {BooAtt::disabled                                                                                                                   , }},
  };

  static std::map<Input::InputTypes, const std::vector<EvtAtt>> allowedEventsAttr {
    {Input::InputTypes::text,          {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::password,      {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::search,        {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::email,         {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::url,           {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::tel,           {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::number,        {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::range,         {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::date,          {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::time,          {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::month,         {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::datetimelocal, {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::week,          {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::checkbox,      {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::radio,         {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::color,         {EvtAtt::onchange, EvtAtt::onclick, EvtAtt::onfocus, EvtAtt::onblur, EvtAtt::onkeydown, EvtAtt::onkeyup, EvtAtt::onkeypress, EvtAtt::onmousedown, EvtAtt::onmouseup, EvtAtt::onmouseover, EvtAtt::onmouseout, EvtAtt::onmousemove, EvtAtt::onmouseenter, EvtAtt::onmouseleave, EvtAtt::ondragstart, EvtAtt::ondrag, EvtAtt::ondrop}},
    {Input::InputTypes::hidden,        {                                                                                                                                                                                                                                                                                                                                 }},
    {Input::InputTypes::file,          {                                                                                                                                                                                                                                                                                                                                 }},
    {Input::InputTypes::image,         {                                                                                                                                                                                                                                                                                                                                 }},
    {Input::InputTypes::submit,        {                                                                                                                                                                                                                                                                                                                                 }},
    {Input::InputTypes::reset,         {                                                                                                                                                                                                                                                                                                                                 }},
    {Input::InputTypes::button,        {                                                                                                                                                                                                                                                                                                                                 }},
  };

  template <>
  Input::FormMethod Input::StrToEnum<Input::FormMethod>(const std::string& str) {
    if("get" == str) return FormMethod::get;
    else if("post" == str) return FormMethod::post;
    else if("dialog" == str) return FormMethod::dialog;
    return FormMethod::none;
  }

  template <>
  Input::TextDir Input::StrToEnum<Input::TextDir>(const std::string& str) {
    if("ltr" == str) return TextDir::ltr;
    else if("rtl" == str) return TextDir::rtl;
    else if("auto" == str) return TextDir::auto_;
    return TextDir::none;
  }

  template <>
  Input::InputMode Input::StrToEnum<Input::InputMode>(const std::string& str) {
    if("text" == str) return InputMode::text;
    else if("decimal" == str) return InputMode::decimal;
    else if("numeric" == str) return InputMode::numeric;
    else if("tel" == str) return InputMode::tel;
    else if("search" == str) return InputMode::search;
    else if("email" == str) return InputMode::email;
    else if("url" == str) return InputMode::url;
    return InputMode::none;
  }

  template <>
  Input::StringAttributes Input::StrToEnum<Input::StringAttributes>(const std::string& str) {
    if("id" == str) return StringAttributes::id;
    else if("name" == str) return StringAttributes::name;
    else if("value" == str) return StringAttributes::value;
    else if("placeholder" == str) return StringAttributes::placeholder;
    else if("pattern" == str) return StringAttributes::pattern;
    else if("list" == str) return StringAttributes::list;
    else if("accept" == str) return StringAttributes::accept;
    else if("src" == str) return StringAttributes::src;
    else if("alt" == str) return StringAttributes::alt;
    else if("inputmode" == str) return StringAttributes::inputmode;
    else if("class" == str) return StringAttributes::class_;
    else if("style" == str) return StringAttributes::style;
    else if("title" == str) return StringAttributes::title;
    else if("form" == str) return StringAttributes::form;
    else if("dir" == str) return StringAttributes::dir;
    return StringAttributes::none;
  }

  template <>
  Input::NumericAttributes Input::StrToEnum<Input::NumericAttributes>(const std::string& str) {
    if("value" == str) return NumericAttributes::value;
    else if("maxlength" == str) return NumericAttributes::maxlength;
    else if("minlength" == str) return NumericAttributes::minlength;
    else if("size" == str) return NumericAttributes::size;
    else if("mim" == str) return NumericAttributes::mim;
    else if("max" == str) return NumericAttributes::max;
    else if("step" == str) return NumericAttributes::step;
    else if("height" == str) return NumericAttributes::height;
    else if("width" == str) return NumericAttributes::width;
    else if("tabindex" == str) return NumericAttributes::tabindex;
    return NumericAttributes::none;
  }

  template <>
  Input::BooleanAttributes Input::StrToEnum<Input::BooleanAttributes>(const std::string& str) {
    if("readonly" == str) return BooleanAttributes::readonly;
    else if("required" == str) return BooleanAttributes::required;
    else if("disabled" == str) return BooleanAttributes::disabled;
    else if("autocomplete" == str) return BooleanAttributes::autocomplete;
    else if("autofocus" == str) return BooleanAttributes::autofocus;
    else if("multiple" == str) return BooleanAttributes::multiple;
    else if("checked" == str) return BooleanAttributes::checked;
    else if("spellcheck" == str) return BooleanAttributes::spellcheck;
    return BooleanAttributes::none;
  }

  template <>
  Input::EventAttributes Input::StrToEnum<Input::EventAttributes>(const std::string& str) {
    if("onchange" == str) return EventAttributes::onchange;
    else if("onclick" == str) return EventAttributes::onclick;
    else if("onfocus" == str) return EventAttributes::onfocus;
    else if("onblur" == str) return EventAttributes::onblur;
    else if("onkeydown" == str) return EventAttributes::onkeydown;
    else if("onkeyup" == str) return EventAttributes::onkeyup;
    else if("onkeypress" == str) return EventAttributes::onkeypress;
    else if("onmousedown" == str) return EventAttributes::onmousedown;
    else if("onmouseup" == str) return EventAttributes::onmouseup;
    else if("onmouseover" == str) return EventAttributes::onmouseover;
    else if("onmouseout" == str) return EventAttributes::onmouseout;
    else if("onmousemove" == str) return EventAttributes::onmousemove;
    else if("onmouseenter" == str) return EventAttributes::onmouseenter;
    else if("onmouseleave" == str) return EventAttributes::onmouseleave;
    else if("ondragstart" == str) return EventAttributes::ondragstart;
    else if("ondrag" == str) return EventAttributes::ondrag;
    else if("ondrop" == str) return EventAttributes::ondrop;
    return EventAttributes::none;
  }

  std::string Input::EnumToStr(Input::InputTypes enm) {
    switch (enm) {
      case InputTypes::text: return "text";
      case InputTypes::password: return "password";
      case InputTypes::search: return "search";
      case InputTypes::email: return "email";
      case InputTypes::url: return "url";
      case InputTypes::tel: return "tel";
      case InputTypes::number: return "number";
      case InputTypes::checkbox: return "checkbox";
      case InputTypes::radio: return "radio";
      case InputTypes::date: return "date";
      case InputTypes::color: return "color";
      case InputTypes::file: return "file";
      case InputTypes::range: return "range";
      case InputTypes::time: return "time";
      case InputTypes::month: return "month";
      case InputTypes::datetimelocal: return "datetimelocal";
      case InputTypes::week: return "week";
      case InputTypes::hidden: return "hidden";
      case InputTypes::image: return "image";
      case InputTypes::submit: return "submit";
      case InputTypes::reset: return "reset";
      case InputTypes::button: return "button";
      default: return "none";
    }
  }

  std::string Input::EnumToStr(FormMethod enm) {
    switch (enm) {
      case FormMethod::get: return "get";
      case FormMethod::post: return "post";
      case FormMethod::dialog: return "dialog";
      default: return "none";
    }
  }

  std::string Input::EnumToStr(TextDir enm) {
    switch (enm) {
      case TextDir::ltr: return "ltr";
      case TextDir::rtl: return "rtl";
      case TextDir::auto_: return "auto";
      default: return "none";
    }
  }

  std::string Input::EnumToStr(InputMode enm) {
    switch (enm) {
      case InputMode::none: return "none";
      case InputMode::text: return "text";
      case InputMode::decimal: return "decimal";
      case InputMode::numeric: return "numeric";
      case InputMode::tel: return "tel";
      case InputMode::search: return "search";
      case InputMode::email: return "email";
      case InputMode::url: return "url";
      default: return "none";
    }
  }

  std::string Input::EnumToStr(StringAttributes enm) {
    switch (enm) {
      case StringAttributes::id: return "id";
      case StringAttributes::name: return "name";
      case StringAttributes::value: return "value";
      case StringAttributes::placeholder: return "placeholder";
      case StringAttributes::pattern: return "pattern";
      case StringAttributes::list: return "list";
      case StringAttributes::accept: return "accept";
      case StringAttributes::src: return "src";
      case StringAttributes::alt: return "alt";
      case StringAttributes::inputmode: return "inputmode";
      case StringAttributes::class_: return "class";
      case StringAttributes::style: return "style";
      case StringAttributes::title: return "title";
      case StringAttributes::form: return "form";
      case StringAttributes::dir: return "dir";
      default: return "none";
    }
  }

  std::string Input::EnumToStr(NumericAttributes enm) {
    switch (enm) {
      case NumericAttributes::value: return "value";
      case NumericAttributes::maxlength: return "maxlength";
      case NumericAttributes::minlength: return "minlength";
      case NumericAttributes::size: return "size";
      case NumericAttributes::mim: return "mim";
      case NumericAttributes::max: return "max";
      case NumericAttributes::step: return "step";
      case NumericAttributes::height: return "height";
      case NumericAttributes::width: return "width";
      case NumericAttributes::tabindex: return "tabindex";
      default: return "";
    }
  }

  std::string Input::EnumToStr(BooleanAttributes enm) {
    switch (enm) {
      case BooleanAttributes::readonly: return "readonly";
      case BooleanAttributes::required: return "required";
      case BooleanAttributes::disabled: return "disabled";
      case BooleanAttributes::autocomplete: return "autocomplete";
      case BooleanAttributes::autofocus: return "autofocus";
      case BooleanAttributes::multiple: return "multiple";
      case BooleanAttributes::checked: return "checked";
      case BooleanAttributes::spellcheck: return "spellcheck";
      default: return "";
    }
  }

  std::string Input::EnumToStr(EventAttributes enm) {
    switch (enm) {
      case EventAttributes::onchange: return "onchange";
      case EventAttributes::onclick: return "onclick";
      case EventAttributes::onfocus: return "onfocus";
      case EventAttributes::onblur: return "onblur";
      case EventAttributes::onkeydown: return "onkeydown";
      case EventAttributes::onkeyup: return "onkeyup";
      case EventAttributes::onkeypress: return "onkeypress";
      case EventAttributes::onmousedown: return "onmousedown";
      case EventAttributes::onmouseup: return "onmouseup";
      case EventAttributes::onmouseover: return "onmouseover";
      case EventAttributes::onmouseout: return "onmouseout";
      case EventAttributes::onmousemove: return "onmousemove";
      case EventAttributes::onmouseenter: return "onmouseenter";
      case EventAttributes::onmouseleave: return "onmouseleave";
      case EventAttributes::ondragstart: return "ondragstart";
      case EventAttributes::ondrag: return "ondrag";
      case EventAttributes::ondrop: return "ondrop";
    default: return "";
    }
  }

  void Input::SetType(InputTypes type) {
    m_type = type;

    m_strAttr.clear();
    m_numAttr.clear();
    m_boolAttr.clear();
    m_eventsAttr.clear();
    m_formAttr.second = FormMethod::none;
    m_dirAttr.second = TextDir::ltr;
    m_custom.clear();
  }

  template <>
  void Input::SetAttribute<const std::string&>(const std::string& attrName, const std::string& val) {

    Input::StringAttributes strAttr = StrToEnum<Input::StringAttributes>(attrName);
    if(Input::StringAttributes::none != strAttr)
      return SetAttribute(strAttr, val);

    Input::NumericAttributes numAttr = StrToEnum<Input::NumericAttributes>(attrName);
    if(Input::NumericAttributes::none != numAttr)
      return SetAttribute(numAttr, atoi(val.c_str()));

    Input::EventAttributes evtAttr = StrToEnum<Input::EventAttributes>(attrName);
      if(Input::EventAttributes::none != evtAttr)
      return SetAttribute(evtAttr, val);
  }

  template <>
  void Input::SetAttribute<const char*>(const std::string& attrName, const char* val) {
    SetAttribute<const std::string&>(attrName, std::string(val));
  }

  template <>
  void Input::SetAttribute<int32_t>(const std::string& attrName, int32_t val) {
    Input::NumericAttributes numAttr = StrToEnum<Input::NumericAttributes>(attrName);
    if(Input::NumericAttributes::none != numAttr)
      return SetAttribute(numAttr, val);
  }

  template <>
  void Input::SetAttribute<bool>(const std::string& attrName, bool val) {
    Input::BooleanAttributes boolAttr = StrToEnum<Input::BooleanAttributes>(attrName);
    if(Input::BooleanAttributes::none != boolAttr)
      return SetAttribute(boolAttr, val);
  }

  template <>
  void Input::SetAttribute<Input::FormMethod>(const std::string& attrName, FormMethod val) {
    Input::StringAttributes strAttr = StrToEnum<Input::StringAttributes>(attrName);
    if (Input::StringAttributes::form == strAttr)
      return SetAttribute(val);
  }

  template <>
  void Input::SetAttribute<Input::TextDir>(const std::string& attrName, TextDir val) {
    Input::StringAttributes strAttr = StrToEnum<Input::StringAttributes>(attrName);
    if (Input::StringAttributes::dir == strAttr)
      return SetAttribute(val);
  }

  template <>
  void Input::SetAttribute<Input::InputMode>(const std::string& attrName, InputMode val) {
    Input::StringAttributes strAttr = StrToEnum<Input::StringAttributes>(attrName);
    if (Input::StringAttributes::inputmode == strAttr)
      return SetAttribute(val);
  }

  template <>
  void Input::SetAttribute<const char*>(const char* attrName, const char* val) {
    SetAttribute<const char*>(std::string(attrName), val);
  }

  template <>
  void Input::SetAttribute<int32_t>(const char* attrName, int32_t val) {
    SetAttribute<int32_t>(std::string(attrName), val);
  }

  template <>
  void Input::SetAttribute<bool>(const char* attrName, bool val) {
    SetAttribute<bool>(std::string(attrName), val);
  }

  void Input::SetAttribute(StringAttributes attr, const std::string& val) {
    //check if attribute allowed for the input type
    auto allowed = allowedStringAttr[m_type];
    if(std::find(allowed.begin(), allowed.end(), attr) == allowed.end())
      return;

    if (Input::StringAttributes::form == attr) {
      auto formVal = StrToEnum<Input::FormMethod>(val);
      if(Input::FormMethod::none != formVal)
        return SetAttribute(formVal);
    }
    else if (Input::StringAttributes::dir == attr) {
      auto dirVal = StrToEnum<Input::TextDir>(val);
      if(Input::TextDir::none != dirVal)
        return SetAttribute(dirVal);
    }
    else if (Input::StringAttributes::inputmode == attr) {
      auto inputModeVal = StrToEnum<Input::InputMode>(val);
      if(Input::InputMode::none != inputModeVal)
        return SetAttribute(inputModeVal);
    }
    else {
      std::string key = EnumToStr(attr);
      if(val.empty() && m_strAttr.contains(key)) {
        m_strAttr.erase(key);
        return;
      }
      m_strAttr[key] = val;
    }
  } 

  void Input::SetAttribute(NumericAttributes attr, int32_t val) {

    auto allowed = allowedNumericAttr[m_type];
    if(std::find(allowed.begin(), allowed.end(), attr) == allowed.end())
      return;

    std::string key = EnumToStr(attr);
    if(INT32_MIN == val && m_numAttr.contains(key)) {
      m_numAttr.erase(key);
      return;
    }

    m_numAttr[key] = val;
  }

  void Input::SetAttribute(BooleanAttributes attr, bool val) {

    auto allowed = allowedBooleanAttr[m_type];
    if(std::find(allowed.begin(), allowed.end(), attr) == allowed.end())
      return;

    std::string key = EnumToStr(attr);
    if(false == val && m_boolAttr.contains(key)) {
      m_boolAttr.erase(key);
      return;
    }
    
    m_boolAttr[key] = val;
  }

  void Input::SetAttribute(EventAttributes attr, const std::string& val) {
    
    auto allowed = allowedEventsAttr[m_type];
    if(std::find(allowed.begin(), allowed.end(), attr) == allowed.end())
      return;

    std::string key = EnumToStr(attr);
    if(val.empty() && m_strAttr.contains(key)) {
      m_eventsAttr.erase(key);
      return;
    }

    m_eventsAttr[EnumToStr(attr)] = val;
  }

  void Input::SetAttribute(FormMethod val) {
    m_formAttr.second = val;
  }

  void Input::SetAttribute(TextDir val) {
    auto allowed = allowedStringAttr[m_type];
    if(std::find(allowed.begin(), allowed.end(), StringAttributes::dir) == allowed.end())
      return;
    m_dirAttr.second = val;
  }

  void Input::SetAttribute(InputMode val) {
    auto allowed = allowedStringAttr[m_type];
    if(std::find(allowed.begin(), allowed.end(), StringAttributes::inputmode) == allowed.end())
      return;
    m_inputModeAttr.second = val;
  }

  template<>
  std::string Input::GetAttribute<std::string>(const std::string& attrName) {
    Input::StringAttributes strAttr = StrToEnum<Input::StringAttributes>(attrName);
    if(Input::StringAttributes::none != strAttr)
      return GetAttribute(strAttr);

    Input::NumericAttributes numAttr = StrToEnum<Input::NumericAttributes>(attrName);
    if(Input::NumericAttributes::none != numAttr)
      return std::to_string(GetAttribute(numAttr));

    Input::EventAttributes evtAttr = StrToEnum<Input::EventAttributes>(attrName);
    if(Input::EventAttributes::none != evtAttr)
      return GetAttribute(evtAttr);

    return "";
  }

  template<>
  int32_t Input::GetAttribute<int32_t>(const std::string& attrName) {
    Input::NumericAttributes numAttr = StrToEnum<Input::NumericAttributes>(attrName);
    if(numAttr != Input::NumericAttributes::none)
      return GetAttribute(numAttr);

    return INT32_MIN;
  }

  template<>
  bool Input::GetAttribute<bool>(const std::string& attrName) {
    Input::BooleanAttributes boolAttr = StrToEnum<Input::BooleanAttributes>(attrName);
    if(boolAttr != Input::BooleanAttributes::none)
      return GetAttribute(boolAttr);

    return false;
  }

  std::string Input::GetAttribute(StringAttributes attr) {
    if(attr == StringAttributes::form)
      return EnumToStr(m_formAttr.second);
    else if(attr == StringAttributes::dir)
      return EnumToStr(m_dirAttr.second);
    else if(attr == StringAttributes::inputmode)
      return EnumToStr(m_inputModeAttr.second);

    return m_strAttr.find(EnumToStr(attr)) != m_strAttr.end() ? m_strAttr[EnumToStr(attr)] : "";
  }

  int32_t Input::GetAttribute(NumericAttributes attr) {
    return m_numAttr.find(EnumToStr(attr)) != m_numAttr.end() ? m_numAttr[EnumToStr(attr)] : INT32_MIN;
  }

  bool Input::GetAttribute(BooleanAttributes attr) {
    return m_boolAttr.find(EnumToStr(attr)) != m_boolAttr.end() ? m_boolAttr[EnumToStr(attr)] : false;
  }

  std::string Input::GetAttribute(EventAttributes attr) {
    return m_eventsAttr.find(EnumToStr(attr)) != m_eventsAttr.end() ? m_eventsAttr[EnumToStr(attr)] : "";
  }

  std::string Input::GetHtml() const {
    std::stringstream res; 
    res << "<input " <<
    "type='" << EnumToStr(m_type) << "'";

    for(const auto& att : m_strAttr) {
      res << " " << att.first << "='" << att.second << "'";
    }

    if(m_formAttr.second != Input::FormMethod::none)
      res << " " << m_formAttr.first << "='" << EnumToStr(m_formAttr.second) << "'";

    if(m_dirAttr.second > Input::TextDir::ltr)
      res << " " << m_dirAttr.first << "='" << EnumToStr(m_dirAttr.second) << "'";

    if(m_inputModeAttr.second != Input::InputMode::none)
      res << " " << m_inputModeAttr.first << "='" << EnumToStr(m_inputModeAttr.second) << "'";

    for(const auto& att : m_numAttr) {
      res << " " << att.first << "='" << std::to_string(att.second) << "'";
    }

    for(const auto& att : m_boolAttr) {
      if(att.second)
        res << " " << att.first;
    }

    for(const auto& att : m_eventsAttr) {
      res << " " << att.first << "='" << att.second << "'";
    }

    res << m_custom;

    res << ">";
    return res.str();
  }

}