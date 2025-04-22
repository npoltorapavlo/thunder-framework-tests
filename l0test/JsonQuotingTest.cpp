#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;

namespace {
const auto kText = "Text";
const auto kTextQuoted = "\"" + string(kText) + "\"";
const auto kTextQuotedTwice = "\"\\\"" + string(kText) + "\\\"\"";
const auto kEmptyQuoted = "\"\"";
}

TEST(ToQuotedString, Quotes)
{
    EXPECT_THAT(Core::ToQuotedString('\"', kText), Eq(kTextQuoted));
    EXPECT_THAT(Core::ToQuotedString('\"', kTextQuoted), Eq(kTextQuotedTwice));
    // not checking for kTextQuotedTwice - would be triple quoted
}

TEST(JsonValue, ConstructorDoesntChangeQuotes)
{
    EXPECT_THAT(JsonValue(kText).Value(), Eq(kText));
    EXPECT_THAT(JsonValue(kTextQuoted).Value(), Eq(kTextQuoted));
    EXPECT_THAT(JsonValue(kTextQuotedTwice).Value(), Eq(kTextQuotedTwice));
}

TEST(JsonString, ConstructorDoesntChangeQuotes)
{
    EXPECT_THAT(Core::JSON::String(kText).Value(), Eq(kText));
    EXPECT_THAT(Core::JSON::String(kTextQuoted).Value(), Eq(kTextQuoted));
    EXPECT_THAT(Core::JSON::String(kTextQuotedTwice).Value(), Eq(kTextQuotedTwice));
}

TEST(JsonValue, AssignDoesntChangeQuotes)
{
    JsonValue jsonValue;
    jsonValue = kText;
    EXPECT_THAT(jsonValue.Value(), Eq(kText));
    jsonValue = kTextQuoted;
    EXPECT_THAT(jsonValue.Value(), Eq(kTextQuoted));
    jsonValue = kTextQuotedTwice;
    EXPECT_THAT(jsonValue.Value(), Eq(kTextQuotedTwice));
}

TEST(JsonString, AssignDoesntChangeQuotes)
{
    Core::JSON::String jsonString;
    jsonString = kText;
    EXPECT_THAT(jsonString.Value(), Eq(kText));
    jsonString = kTextQuoted;
    EXPECT_THAT(jsonString.Value(), Eq(kTextQuoted));
    jsonString = kTextQuotedTwice;
    EXPECT_THAT(jsonString.Value(), Eq(kTextQuotedTwice));
}

TEST(JsonValue, FromStringDoesntChangeQuotes)
{
    JsonValue jsonValue;
    jsonValue.FromString(kText);
    EXPECT_THAT(jsonValue.Value(), Eq(kText));
    jsonValue.FromString(kTextQuoted);
    EXPECT_THAT(jsonValue.Value(), Eq(kTextQuoted));
    jsonValue.FromString(kTextQuotedTwice);
    EXPECT_THAT(jsonValue.Value(), Eq(kTextQuotedTwice));
}

TEST(JsonString, FromStringUnquotes)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kText); // not quoted - unquote not needed
    EXPECT_THAT(jsonString.Value(), Eq(kText));
    jsonString.FromString(kTextQuoted);
    EXPECT_THAT(jsonString.Value(), Eq(kText));
    jsonString.FromString(kTextQuotedTwice);
    EXPECT_THAT(jsonString.Value(), Eq(kTextQuoted));
}

TEST(JsonValue, ToStringQuotesUnlessFromStringQuoted)
{
    string str;
    JsonValue(kText).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    JsonValue(kTextQuoted).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuotedTwice));
    // not checking for kTextQuotedTwice - would be triple quoted
    JsonValue jsonValue;
    jsonValue = kText;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    jsonValue = kTextQuoted;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuotedTwice));
    // not checking for kTextQuotedTwice - would be triple quoted
    jsonValue.FromString(kText);
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    jsonValue.FromString(kTextQuoted); // FromStringQuoted
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    jsonValue.FromString(kTextQuotedTwice); // FromStringQuoted
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kTextQuotedTwice));
}

TEST(JsonString, InitedWithConstructorToStringIsEmpty)
{
    string str;
    Core::JSON::String(kText).ToString(str);
    EXPECT_THAT(str, Eq(kEmptyQuoted));
    Core::JSON::String(kTextQuoted).ToString(str);
    EXPECT_THAT(str, Eq(kEmptyQuoted));
    Core::JSON::String(kTextQuotedTwice).ToString(str);
    EXPECT_THAT(str, Eq(kEmptyQuoted));
}

TEST(JsonString, ToStringQuotesUnlessFromStringQuoted)
{
    string str;
    Core::JSON::String jsonString;
    jsonString = kText;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    jsonString = kTextQuoted;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kTextQuotedTwice));
    // not checking for kTextQuotedTwice - would be triple quoted
    jsonString.FromString(kText);
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    jsonString.FromString(kTextQuoted); // FromStringQuoted
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kTextQuoted));
    jsonString.FromString(kTextQuotedTwice); // FromStringQuoted
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kTextQuotedTwice));
}
