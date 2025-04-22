#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;

const auto kUnescaped = "55b2C9AZ/WxhTsrLIQFA1hN9YAA";
const auto kEscaped = "55b2C9AZ\\/WxhTsrLIQFA1hN9YAA";
const auto kQuotedUnescaped = "\"55b2C9AZ/WxhTsrLIQFA1hN9YAA\"";
const auto kQuotedEscaped = "\"55b2C9AZ\\/WxhTsrLIQFA1hN9YAA\"";
const auto kQuotedEscapedTwice = "\"55b2C9AZ\\\\\\/WxhTsrLIQFA1hN9YAA\"";
const auto kQuotedEmpty = "\"\"";

TEST(Unescaped, ToQuotedStringIsQuotedUnescaped)
{
    EXPECT_THAT(Core::ToQuotedString('\"', kUnescaped), Eq(kQuotedUnescaped));
}

TEST(Escaped, ToQuotedStringIsQuotedEscaped)
{
    EXPECT_THAT(Core::ToQuotedString('\"', kEscaped), Eq(kQuotedEscaped));
}

TEST(JsonValueUnescaped, ValueIsUnescaped)
{
    EXPECT_THAT(JsonValue(kUnescaped).Value(), Eq(kUnescaped));
}

TEST(JsonValueUnescaped, ToStringIsQuotedEscaped)
{
    string str;
    JsonValue(kUnescaped).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonValueEscaped, ValueIsEscaped)
{
    EXPECT_THAT(JsonValue(kEscaped).Value(), Eq(kEscaped));
}

TEST(JsonValueEscaped, ToStringIsQuotedEscapedTwice)
{
    string str;
    JsonValue(kEscaped).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscapedTwice));
}

TEST(JsonValueFromStringQuotedUnescaped, ValueIsQuotedUnescaped)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedUnescaped);
    EXPECT_THAT(jsonValue.Value(), Eq(kQuotedUnescaped));
}

TEST(JsonValueFromStringQuotedUnescaped, ToStringIsQuotedEscaped)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedUnescaped);
    string str;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonValueFromStringQuotedEscaped, ValueIsQuotedUnescaped)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedEscaped);
    EXPECT_THAT(jsonValue.Value(), Eq(kQuotedUnescaped));
}

TEST(JsonValueFromStringQuotedEscaped, ToStringIsQuotedEscaped)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedEscaped);
    string str;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringUnescaped, ValueIsUnescaped)
{
    EXPECT_THAT(Core::JSON::String(kUnescaped).Value(), Eq(kUnescaped));
}

TEST(JsonStringUnescaped, ToStringIsQuotedEmpty)
{
    string str;
    Core::JSON::String(kUnescaped).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEmpty));
}

TEST(JsonStringQuotedUnescaped, ValueIsQuotedUnescaped)
{
    EXPECT_THAT(Core::JSON::String(kQuotedUnescaped).Value(), Eq(kQuotedUnescaped));
}

TEST(JsonStringQuotedUnescaped, ToStringIsQuotedEmpty)
{
    string str;
    Core::JSON::String(kQuotedUnescaped).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEmpty));
}

TEST(JsonStringEscaped, ValueIsEscaped)
{
    EXPECT_THAT(Core::JSON::String(kEscaped).Value(), Eq(kEscaped));
}

TEST(JsonStringEscaped, ToStringIsQuotedEmpty)
{
    string str;
    Core::JSON::String(kEscaped).ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEmpty));
}

TEST(JsonStringQuotedEscaped, ValueIsQuotedEscaped)
{
    EXPECT_THAT(Core::JSON::String(kQuotedEscaped).Value(), Eq(kQuotedEscaped));
}

TEST(JsonStringQuotedEscaped, ToStringIsQuotedEmpty)
{
    string str;
    Core::JSON::String(kQuotedEscaped).ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEmpty));
}

TEST(JsonStringFromStringQuotedUnescaped, ValueIsUnescaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedUnescaped);
    EXPECT_THAT(jsonString.Value(), Eq(kUnescaped));
}

TEST(JsonStringFromStringQuotedUnescaped, ToStringIsQuotedEscaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedUnescaped);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringQuotedEscaped, ValueIsUnescaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscaped);
    EXPECT_THAT(jsonString.Value(), Eq(kUnescaped));
}

TEST(JsonStringFromStringQuotedEscaped, ToStringIsQuotedEscaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscaped);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringUnescaped, ValueIsUnescaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kUnescaped);
    EXPECT_THAT(jsonString.Value(), Eq(kUnescaped));
}

TEST(JsonStringFromStringUnescaped, ToStringIsQuotedEscaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kUnescaped);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringEscaped, ValueIsEscaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kEscaped);
    EXPECT_THAT(jsonString.Value(), Eq(kEscaped));
}

TEST(JsonStringFromStringEscaped, ToStringIsQuotedEscapedTwice)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kEscaped);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscapedTwice));
}

TEST(JsonStringFromStringQuotedEscapedTwice, ValueIsEscaped)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscapedTwice);
    EXPECT_THAT(jsonString.Value(), Eq(kEscaped));
}

TEST(JsonStringFromStringQuotedEscapedTwice, ToStringIsQuotedEscapedTwice)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscapedTwice);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscapedTwice));
}
