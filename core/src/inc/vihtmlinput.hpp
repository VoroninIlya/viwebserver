/**
 * @file vihtmlinput.hpp
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
#include <vector>
#include <map>

namespace vihtmlformatter {

class Input : public IHtmlElement {

public:

  enum class InputTypes {
    text = 0,
    password,
    search,
    email,
    url,
    tel,
    number,
    checkbox,
    radio,
    date,
    color,
    file,
    range,
    time,
    month,
    datetimelocal,
    week,
    hidden,
    image,
    submit,
    reset,
    button,

    sizeofenum
  };

  enum class InputMode {
    none = 0,
    text,
    decimal,
    numeric,
    tel,
    search,
    email,
    url,

    sizeofenum
  };

  enum class FormMethod {
    none = 0,
    get,
    post,
    dialog,

    sizeofenum
  };

  enum class TextDir {
    none = 0,
    ltr,
    rtl,
    auto_,

    sizeofenum
  };

  enum class StringAttributes {
    none = 0,
    id,
    name,
    value,
    placeholder,
    pattern,
    list,
    accept,
    src,
    alt,
    inputmode,
    class_,
    style,
    title,
    form,
    dir,

    sizeofenum
  };

  enum class NumericAttributes {
    none = 0,
    value,
    maxlength,
    minlength,
    size,
    mim,
    max,
    step,
    height,
    width,
    tabindex,

    sizeofenum
  };

  enum class BooleanAttributes{
    none = 0,
    readonly,
    required,
    disabled,
    autocomplete,
    autofocus,
    multiple,
    checked,
    spellcheck,

    sizeofenum
  };

  enum class EventAttributes {
    none = 0,
    onchange,
    onclick,
    onfocus,
    onblur,
    onkeydown,
    onkeyup,
    onkeypress,
    onmousedown,
    onmouseup,
    onmouseover,
    onmouseout,
    onmousemove,
    onmouseenter,
    onmouseleave,
    ondragstart,
    ondrag,
    ondrop,

    sizeofenum
  };

  Input();
  Input(Input::InputTypes type) : m_type(type) {}

  template <class T>
  T StrToEnum(const std::string&);

  static std::string EnumToStr(Input::InputTypes enm);
  static std::string EnumToStr(Input::FormMethod enm);
  static std::string EnumToStr(Input::TextDir enm);
  static std::string EnumToStr(Input::InputMode enm);
  static std::string EnumToStr(Input::StringAttributes enm);
  static std::string EnumToStr(Input::NumericAttributes enm);
  static std::string EnumToStr(Input::BooleanAttributes enm);
  static std::string EnumToStr(Input::EventAttributes enm);

  void SetType(Input::InputTypes type);

  template <class T>
  void SetAttribute(const std::string& attrName, T val);

  template <class T>
  void SetAttribute(const char* attrName, T val);

  void SetAttribute(Input::StringAttributes attr, const std::string& val);
  void SetAttribute(Input::NumericAttributes attr, int32_t val);
  void SetAttribute(Input::BooleanAttributes attr, bool val);
  void SetAttribute(Input::EventAttributes attr, const std::string& val);
  void SetAttribute(Input::FormMethod val);
  void SetAttribute(Input::TextDir val);
  void SetAttribute(Input::InputMode val);

  template <class T>
  T GetAttribute(const std::string&);

  template <class T>
  T GetAttribute(); // TODO

  std::string GetAttribute(Input::StringAttributes attr);
  int32_t GetAttribute(Input::NumericAttributes attr);
  bool GetAttribute(Input::BooleanAttributes attr);
  std::string GetAttribute(Input::EventAttributes attr);

  std::string GetHtml() const override;
  std::string GetStyle() const override { return ""; } //TODO: implement
  std::string GetScript() const override { return ""; } //TODO: implement

private:
  InputTypes m_type{};

  std::map<std::string, std::string> m_strAttr{};
  std::map<std::string, int32_t> m_numAttr{};
  std::map<std::string, bool> m_boolAttr{};
  std::map<std::string, std::string> m_eventsAttr{};
  std::pair<const std::string, FormMethod> m_formAttr{ "form", Input::FormMethod::none };
  std::pair<const std::string, TextDir> m_dirAttr{ "dir", Input::TextDir::ltr };
  std::pair<const std::string, InputMode> m_inputModeAttr{ "inputmode", Input::InputMode::none };

  std::string m_custom;
};

}
