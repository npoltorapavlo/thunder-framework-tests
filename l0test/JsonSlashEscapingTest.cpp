#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;

namespace {
const auto kSlash = "/";
const auto kSlashEscaped = "\\/";
const auto kSlashEscapedTwice = "\\\\\\/";
const auto kSlashQuoted = "\"" + string(kSlash) + "\"";
const auto kSlashEscapedQuoted = "\"" + string(kSlashEscaped) + "\"";
const auto kSlashEscapedTwiceQuoted = "\"" + string(kSlashEscapedTwice) + "\"";
const auto kEmptyQuoted = "\"\"";
}

TEST(ToQuotedString, DoesntChangeSlash)
{
    EXPECT_THAT(Core::ToQuotedString('\"', kSlash), Eq(kSlashQuoted));
    EXPECT_THAT(Core::ToQuotedString('\"', kSlashEscaped),
        Eq(kSlashEscapedQuoted));
    EXPECT_THAT(Core::ToQuotedString('\"', kSlashEscapedTwice),
        Eq(kSlashEscapedTwiceQuoted));
    // not checking for quoted - would be double-quoted
}

TEST(JsonValue, ConstructorDoesntChangeSlash)
{
    EXPECT_THAT(JsonValue(kSlash).Value(), Eq(kSlash));
    EXPECT_THAT(JsonValue(kSlashEscaped).Value(), Eq(kSlashEscaped));
    EXPECT_THAT(JsonValue(kSlashEscapedTwice).Value(),
        Eq(kSlashEscapedTwice));
    EXPECT_THAT(JsonValue(kSlashQuoted).Value(), Eq(kSlashQuoted));
    EXPECT_THAT(JsonValue(kSlashEscapedQuoted).Value(),
        Eq(kSlashEscapedQuoted));
    EXPECT_THAT(JsonValue(kSlashEscapedTwiceQuoted).Value(),
        Eq(kSlashEscapedTwiceQuoted));
}

TEST(JsonString, ConstructorDoesntChangeSlash)
{
    EXPECT_THAT(Core::JSON::String(kSlash).Value(), Eq(kSlash));
    EXPECT_THAT(Core::JSON::String(kSlashEscaped).Value(), Eq(kSlashEscaped));
    EXPECT_THAT(Core::JSON::String(kSlashEscapedTwice).Value(),
        Eq(kSlashEscapedTwice));
    EXPECT_THAT(Core::JSON::String(kSlashQuoted).Value(), Eq(kSlashQuoted));
    EXPECT_THAT(Core::JSON::String(kSlashEscapedQuoted).Value(),
        Eq(kSlashEscapedQuoted));
    EXPECT_THAT(Core::JSON::String(kSlashEscapedTwiceQuoted).Value(),
        Eq(kSlashEscapedTwiceQuoted));
}

TEST(JsonValue, AssignDoesntChangeSlash)
{
    JsonValue jsonValue;
    jsonValue = kSlash;
    EXPECT_THAT(jsonValue.Value(), Eq(kSlash));
    jsonValue = kSlashEscaped;
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscaped));
    jsonValue = kSlashEscapedTwice;
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscapedTwice));
    jsonValue = kSlashQuoted;
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashQuoted));
    jsonValue = kSlashEscapedQuoted;
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscapedQuoted));
    jsonValue = kSlashEscapedTwiceQuoted;
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscapedTwiceQuoted));
}

TEST(JsonString, AssignDoesntChangeSlash)
{
    Core::JSON::String jsonString;
    jsonString = kSlash;
    EXPECT_THAT(jsonString.Value(), Eq(kSlash));
    jsonString = kSlashEscaped;
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscaped));
    jsonString = kSlashEscapedTwice;
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscapedTwice));
    jsonString = kSlashQuoted;
    EXPECT_THAT(jsonString.Value(), Eq(kSlashQuoted));
    jsonString = kSlashEscapedQuoted;
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscapedQuoted));
    jsonString = kSlashEscapedTwiceQuoted;
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscapedTwiceQuoted));
}

TEST(JsonValue, FromStringUnescapesSlashIfQuoted)
{
    JsonValue jsonValue;
    jsonValue.FromString(kSlash); // not escaped - unescape not needed
    EXPECT_THAT(jsonValue.Value(), Eq(kSlash));
    jsonValue.FromString(kSlashEscaped); // not Quoted
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscaped));
    jsonValue.FromString(kSlashEscapedTwice); // not Quoted
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscapedTwice));
    jsonValue.FromString(kSlashQuoted); // not escaped - unescape not needed
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashQuoted));
    jsonValue.FromString(kSlashEscapedQuoted);
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashQuoted));
    jsonValue.FromString(kSlashEscapedTwiceQuoted);
    EXPECT_THAT(jsonValue.Value(), Eq(kSlashEscapedQuoted));
}

TEST(JsonString, FromStringUnescapesSlashIfQuoted)
{
    Core::JSON::String jsonString;
    jsonString.FromString(kSlash); // not escaped - unescape not needed
    EXPECT_THAT(jsonString.Value(), Eq(kSlash));
    jsonString.FromString(kSlashEscaped); // not Quoted
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscaped));
    jsonString.FromString(kSlashEscapedTwice); // not Quoted
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscapedTwice));
    jsonString.FromString(kSlashQuoted); // not escaped - unescape not needed
    EXPECT_THAT(jsonString.Value(), Eq(kSlash));
    jsonString.FromString(kSlashEscapedQuoted);
    EXPECT_THAT(jsonString.Value(), Eq(kSlash));
    jsonString.FromString(kSlashEscapedTwiceQuoted);
    EXPECT_THAT(jsonString.Value(), Eq(kSlashEscaped));
}

TEST(JsonValue, ToStringEscapesSlashUnlessFromStringEscapedQuoted)
{
    string str;
    JsonValue(kSlash).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    JsonValue(kSlashEscaped).IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
    // not checking for kSlashEscapedTwice - would be triple escaped
    // not checking for quoted - would be double-quoted
    JsonValue jsonValue;
    jsonValue = kSlash;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonValue = kSlashEscaped;
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
    // not checking for kSlashEscapedTwice - would be triple escaped
    // not checking for quoted - would be double-quoted
    jsonValue.FromString(kSlash);
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonValue.FromString(kSlashEscaped);
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
    // not checking for kSlashEscapedTwice - would be triple escaped
    jsonValue.FromString(kSlashQuoted);
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonValue.FromString(kSlashEscapedQuoted); // FromStringEscapedQuoted
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonValue.FromString(kSlashEscapedTwiceQuoted); // FromStringEscapedQuoted
    jsonValue.IElement::ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
}

TEST(JsonString, ToStringEscapesSlashUnlessFromStringEscapedQuoted)
{
    // not checking for constructor - see InitedWithConstructorToStringIsEmpty
    string str;
    Core::JSON::String jsonString;
    jsonString = kSlash;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonString = kSlashEscaped;
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
    // not checking for kSlashEscapedTwice - would be triple escaped
    // not checking for quoted - would be double-quoted
    jsonString.FromString(kSlash);
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonString.FromString(kSlashEscaped);
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
    // not checking for kSlashEscapedTwice - would be triple escaped
    jsonString.FromString(kSlashQuoted);
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonString.FromString(kSlashEscapedQuoted); // FromStringEscapedQuoted
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedQuoted));
    jsonString.FromString(kSlashEscapedTwiceQuoted); // FromStringEscapedQuoted
    jsonString.ToString(str);
    EXPECT_THAT(str, Eq(kSlashEscapedTwiceQuoted));
}
