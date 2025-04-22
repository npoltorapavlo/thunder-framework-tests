#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;

const auto kBase64 = "base64/with/forward/slash";
const auto kEscaped = "base64\\/with\\/forward\\/slash";
const auto kEscapedTwice = "base64\\\\\\/with\\\\\\/forward\\\\\\/slash";
const auto kQuotedBase64 = "\"" + string(kBase64) + "\"";
const auto kQuotedEscaped = "\"" + string(kEscaped) + "\"";
const auto kQuotedEscapedTwice = "\"" + string(kEscapedTwice) + "\"";

TEST(Base64, ToQuotedStringAddsQuotes)
{
    EXPECT_THAT(Core::ToQuotedString('\"', kBase64), Eq(kQuotedBase64));
}

TEST(Escaped, ToQuotedStringAddsQuotes)
{
    EXPECT_THAT(Core::ToQuotedString('\"', kEscaped), Eq(kQuotedEscaped));
}

TEST(JsonValueBase64, ValueIsSame)
{
    EXPECT_THAT(JsonValue(kBase64).Value(), Eq(kBase64));
}

TEST(JsonValueBase64, ToStringAddsQuotesAndEscapes)
{
    string str;
    JsonValue(kBase64).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonValueEscaped, ValueIsSame)
{
    EXPECT_THAT(JsonValue(kEscaped).Value(), Eq(kEscaped));
}

TEST(JsonValueEscaped, ToStringAddsQuotesAndEscapes)
{
    string str;
    JsonValue(kEscaped).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscapedTwice));
}

TEST(JsonValueFromStringQuotedBase64, ValueIsSame)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedBase64);
    EXPECT_THAT(jsonValue.Value(), Eq(kQuotedBase64));
}

TEST(JsonValueFromStringQuotedBase64, ToStringEscapes)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedBase64);
    string str;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonValueFromStringQuotedEscaped, ValueUnescapes)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedEscaped);
    EXPECT_THAT(jsonValue.Value(), Eq(kQuotedBase64));
}

TEST(JsonValueFromStringQuotedEscaped, ToStringIsSame)
{
    JsonValue jsonValue;
    jsonValue.FromString(kQuotedEscaped);
    string str;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringBase64, ValueIsSame)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kBase64);
    EXPECT_THAT(jsonString.Value(), Eq(kBase64));
}

TEST(JsonStringFromStringBase64, ToStringAddsQuotesAndEscapes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kBase64);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringEscaped, ValueIsSame)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kEscaped);
    EXPECT_THAT(jsonString.Value(), Eq(kEscaped));
}

TEST(JsonStringFromStringEscaped, ToStringAddsQuotesAndEscapes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kEscaped);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscapedTwice));
}

TEST(JsonStringFromStringQuotedBase64, ValueRemovesQuotes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedBase64);
    EXPECT_THAT(jsonString.Value(), Eq(kBase64));
}

TEST(JsonStringFromStringQuotedBase64, ToStringEscapes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedBase64);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringQuotedEscaped, ValueRemovesQuotesAndUnescapes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscaped);
    EXPECT_THAT(jsonString.Value(), Eq(kBase64));
}

TEST(JsonStringFromStringQuotedEscaped, ToStringIsSame)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscaped);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscaped));
}

TEST(JsonStringFromStringQuotedEscapedTwice, ValueRemovesQuotesAndUnescapes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscapedTwice);
    EXPECT_THAT(jsonString.Value(), Eq(kEscaped));
}

TEST(JsonStringFromStringQuotedEscapedTwice, ToStringIsSame)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kQuotedEscapedTwice);
    string str;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kQuotedEscapedTwice));
}
