#include "stdio.h"
#include "conio.h"

enum e_type // prefix e_ <= enum
{
    TYPE_PRODUCT_CLOTHING,
    TYPE_PRODUCT_FOOTWEAR,
    TYPE_PRODUCT_ELECTRONIC,
} typedef type_t;

union union_weight_or_size
{
    int  size;
    float weight;
} typedef weight_or_size_t;

struct st_product_information // prefix st_ <= struct
{
    /* please make sure size of this type is lowest */
    weight_or_size_t weight_or_size;
    float price;
    type_t type;
    char name[10];
} typedef product_information_t;

product_information_t g_product_available[100] =  // limit 100 product, improve for using the heap íntead
{
   // example:
   // [0] = {.name = "T-shirt", .price = 15.99, .type = TYPE_PRODUCT_CLOTHING, .weight_or_size.size = 2}, 
   // [1] = {.name = "Smartphone", .price = 499.99, .type = TYPE_PRODUCT_ELECTRONIC, .weight_or_size.weight = 0.12}
};

char *gp_product_array_display[] = 
{
    "Enter the number of products: ",
    "\nEnter information for product ",
    "\nName: ",
    "Price: ",
    "Type (0: Clothing, 1: Footwear, 2: Electronics): ",
    "Size: ",
    "Weight: ",
    "\nEnter the name of the product to retrieve information: ",
    "Product Information:\n",
    "\nType: "
};

char *type_of_input[] = {"%s", "%f", "%d", "%d", "%f"};
char *type_of_output[] = {"%s", "%2f", "%d", "%d", "%2f"};

char size_or_weight_of_input_lut[] = 
{
    [TYPE_PRODUCT_CLOTHING] = 0,
    [TYPE_PRODUCT_FOOTWEAR] = 0,
    [TYPE_PRODUCT_ELECTRONIC] = 1,
};
char *size_or_weight_of_output_lut[] = 
{
    [TYPE_PRODUCT_CLOTHING] = "Clothing",
    [TYPE_PRODUCT_FOOTWEAR] = "Footwear",
    [TYPE_PRODUCT_ELECTRONIC] = "Electronics",
};

void user_input_product_data()
{
  printf("%s", gp_product_array_display[0]);
  int count;
  scanf("%d", &count);
  for (int input_infor_count = 1; input_infor_count < count + 1; input_infor_count++)
  {
    printf("%s ", gp_product_array_display[1]);
    printf("%d:", input_infor_count);

    int product_count = input_infor_count - 1;
    int *p_product_item_adress[] = {
        [0] = (int *) &g_product_available[product_count].name, 
        [1] = (int *) &g_product_available[product_count].price, 
        [2] = (int *) &g_product_available[product_count].type,
        [3] = (int *) &g_product_available[product_count].weight_or_size.size,
        [4] = (int *) &g_product_available[product_count].weight_or_size.weight,
    };

    for(int input_product_item_count = 2;  input_product_item_count < 5; input_product_item_count++)
    {
        printf("%s", gp_product_array_display[input_product_item_count]);
        scanf(type_of_input[input_product_item_count - 2], p_product_item_adress[input_product_item_count - 2]);
    }

    int offset = size_or_weight_of_input_lut[g_product_available[product_count].type];
    printf("%s", gp_product_array_display[5 + offset]);
    scanf(type_of_input[3 + offset], p_product_item_adress[3 + offset]);
  }
}

int compare_product_data(char str[])
{
    for(int i = 0; i < 100; i++) // count the product available, return the index
    {
        for(char namecount = 0; namecount < 10; namecount++)
        {
            if(g_product_available[i].name[namecount] != str[namecount])
            {
                break;
            }
            if(namecount == 9)
            {
                return i;
            }
        }
    }

    return -1;
}

void user_search_product_data()
{
    printf("%s", gp_product_array_display[7]);
    char search_product[100] = {0};
    scanf("%s", search_product);

    int product_count = compare_product_data(search_product);
    
    if (product_count == -1) return;

    printf("%s", gp_product_array_display[8]);
    printf("%s", gp_product_array_display[2]);
    printf(type_of_output[0], g_product_available[product_count].name);
    printf("\n");

    printf("%s", gp_product_array_display[3]);
    printf(type_of_output[1], g_product_available[product_count].price);

    printf("%s", gp_product_array_display[9]);
    printf("%s", size_or_weight_of_output_lut[g_product_available[product_count].type]);
    printf("\n");

    int offset = size_or_weight_of_input_lut[g_product_available[product_count].type];
    printf("%s", gp_product_array_display[5 + offset]);
    if(offset == 1)
    {
      printf(type_of_output[3 + offset], g_product_available[product_count].weight_or_size.weight);
    }
    else
    {
      printf(type_of_output[3 + offset], g_product_available[product_count].weight_or_size.size);
    }
}
int main(int argc, char *argv[])
{

  user_input_product_data();
  user_search_product_data();
  return 0;

}