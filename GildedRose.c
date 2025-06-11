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

        if(item->sellIn < 10 && item->quality < 50)
        {
            item->quality += 1;
        }

        if(item->sellIn < 5 && item->quality < 50)
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
    for(int index = 0; index < size; index++)
    {
        Item* current_item = &items[index];
        ItemType type = get_item_type(current_item->name);

        if(type != SULFURAS)
        {
            current_item->sellIn -= 1;
        }

        switch(type)
        {
            case NORMAL_ITEM:
                update_normal_item(current_item);
                break;
            case AGED_BRIE:
                update_aged_brie(current_item);
                break;
            case SULFURAS:
                update_sulfuras(current_item);
                break;
            case BACKSTAGE_PASS:
                update_backstage_pass(current_item);
                break;
            case CONJURED_ITEM:
                update_conjured_item(current_item);
                break;
        }
    }
}
