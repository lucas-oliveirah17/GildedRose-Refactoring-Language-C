#include <string.h>
#include "GildedRose.h"
#include <stdio.h>

Item*
init_item(Item* item, const char *name, int sellIn, int quality)
{
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);
    
    return item;
}

typedef enum
{
    NORMAL_ITEM,
    AGED_BRIE,
    SULFURAS,
    BACKSTAGE_PASS,
    CONJURED_ITEM
} ItemType;

ItemType get_item_type(const char* name)
{
    if (strcmp(name, "Aged Brie") == 0)
        return AGED_BRIE;

    else if (strcmp(name, "Sulfuras, Hand of Ragnaros") == 0)
        return SULFURAS;

    else if (strcmp(name, "Backstage passes to a TAFKAL80ETC concert") == 0)
        return BACKSTAGE_PASS;

    else if (strcmp(name, "Conjured Mana Cake") == 0)
        return CONJURED_ITEM;

    else
        return NORMAL_ITEM;
}

extern char* 
print_item(char* buffer, Item* item) 
{
    sprintf(buffer, "%s, %d, %d", item->name, item->sellIn, item->quality);
    return buffer;
}

void update_normal_item(Item* item)
{
    if(item->quality > 0)
    {
        item->quality -= 1;
    }

    if(item->sellIn < 0 && item->quality > 0)
    {
        item->quality -= 1;
    }
}

void update_aged_brie(Item* item)
{
    if(item->quality < 50)
    {
        item->quality += 1;
    }

    if(item->sellIn < 0 && item->quality < 50)
    {
        item->quality += 1;
    }
}

void update_sulfuras(Item* item)
{
    (void)item;
}

void update_backstage_pass(Item* item)
{
    if(item->quality < 50)
    {
        item->quality += 1;

        if(item->sellIn <= 10 && item->quality < 50)
        {
            item->quality += 1;
        }

        if(item->sellIn <= 5 && item->quality < 50)
        {
            item->quality += 1;
        }
    }

    if(item->sellIn < 0)
    {
        item->quality = 0;
    }
}

void update_conjured_item(Item* item)
{
    if(item->quality > 0)
    {
        item->quality -= 2;
    }

    if(item->sellIn < 0 && item->quality > 0)
    {
        item->quality -= 2;
    }
}

void 
update_quality(Item items[], int size) 
{
    int i;
    
    for (i = 0; i < size; i++)
    {
        if (strcmp(items[i].name, "Aged Brie") && strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert"))
        {
            if (items[i].quality > 0)
            {
                if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros"))
                {
                    items[i].quality = items[i].quality - 1;
                }
            }
        }
        else
        {
            if (items[i].quality < 50)
            {
                items[i].quality = items[i].quality + 1;

                if (!strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert"))
                {
                    if (items[i].sellIn < 11)
                    {
                        if (items[i].quality < 50)
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }

                    if (items[i].sellIn < 6)
                    {
                        if (items[i].quality < 50)
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }
                }
            }
        }

        if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros"))
        {
            items[i].sellIn = items[i].sellIn - 1;
        }

        if (items[i].sellIn < 0)
        {
            if (strcmp(items[i].name, "Aged Brie"))
            {
                if (strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert"))
                {
                    if (items[i].quality > 0)
                    {
                        if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros"))
                        {
                            items[i].quality = items[i].quality - 1;
                        }
                    }
                }
                else
                {
                    items[i].quality = items[i].quality - items[i].quality;
                }
            }
            else
            {
                if (items[i].quality < 50)
                {
                    items[i].quality = items[i].quality + 1;
                }
            }
        }
    }
}
