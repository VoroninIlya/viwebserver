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