#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "GildedRose.h"
}

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
  }
  void teardown() {
  }
};

TEST(TestGildedRoseGroup, TestNormalItem_DecreaseQualityAndSellIn)
{
    Item items[1];
    init_item(items, "Normal Item", 10, 20);
    
    update_quality(items, 1);

    CHECK_EQUAL(9, items[0].sellIn);
    CHECK_EQUAL(19, items[0].quality);
    STRCMP_EQUAL("Normal Item", items[0].name);
}

TEST(TestGildedRoseGroup, TestNormalItem_OnceSellInHasPassed_QualityDecreaseByTwo)
{
    Item items[1];
    init_item(items, "Normal Item", 0, 20);
    
    update_quality(items, 1);

    CHECK_EQUAL(-1, items[0].sellIn);
    CHECK_EQUAL(18, items[0].quality);
    STRCMP_EQUAL("Normal Item", items[0].name);
}

TEST(TestGildedRoseGroup, TestNormalItem_QualityIsNeverNegative)
{
    Item items[1];
    init_item(items, "Normal Item", 10, 0);
    
    update_quality(items, 1);

    CHECK_EQUAL(9, items[0].sellIn);
    CHECK_EQUAL(0, items[0].quality);
    STRCMP_EQUAL("Normal Item", items[0].name);
}

void example()
{
    Item items[6];
    int last = 0;
    
    init_item(items + last++, "+5 Dexterity Vest", 10, 20);
    init_item(items + last++, "Aged Brie", 2, 0);
    init_item(items + last++, "Elixir of the Mongoose", 5, 7);
    init_item(items + last++, "Sulfuras, Hand of Ragnaros", 0, 80);
    init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 15, 20);
    init_item(items + last++, "Conjured Mana Cake", 3, 6);
    update_quality(items, last);
}

int
main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
