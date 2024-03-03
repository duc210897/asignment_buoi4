#include "stdio.h"
#include "conio.h"

/* T.B.D: There are some warning, will be improve later */

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

product_information_t g_product_available[100] =  // limit 100 product
{
   // example:
   // [0] = {.name = "T-shirt", .price = 15.99, .type = TYPE_PRODUCT_CLOTHING, .weight_or_size.size = 2}, 
   // [1] = {.name = "Smartphone", .price = 499.99, .type = TYPE_PRODUCT_ELECTRONIC, .weight_or_size.weight = 0.12}
};

char *gp_product_array_display[] = 
{
    "Enter the number of products: ",
    "\nEnter information for product",
    "\nName:",
    "Price:",
    "Type:",
    "Size:",
    "Weight:",
    "\nEnter the name of the product to retrieve information",
};

char *type_of_input[] = {"%s", "%f", "%d", "%d", "%f"};

char size_or_weight_of_input_lut[] = 
{
    [TYPE_PRODUCT_CLOTHING] = 0,
    [TYPE_PRODUCT_FOOTWEAR] = 0,
    [TYPE_PRODUCT_ELECTRONIC] = 1,
};
int main(int argc, char *argv[])
{

  printf("%s", gp_product_array_display[0]);
  int count;
  scanf("%d", &count);
  for (int input_infor_count = 1; input_infor_count < count + 1; input_infor_count++)
  {
    printf("%s ", gp_product_array_display[input_infor_count]);
    printf("%d:", input_infor_count);

    /* T.B.D: There is many warning right here but improve later */
    int product_count = input_infor_count - 1;
    int *p_product_item_adress[] = {
        [0] = &g_product_available[product_count].name, 
        [1] = &g_product_available[product_count].price, 
        [2] = &g_product_available[product_count].type,
        [3] = &g_product_available[product_count].weight_or_size.size,
        [4] = &g_product_available[product_count].weight_or_size.weight,
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

  /* show value*/
//   for (int input_infor_count = 1; input_infor_count < count + 1; input_infor_count++)
//   {
//      printf("%s\n", g_product_available[input_infor_count].name);
//      printf("%f\n", g_product_available[input_infor_count].price);
//      printf("%d\n", g_product_available[input_infor_count].type);
//      printf("%d\n", g_product_available[input_infor_count].weight_or_size.size);
//   }


  return 0;

}