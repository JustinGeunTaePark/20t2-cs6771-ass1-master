//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//-------------------------------------------------------------------------------------
// Written by Justin Geuntae Park (z5060336)
// Please note that this is the actual file for test cases
// The following file contains test cases designed to test the word ladder implementation
// found in word_ladder.cpp. The general approach to writing test is to start off easy then progress
// into more difficult edge cases. This way when the program fails it will be simpler to determine
// whether it is a problem with the algorthim or way the solution is complied. If the program can't
// even add words to a list or have multiple lists then it will fail sooner than later. Then only
// the way data structures are handled has to be checked. As the program progresses it will go into
// difficult cases such as word ladder cases with multiple branches and if it fails then the way the
// algorthim is handled has to be checked. Testing is also ordered in a manner where it doesn't
// introduce more than one new variable. This is why the first test, checks for if the program can
// locate solutions at different positions. As there is no point in checking increasing size if the
// program can't even find a solution.
#include "catch2/catch.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/word_ladder.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/is_sorted.hpp"
#include "range/v3/range/primitives.hpp"
#include <string>
#include <vector>

TEST_CASE("Testing for word ladder cases where words exist by looking at different positions") {
	auto const english_lexicon_test = word_ladder::read_lexicon("./english_test.txt");

	SECTION("Word ladder solution for where a word exists at the beginning") {
		auto const ladders = word_ladder::generate("cope", "hope", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"cope", "hope"})));
	}

	SECTION("Word ladder solution for where a word exists at a middle position") {
		auto const ladders = word_ladder::generate("cope", "cape", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"cope", "cape"})));
	}

	SECTION("Word ladder solution for where a word exists at a end position") {
		auto const ladders = word_ladder::generate("cope", "copd", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"cope", "copd"})));
	}
}

TEST_CASE("Testing for word ladder cases where there is no result") {
	auto const english_lexicon_test = word_ladder::read_lexicon("./english_test.txt");

	SECTION("Word ladder solution where there is no inbetween words") {
		auto const ladders = word_ladder::generate("phone", "cones", english_lexicon_test);
		CHECK(ranges::size(ladders) == 0);
		CHECK(ranges::is_sorted(ladders));
	}

	SECTION("Word ladder solution where there is some inbetween words but no solution") {
		auto const ladders = word_ladder::generate("south", "cattt", english_lexicon_test);
		CHECK(ranges::size(ladders) == 0);
		CHECK(ranges::is_sorted(ladders));
	}
}

TEST_CASE("Testing for word ladder cases with varying depths") {
	auto const english_lexicon_test = word_ladder::read_lexicon("./english_test.txt");
	SECTION("Word ladder solution with no inbetween words") {
		auto const ladders = word_ladder::generate("jim", "kim", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"jim", "kim"})));
	}

	SECTION("Word ladder solution with 1 inbetween words") {
		auto const ladders = word_ladder::generate("kaye", "jayl", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"kaye", "jaye", "jayl"})));
	}

	SECTION("Word ladder solution with 2 inbetween words") {
		auto const ladders = word_ladder::generate("jimmy", "kinny", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"jimmy", "kimmy", "kinmy", "kinny"})));
	}
}

