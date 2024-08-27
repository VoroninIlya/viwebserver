#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "vihtmlinput.hpp"

using namespace vihtmlformatter;

class Test_vihtmlinput : public ::testing::Test {};

TEST_F(Test_vihtmlinput, Test_TextInput_GetHtml)
{
  Input textInput{Input::InputTypes::text};
  ASSERT_EQ("", textInput.GetAttribute<std::string>("id"));
  ASSERT_EQ("", textInput.GetAttribute(Input::StringAttributes::id));
  ASSERT_EQ("<input type='text'>", textInput.GetHtml());

  textInput.SetAttribute(Input::StringAttributes::id, "test-id");
  ASSERT_EQ("test-id", textInput.GetAttribute<std::string>("id"));
  ASSERT_EQ("test-id", textInput.GetAttribute(Input::StringAttributes::id));
  ASSERT_EQ("<input type='text' id='test-id'>", textInput.GetHtml());

  textInput.SetAttribute("name", "test-name");
  ASSERT_EQ("test-name", textInput.GetAttribute<std::string>("name"));
  ASSERT_EQ("test-name", textInput.GetAttribute(Input::StringAttributes::name));
  ASSERT_EQ("<input type='text' id='test-id' name='test-name'>", textInput.GetHtml());

  textInput.SetAttribute(Input::StringAttributes::value, "test-value");
  ASSERT_EQ("test-value", textInput.GetAttribute<std::string>("value"));
  ASSERT_EQ("test-value", textInput.GetAttribute(Input::StringAttributes::value));
  ASSERT_EQ("<input type='text' id='test-id' name='test-name' \
value='test-value'>", textInput.GetHtml());

  textInput.SetAttribute(std::string("list"), "test-list");
  ASSERT_EQ("test-list", textInput.GetAttribute<std::string>("list"));
  ASSERT_EQ("test-list", textInput.GetAttribute(Input::StringAttributes::list));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
value='test-value'>", textInput.GetHtml());

  textInput.SetAttribute("pattern", "test-pattern");
  ASSERT_EQ("test-pattern", textInput.GetAttribute<std::string>("pattern"));
  ASSERT_EQ("test-pattern", textInput.GetAttribute(Input::StringAttributes::pattern));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' value='test-value'>", textInput.GetHtml());

  textInput.SetAttribute(Input::StringAttributes::placeholder, "test-placeholder");
  ASSERT_EQ("test-placeholder", textInput.GetAttribute<std::string>("placeholder"));
  ASSERT_EQ("test-placeholder", textInput.GetAttribute(Input::StringAttributes::placeholder));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value'>", 
textInput.GetHtml());

  textInput.SetAttribute("size", 5);
  ASSERT_EQ(5, textInput.GetAttribute<int32_t>("size"));
  ASSERT_EQ(5, textInput.GetAttribute(Input::NumericAttributes::size));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value' \
size='5'>", textInput.GetHtml());

  textInput.SetAttribute(Input::NumericAttributes::maxlength, 50);
  ASSERT_EQ(50, textInput.GetAttribute<int32_t>("maxlength"));
  ASSERT_EQ(50, textInput.GetAttribute(Input::NumericAttributes::maxlength));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value' \
maxlength='50' size='5'>", textInput.GetHtml());

  textInput.SetAttribute("readonly", true);
  ASSERT_EQ(true, textInput.GetAttribute<bool>("readonly"));
  ASSERT_EQ(true, textInput.GetAttribute(Input::BooleanAttributes::readonly));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value' \
maxlength='50' size='5' readonly>", textInput.GetHtml());

  textInput.SetAttribute(Input::BooleanAttributes::required, true);
  ASSERT_EQ(true, textInput.GetAttribute<bool>("required"));
  ASSERT_EQ(true, textInput.GetAttribute(Input::BooleanAttributes::required));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value' \
maxlength='50' size='5' readonly required>", textInput.GetHtml());

  textInput.SetAttribute(Input::BooleanAttributes::autofocus, true);
  ASSERT_EQ(true, textInput.GetAttribute<bool>("autofocus"));
  ASSERT_EQ(true, textInput.GetAttribute(Input::BooleanAttributes::autofocus));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value' \
maxlength='50' size='5' autofocus readonly required>", textInput.GetHtml());

  textInput.SetAttribute(Input::TextDir::rtl);
  ASSERT_EQ("rtl", textInput.GetAttribute<std::string>(std::string("dir")));
  ASSERT_EQ("rtl", textInput.GetAttribute(Input::StringAttributes::dir));
  ASSERT_EQ("<input type='text' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' value='test-value' \
dir='rtl' maxlength='50' size='5' autofocus readonly required>",
textInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_PasswordInput_GetHtml) {
  Input checkboxInput{Input::InputTypes::password};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    checkboxInput.SetAttribute(attr, attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    checkboxInput.SetAttribute(Input::EnumToStr(attr), i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    checkboxInput.SetAttribute(attr, true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    checkboxInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='password' class='test-class' id='test-id' \
name='test-name' pattern='test-pattern' placeholder='test-placeholder' \
style='test-style' title='test-title' value='test-value' maxlength='2' \
minlength='3' size='4' tabindex='10' autocomplete autofocus disabled \
readonly required onblur='test-event-onblur' onchange='test-event-onchange' \
onclick='test-event-onclick' ondrag='test-event-ondrag' \
ondragstart='test-event-ondragstart' ondrop='test-event-ondrop' \
onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' \
onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' \
onmousedown='test-event-onmousedown' onmouseenter='test-event-onmouseenter' \
onmouseleave='test-event-onmouseleave' onmousemove='test-event-onmousemove' \
onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", checkboxInput.GetHtml());

  checkboxInput.SetType(Input::InputTypes::password);
  checkboxInput.SetAttribute(Input::FormMethod::dialog);
  checkboxInput.SetAttribute(Input::TextDir::auto_);
  checkboxInput.SetAttribute(Input::InputMode::numeric);

  ASSERT_EQ("<input type='password' form='dialog' dir='auto'>", checkboxInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_SearchInput_GetHtml) {
  Input searchInput{Input::InputTypes::search};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    searchInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    searchInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    searchInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    searchInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='search' class='test-class' id='test-id' list='test-list' \
name='test-name' pattern='test-pattern' placeholder='test-placeholder' \
style='test-style' title='test-title' value='test-value' maxlength='2' minlength='3' \
size='4' tabindex='10' autocomplete autofocus disabled readonly required spellcheck \
onblur='test-event-onblur' onchange='test-event-onchange' onclick='test-event-onclick' \
ondrag='test-event-ondrag' ondragstart='test-event-ondragstart' ondrop='test-event-ondrop' \
onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' onkeypress='test-event-onkeypress' \
onkeyup='test-event-onkeyup' onmousedown='test-event-onmousedown' \
onmouseenter='test-event-onmouseenter' onmouseleave='test-event-onmouseleave' \
onmousemove='test-event-onmousemove' onmouseout='test-event-onmouseout' \
onmouseover='test-event-onmouseover' onmouseup='test-event-onmouseup'>", searchInput.GetHtml());

  searchInput.SetType(Input::InputTypes::search);
  searchInput.SetAttribute(Input::FormMethod::post);
  searchInput.SetAttribute(Input::TextDir::ltr);
  searchInput.SetAttribute(Input::InputMode::search);

  ASSERT_EQ("<input type='search' form='post' inputmode='search'>", searchInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_EmailInput_GetHtml) {
  Input emailInput{Input::InputTypes::email};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    emailInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    emailInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), std::to_string(i));
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    emailInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    emailInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='email' class='test-class' id='test-id' list='test-list' name='test-name' \
pattern='test-pattern' placeholder='test-placeholder' style='test-style' title='test-title' \
value='1' maxlength='2' minlength='3' size='4' tabindex='10' autocomplete autofocus \
disabled multiple readonly required spellcheck onblur='test-event-onblur' onchange='test-event-onchange' \
onclick='test-event-onclick' ondrag='test-event-ondrag' ondragstart='test-event-ondragstart' \
ondrop='test-event-ondrop' onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' \
onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' onmousedown='test-event-onmousedown' \
onmouseenter='test-event-onmouseenter' onmouseleave='test-event-onmouseleave' \
onmousemove='test-event-onmousemove' onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", emailInput.GetHtml());

  ASSERT_EQ("10", emailInput.GetAttribute<std::string>("tabindex"));
  ASSERT_EQ("test-event-onmouseout", emailInput.GetAttribute<std::string>("onmouseout"));

  emailInput.SetType(Input::InputTypes::email);
  emailInput.SetAttribute(Input::FormMethod::post);
  emailInput.SetAttribute(Input::TextDir::ltr);
  emailInput.SetAttribute(Input::InputMode::email);

  ASSERT_EQ("<input type='email' form='post' inputmode='email'>", emailInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_NumberInput_GetHtml) {
  Input numberInput{Input::InputTypes::number};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    numberInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    numberInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    numberInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    numberInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='number' class='test-class' id='test-id' list='test-list' \
name='test-name' placeholder='test-placeholder' style='test-style' title='test-title' \
value='test-value' max='6' mim='5' step='7' tabindex='10' autocomplete autofocus \
disabled readonly required onblur='test-event-onblur' onchange='test-event-onchange' \
onclick='test-event-onclick' ondrag='test-event-ondrag' ondragstart='test-event-ondragstart' \
ondrop='test-event-ondrop' onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' \
onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' \
onmousedown='test-event-onmousedown' onmouseenter='test-event-onmouseenter' \
onmouseleave='test-event-onmouseleave' onmousemove='test-event-onmousemove' \
onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", numberInput.GetHtml());

  numberInput.SetType(Input::InputTypes::number);
  numberInput.SetAttribute(std::string("form"), Input::FormMethod::post);
  numberInput.SetAttribute(Input::TextDir::ltr);
  numberInput.SetAttribute(Input::InputMode::decimal);

  ASSERT_EQ("<input type='number' form='post' inputmode='decimal'>", numberInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_RangeInput_GetHtml) {
  Input rangeInput{Input::InputTypes::range};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    rangeInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    rangeInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    rangeInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    rangeInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='range' class='test-class' id='test-id' list='test-list' \
name='test-name' style='test-style' title='test-title' value='test-value' max='6' \
mim='5' step='7' tabindex='10' autocomplete autofocus disabled required \
onblur='test-event-onblur' onchange='test-event-onchange' onclick='test-event-onclick' \
ondrag='test-event-ondrag' ondragstart='test-event-ondragstart' ondrop='test-event-ondrop' \
onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' \
onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' \
onmousedown='test-event-onmousedown' onmouseenter='test-event-onmouseenter' \
onmouseleave='test-event-onmouseleave' onmousemove='test-event-onmousemove' \
onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", rangeInput.GetHtml());

  rangeInput.SetType(Input::InputTypes::range);
  rangeInput.SetAttribute(Input::FormMethod::post);
  rangeInput.SetAttribute(std::string("dir"), Input::TextDir::ltr);
  rangeInput.SetAttribute(Input::InputMode::tel);

  ASSERT_EQ("<input type='range' form='post'>", rangeInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_CheckboxInput_GetHtml)
{
  Input checkboxInput{Input::InputTypes::checkbox};

  ASSERT_EQ("<input type='checkbox'>", checkboxInput.GetHtml());

  checkboxInput.SetAttribute(Input::StringAttributes::name, "test-name");
  checkboxInput.SetAttribute("checked", true);
  checkboxInput.SetAttribute(Input::BooleanAttributes::required, true);
  ASSERT_EQ("<input type='checkbox' name='test-name' checked required>", checkboxInput.GetHtml());

  checkboxInput.SetAttribute("name", "");
  checkboxInput.SetAttribute(Input::BooleanAttributes::checked, true);
  checkboxInput.SetAttribute("required", false);
  checkboxInput.SetAttribute("autofocus", true);
  ASSERT_EQ("<input type='checkbox' autofocus checked>", checkboxInput.GetHtml());

  checkboxInput.SetAttribute("id", "test-id");
  checkboxInput.SetAttribute("checked", false);
  checkboxInput.SetAttribute("required", true);
  checkboxInput.SetAttribute(Input::BooleanAttributes::autofocus, false);
  ASSERT_EQ("<input type='checkbox' id='test-id' required>", checkboxInput.GetHtml());

  checkboxInput.SetAttribute(Input::StringAttributes::name, "test-name");
  checkboxInput.SetAttribute("id", "test-id");
  checkboxInput.SetAttribute("checked", true);
  checkboxInput.SetAttribute(Input::BooleanAttributes::readonly, true);
  checkboxInput.SetAttribute("required", true);
  checkboxInput.SetAttribute(Input::BooleanAttributes::autofocus, true);
  ASSERT_EQ("<input type='checkbox' id='test-id' name='test-name' autofocus checked required>", checkboxInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_RadioInput_GetHtml) {
  Input radioInput{Input::InputTypes::radio};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    radioInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    radioInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    radioInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    radioInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='radio' class='test-class' id='test-id' name='test-name' \
style='test-style' title='test-title' value='test-value' tabindex='10' autocomplete \
autofocus checked disabled required onblur='test-event-onblur' \
onchange='test-event-onchange' onclick='test-event-onclick' ondrag='test-event-ondrag' \
ondragstart='test-event-ondragstart' ondrop='test-event-ondrop' onfocus='test-event-onfocus' \
onkeydown='test-event-onkeydown' onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' \
onmousedown='test-event-onmousedown' onmouseenter='test-event-onmouseenter' \
onmouseleave='test-event-onmouseleave' onmousemove='test-event-onmousemove' \
onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", radioInput.GetHtml());

  radioInput.SetType(Input::InputTypes::radio);
  radioInput.SetAttribute(Input::FormMethod::post);
  radioInput.SetAttribute(Input::TextDir::ltr);
  radioInput.SetAttribute(Input::InputMode::url);

  ASSERT_EQ("<input type='radio' form='post'>", radioInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_DateInput_GetHtml) {
  Input dateInput{Input::InputTypes::date};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    dateInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    dateInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    dateInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    dateInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='date' class='test-class' id='test-id' list='test-list' \
name='test-name' placeholder='test-placeholder' style='test-style' title='test-title' \
value='test-value' max='6' mim='5' step='7' tabindex='10' autocomplete autofocus \
disabled readonly required onblur='test-event-onblur' onchange='test-event-onchange' \
onclick='test-event-onclick' ondrag='test-event-ondrag' ondragstart='test-event-ondragstart' \
ondrop='test-event-ondrop' onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' \
onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' onmousedown='test-event-onmousedown' \
onmouseenter='test-event-onmouseenter' onmouseleave='test-event-onmouseleave' \
onmousemove='test-event-onmousemove' onmouseout='test-event-onmouseout' \
onmouseover='test-event-onmouseover' onmouseup='test-event-onmouseup'>", dateInput.GetHtml());

  dateInput.SetType(Input::InputTypes::date);
  dateInput.SetAttribute(Input::FormMethod::post);
  dateInput.SetAttribute(Input::TextDir::ltr);
  dateInput.SetAttribute(std::string("inputmode"), Input::InputMode::url);

  ASSERT_EQ("<input type='date' form='post' inputmode='url'>", dateInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_ColorInput_GetHtml) {
  Input colorInput{Input::InputTypes::color};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    colorInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    colorInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    colorInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    colorInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='color' class='test-class' id='test-id' list='test-list' \
name='test-name' style='test-style' title='test-title' value='test-value' tabindex='10' \
autocomplete autofocus disabled required onblur='test-event-onblur' \
onchange='test-event-onchange' onclick='test-event-onclick' ondrag='test-event-ondrag' \
ondragstart='test-event-ondragstart' ondrop='test-event-ondrop' onfocus='test-event-onfocus' \
onkeydown='test-event-onkeydown' onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' \
onmousedown='test-event-onmousedown' onmouseenter='test-event-onmouseenter' \
onmouseleave='test-event-onmouseleave' onmousemove='test-event-onmousemove' \
onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", colorInput.GetHtml());

  colorInput.SetType(Input::InputTypes::color);
  colorInput.SetAttribute(Input::FormMethod::post);
  colorInput.SetAttribute(Input::TextDir::ltr);
  colorInput.SetAttribute(Input::InputMode::text);

  ASSERT_EQ("<input type='color' form='post'>", colorInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_FileInput_GetHtml) {
  Input fileInput{Input::InputTypes::file};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    fileInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    fileInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    fileInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    fileInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='file' accept='test-accept' class='test-class' id='test-id' \
name='test-name' style='test-style' title='test-title' tabindex='10' autocomplete \
disabled multiple>", fileInput.GetHtml());

  fileInput.SetType(Input::InputTypes::file);
  fileInput.SetAttribute(Input::FormMethod::post);
  fileInput.SetAttribute(Input::TextDir::ltr);
  fileInput.SetAttribute(Input::InputMode::numeric);

  ASSERT_EQ("<input type='file' form='post'>", fileInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_DatetimelocalInput_GetHtml) {
  Input datetimelocalInput{Input::InputTypes::datetimelocal};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    datetimelocalInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    datetimelocalInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    datetimelocalInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    datetimelocalInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='datetimelocal' class='test-class' id='test-id' list='test-list' \
name='test-name' placeholder='test-placeholder' style='test-style' title='test-title' \
value='test-value' max='6' mim='5' step='7' tabindex='10' autocomplete autofocus \
disabled readonly required onblur='test-event-onblur' onchange='test-event-onchange' \
onclick='test-event-onclick' ondrag='test-event-ondrag' ondragstart='test-event-ondragstart' \
ondrop='test-event-ondrop' onfocus='test-event-onfocus' onkeydown='test-event-onkeydown' \
onkeypress='test-event-onkeypress' onkeyup='test-event-onkeyup' \
onmousedown='test-event-onmousedown' onmouseenter='test-event-onmouseenter' \
onmouseleave='test-event-onmouseleave' onmousemove='test-event-onmousemove' \
onmouseout='test-event-onmouseout' onmouseover='test-event-onmouseover' \
onmouseup='test-event-onmouseup'>", datetimelocalInput.GetHtml());

  datetimelocalInput.SetType(Input::InputTypes::datetimelocal);
  datetimelocalInput.SetAttribute(Input::FormMethod::post);
  datetimelocalInput.SetAttribute(Input::TextDir::ltr);
  datetimelocalInput.SetAttribute(Input::InputMode::numeric);

  ASSERT_EQ("<input type='datetimelocal' form='post' inputmode='numeric'>", datetimelocalInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_HiddenInput_GetHtml) {
  Input hiddenInput{Input::InputTypes::hidden};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    hiddenInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    hiddenInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    hiddenInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    hiddenInput.SetAttribute(attr, attrValue);
  }

  ASSERT_EQ("<input type='hidden' class='test-class' id='test-id' name='test-name' \
style='test-style' title='test-title'>", hiddenInput.GetHtml());

  hiddenInput.SetType(Input::InputTypes::hidden);
  hiddenInput.SetAttribute(Input::FormMethod::post);
  hiddenInput.SetAttribute(Input::TextDir::ltr);
  hiddenInput.SetAttribute(Input::InputMode::numeric);

  ASSERT_EQ("<input type='hidden' form='post'>", hiddenInput.GetHtml());
}

TEST_F(Test_vihtmlinput, Test_ButtonInput_GetHtml) {
  Input buttonInput{Input::InputTypes::button};

  for(int32_t i = 1; i < static_cast<int32_t>(Input::StringAttributes::SizeOfEnum); i++) {
    Input::StringAttributes attr = static_cast<Input::StringAttributes>(i);
    std::string attrValue = "test-" + Input::EnumToStr(attr);
    buttonInput.SetAttribute(attr, attrValue);
  }
  
  for(int32_t i = 1; i < static_cast<int32_t>(Input::NumericAttributes::SizeOfEnum); i++) {
    Input::NumericAttributes attr = static_cast<Input::NumericAttributes>(i);
    buttonInput.SetAttribute(attr, i);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::BooleanAttributes::SizeOfEnum); i++) {
    Input::BooleanAttributes attr = static_cast<Input::BooleanAttributes>(i);
    buttonInput.SetAttribute(Input::EnumToStr(attr).c_str(), true);
  }

  for(int32_t i = 1; i < static_cast<int32_t>(Input::EventAttributes::SizeOfEnum); i++) {
    Input::EventAttributes attr = static_cast<Input::EventAttributes>(i);
    std::string attrValue = "test-event-" + Input::EnumToStr(attr);
    buttonInput.SetAttribute<const std::string&>(Input::EnumToStr(attr), attrValue);
  }

  ASSERT_EQ("<input type='button' class='test-class' id='test-id' name='test-name' \
style='test-style' title='test-title' tabindex='10' disabled>", buttonInput.GetHtml());

  buttonInput.SetType(Input::InputTypes::button);
  buttonInput.SetAttribute(Input::FormMethod::post);
  buttonInput.SetAttribute(Input::TextDir::ltr);
  buttonInput.SetAttribute(Input::InputMode::numeric);

  ASSERT_EQ("<input type='button' form='post'>", buttonInput.GetHtml());
}
