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

TEST(TestGildedRoseGroup, TestAgedBrieItem_QualityIsNeverMoreThan50)
{
    Item items[1];
    init_item(items, "Aged Brie", 20, 50);
    
    update_quality(items, 1);

    CHECK_EQUAL(19, items[0].sellIn);
    CHECK_EQUAL(50, items[0].quality);
    STRCMP_EQUAL("Aged Brie", items[0].name);
}

TEST(TestGildedRoseGroup, TestAgedBrieItem_IncreaseQuality)
{
    Item items[1];
    init_item(items, "Aged Brie", 20, 30);
    
    update_quality(items, 1);

    CHECK_EQUAL(19, items[0].sellIn);
    CHECK_EQUAL(31, items[0].quality);
    STRCMP_EQUAL("Aged Brie", items[0].name);
}

TEST(TestGildedRoseGroup, TestSulfuras_NeverChanges)
{
    Item items[1];
    init_item(items, "Sulfuras, Hand of Ragnaros", 20, 30);
    
    update_quality(items, 1);

    CHECK_EQUAL(20, items[0].sellIn);
    CHECK_EQUAL(30, items[0].quality);
    STRCMP_EQUAL("Sulfuras, Hand of Ragnaros", items[0].name);
}

TEST(TestGildedRoseGroup, TestBackstage_ncreasesQualityBy2_When10DaysOrLess)
{
    Item items[1];
    init_item(items, "Backstage passes to a TAFKAL80ETC concert", 10, 20);
    
    update_quality(items, 1);

    CHECK_EQUAL(9, items[0].sellIn);
    CHECK_EQUAL(22, items[0].quality);
    STRCMP_EQUAL("Backstage passes to a TAFKAL80ETC concert", items[0].name);
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