TEST_CASE("Testing for word ladders with multiple solutions") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	SECTION("Word ladder solution with no solution") {
		auto const ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
		CHECK(ranges::is_sorted(ladders));
	}

	SECTION("Word ladder solution with one solution") {
		auto const ladders = word_ladder::generate("at", "it", english_lexicon);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"at", "it"})));
	}

	SECTION("Word ladder solution with two solutions") {
		auto const ladders = word_ladder::generate("awake", "sleep", english_lexicon);
		CHECK(ranges::size(ladders) == 2);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(
		   ladders,
		   testing::contain(
		      {"awake", "aware", "sware", "share", "sharn", "shawn", "shewn", "sheen", "sheep", "sleep"})));
		CHECK(ranges::any_of(
		   ladders,
		   testing::contain(
		      {"awake", "aware", "sware", "share", "shire", "shirr", "shier", "sheer", "sheep", "sleep"})));
	}

	SECTION("Word ladder solution with multiple solutions") {
		auto const ladders = word_ladder::generate("work", "play", english_lexicon);
		CHECK(ranges::size(ladders) == 12);
		CHECK(ranges::is_sorted(ladders));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "fork", "form", "foam", "flam", "flay", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "perk", "peak", "pean", "plan", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "perk", "peak", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "perk", "pert", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "porn", "pirn", "pian", "plan", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "pork", "port", "pert", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "word", "wood", "pood", "plod", "ploy", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "worm", "form", "foam", "flam", "flay", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "worn", "porn", "pirn", "pian", "plan", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "wort", "bort", "boat", "blat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "wort", "port", "pert", "peat", "plat", "play"})));
		CHECK(
		   ranges::any_of(ladders,
		                  testing::contain({"work", "wort", "wert", "pert", "peat", "plat", "play"})));
	}
}

TEST_CASE("Testing for word ladder cases where there exists mutliple branches") {
	auto const english_lexicon_test = word_ladder::read_lexicon("./english_test.txt");

	SECTION("Has four branches with the same length but only one answer") {
		auto const ladders = word_ladder::generate("aaaaa", "ccccc", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"aaaaa", "aaaac", "aaacc", "aaccc", "acccc", "ccccc"})));
	}

	SECTION("Has three branches where only two reach a solution") {
		auto const ladders = word_ladder::generate("ddd", "ggg", english_lexicon_test);
		CHECK(ranges::size(ladders) == 2);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"ddd", "ddg", "dgg", "ggg"})));
		CHECK(ranges::any_of(ladders, testing::contain({"ddd", "gdd", "ggd", "ggg"})));
	}
}

TEST_CASE("Testing for word ladder cases where different branches converge") {
	auto const english_lexicon_test = word_ladder::read_lexicon("./english_test.txt");

	SECTION("There exists two branches that coverge") {
		auto const ladders = word_ladder::generate("waiter", "pattel", english_lexicon_test);
		CHECK(ranges::size(ladders) == 2);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"waiter", "saiter", "satter", "patter", "pattel"})));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"waiter", "caiter", "catter", "patter", "pattel"})));
	}

	SECTION("There exists multiple branches that coverge into one solution but at different "
	        "points") {
		auto const ladders = word_ladder::generate("storm", "xpern", english_lexicon_test);
		CHECK(ranges::size(ladders) == 4);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"storm", "atorm", "aterm", "xterm", "xtern", "xpern"})));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"storm", "btorm", "bterm", "xterm", "xtern", "xpern"})));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"storm", "otorm", "otorn", "xtorn", "xtern", "xpern"})));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"storm", "ptorm", "ptorn", "xtorn", "xtern", "xpern"})));
	}
}

TEST_CASE("Testing for word ladder cases on different point of the same ladder") {
	auto const english_lexicon_test = word_ladder::read_lexicon("./english_test.txt");

	SECTION("Solution for one long ladder") {
		auto const ladders = word_ladder::generate("scrap", "tpala", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		                     testing::contain({"scrap", "sprap", "tprap", "tpaap", "tpaaa", "tpala"})));
	}

	SECTION("Sub ladder from the beginning to middle") {
		auto const ladders = word_ladder::generate("scrap", "tprap", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"scrap", "sprap", "tprap"})));
	}

	SECTION("Sub ladder that is in the middle of previous solution") {
		auto const ladders = word_ladder::generate("sprap", "tpaap", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"sprap", "tprap", "tpaap"})));
	}

	SECTION("Sub ladder from middle to end") {
		auto const ladders = word_ladder::generate("tpaap", "tpala", english_lexicon_test);
		CHECK(ranges::size(ladders) == 1);
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"tpaap", "tpaaa", "tpala"})));
	}
}
