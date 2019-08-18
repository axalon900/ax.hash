//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#include <ax/hash.hpp>

#include <catch2/catch.hpp>

namespace {

struct aggregate
{
    int id;
    std::string name;
    std::vector<std::string> tokens;

    constexpr size_t hash() const { return ax::hash_t{id} << name << tokens; }
};

}

namespace std {
template <> struct hash<aggregate>
{
    using argument_type = aggregate;
    using result_type = std::size_t;
    constexpr result_type operator()(argument_type const &s) const noexcept { return s.hash(); }
};
}

TEST_CASE("hash_t is correctly initialized", "[hash_t]")
{
    SECTION("int")
    {
        const auto intHash = std::hash<int>{}(42);
        ax::hash_t hash{intHash};
        REQUIRE(hash == intHash);
    }

    SECTION("double")
    {
        const auto doubleHash = std::hash<double>{}(3.1415926);
        ax::hash_t hash{doubleHash};
        REQUIRE(hash == doubleHash);
    }

    SECTION("std::string")
    {
        const auto stringHash = std::hash<std::string>{}("Hello world");
        ax::hash_t hash{stringHash};
        REQUIRE(hash == stringHash);
    }
}

TEST_CASE("Combining hashes", "[hash_functions]")
{
    const auto intHash = std::hash<int>{}(42);
    const auto doubleHash = std::hash<double>{}(3.1415926);
    const auto stringHash = std::hash<std::string>{}("Hello world");
    const auto int_doubleHash = intHash ^ (doubleHash + 0x9e3779b9 + (intHash<<6u) + (intHash >> 2u));
    REQUIRE(ax::combine_hashes(intHash, doubleHash) == int_doubleHash);
    const auto double_stringHash = doubleHash ^ (stringHash + 0x9e3779b9 + (doubleHash<<6u) + (doubleHash >> 2u));
    REQUIRE(ax::combine_hashes(doubleHash, stringHash) == double_stringHash);
    const auto int_double_stringHash = int_doubleHash ^ (stringHash + 0x9e3779b9 + (int_doubleHash<<6u) + (int_doubleHash >> 2u));
    const auto int_doubleStringHash = intHash ^ (double_stringHash + 0x9e3779b9 + (intHash<<6u) + (intHash >> 2u));
    REQUIRE(ax::combine_hashes(intHash, doubleHash, stringHash) == int_double_stringHash);
    REQUIRE_FALSE(ax::combine_hashes(intHash, doubleHash, stringHash) == int_doubleStringHash);
    REQUIRE(ax::combine_hashes(intHash, ax::combine_hashes(doubleHash, stringHash)) == int_doubleStringHash);
    REQUIRE_FALSE(ax::combine_hashes(intHash, ax::combine_hashes(doubleHash, stringHash)) == int_double_stringHash);
}

TEST_CASE("Can accumulate hashes", "[hash_t]")
{
    const auto intHash = std::hash<int>{}(42);
    ax::hash_t hash{intHash};
    REQUIRE(hash == intHash);

    const auto doubleHash = std::hash<double>{}(3.1415926);
    hash << ax::hash_t{doubleHash};
    REQUIRE(hash == ax::combine_hashes(intHash, doubleHash));

    const auto stringHash = std::hash<std::string>{}("Hello world");
    hash << stringHash;
    REQUIRE(hash == ax::combine_hashes(intHash, doubleHash, stringHash));
}

TEST_CASE("Recognizes custom types", "[hash_t]")
{
    using namespace std::literals;
    const auto value = aggregate{0, "foo"s, {"this"s, "is"s, "a"s, "test"s}};
    ax::hash_t hash{value};
    REQUIRE(hash == value.hash());
}
