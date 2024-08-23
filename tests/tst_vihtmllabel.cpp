#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "vihtmllabel.hpp"

class Test_vihtmllabel : public ::testing::Test
{
protected:
	void SetUp(std::string forVal = "", std::string value = "")
	{
    m_label.forValue = forVal;
    m_label.value = value;
	}
	void TearDown()
	{

	}
  vihtmlformatter::Label m_label{};
};

TEST_F(Test_vihtmllabel, TestGetHtml)
{
  SetUp();
  ASSERT_EQ("<label></label>", m_label.GetHtml());

  SetUp("test-for");
  ASSERT_EQ("<label for='test-for'></label>", m_label.GetHtml());

  SetUp("test-for", "test-value");
  ASSERT_EQ("<label for='test-for'>test-value</label>", m_label.GetHtml());

  SetUp("", "test-value");
  ASSERT_EQ("<label>test-value</label>", m_label.GetHtml());
}