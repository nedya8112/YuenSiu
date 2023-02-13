#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *typeOfFood[] = {"出前一丁",     "烏冬",         "米線",
                            "炒飯",         "炒麵",         "炒烏冬",
                            "蒜蓉辣醬炒飯", "蒜蓉辣醬炒麵", "蒜蓉辣醬炒烏冬"};
const char *typeOfStock[] = {"日本清湯", "番茄洋葱湯", "麻辣湯", "芝士撈"};
const char *typeOfSides[] = {
    "生炸雞翼", "生炸雞髀", "水魷",   "牛栢葉", "鴨胸",  "豬頸肉 ",
    "五花腩",   "多春魚",   "午餐肉", "廚師腸", "雞腎",  "豆卜",
    "冬菇",     "粟米",     "茄子",   "蘿蔔",   "時菜 ", "翠玉瓜",
    "煙肉金菇", "魚皮餃",   "墨魚丸", "牛丸",   "芝心丸"};

int searchNumber() {
  int number = 1;
  char buf[100] = {'\0'};
  FILE *f = fopen("output.txt", "r");
  fseek(f, -100, SEEK_END);
  fread(buf, 100, 1, f);
  char *last_newline = strrchr(buf, '\n');
  if (last_newline != NULL) {
    last_newline = last_newline + 1;
    number = atoi(last_newline) + 1;
  }
  fclose(f);
  return number;
}

int main(void) {
  int number = searchNumber();
  printf("嗨你係落單嘅第%d條友\n", number);
  char name[100];
  printf("名？^^\n");
  fgets(name, 100, stdin);
  name[strlen(name) - 1] = '\0';

  int foodType = 0, stockType = 0, sideType[6] = {0}, confirm = 0;
  char sides[100] = {'\0'}, remarks[100] = {'\0'}, input[100] = {'\0'};
mainDish:
  printf("\n想食啲咩？^^\n1.出前一丁 2.烏冬 3.米線 4.炒飯(+$8) "
         "5.炒麵(+$8) 6.炒烏冬(+$8) 7.蒜蓉辣醬炒飯(+$10) 8.蒜蓉辣醬炒麵(+$10) "
         "9.蒜蓉辣醬炒烏冬(+$10)\n");
  fgets(input, 10, stdin);
  foodType = atoi(input);
  while (foodType < 1 || foodType > 9) {
    printf("invalid input, type again.\n");
    fgets(input, 100, stdin);
    foodType = atoi(input);
  }

  if (foodType >= 1 && foodType <= 3) {
    printf(
        "\n咩湯底？^^\n1.日本清湯 2.番茄洋葱湯 3.麻辣湯(+$8) 4.芝士撈(+$8)\n");
    printf("你而家揀咗%s\n打\"99\"返轉頭再揀過主食\n",
           typeOfFood[foodType - 1]);
    fgets(input, 100, stdin);
    stockType = atoi(input);
    while ((stockType < 1 || stockType > 9) && stockType != 99) {
      printf("invalid input, type again.\n");
      fgets(input, 100, stdin);
      stockType = atoi(input);
    }
    if (stockType == 99) {
      stockType = 0;
      goto mainDish;
    }
  }

sideDish:
  printf("\n打低三個餸吧^^\nFYI: 1.生炸雞翼 2.生炸雞髀 3.水魷 "
         "4.牛栢葉 5.鴨胸 6.豬頸肉 "
         "7.五花腩 8.多春魚 9.午餐肉 10.廚師腸 11.雞腎 12.豆卜 13.冬菇 14.粟米 "
         "15.茄子 16.蘿蔔 17.時菜 "
         "18.翠玉瓜 19.煙肉金菇 20.魚皮餃 21.墨魚丸 22.牛丸 "
         "23.芝心丸\n每款限選一次（加餸每款+$8 "
         "加雞髀+$20）\n");
  if (foodType >= 1 && foodType <= 3)
    printf("你而家揀咗%s %s\n打\"99\"返轉頭再揀過主食\n",
           typeOfFood[foodType - 1], typeOfStock[stockType - 1]);
  else
    printf("你而家揀咗%s\n打\"99\"返轉頭再揀過主食\n",
           typeOfFood[foodType - 1]);
  fgets(input, 100, stdin);
  sscanf(input, "%d%d%d%d%d%d", &sideType[0], &sideType[1], &sideType[2],
         &sideType[3], &sideType[4], &sideType[5]);
  while ((sideType[0] < 1 || sideType[0] > 23 || sideType[1] < 1 ||
          sideType[1] > 23 || sideType[2] < 1 || sideType[2] > 23 ||
          sideType[3] < 0 || sideType[3] > 23 || sideType[4] > 23 ||
          sideType[4] < 0 || sideType[5] > 23 || sideType[5] < 0) &&
         sideType[0] != 99) {
    printf("invalid input, type again.\n");
    fgets(input, 100, stdin);
    sscanf(input, "%d%d%d%d%d%d", &sideType[0], &sideType[1], &sideType[2],
           &sideType[3], &sideType[4], &sideType[5]);
  }
  if (sideType[0] == 0) {
    memset(sideType, 0, sizeof(sideType));
    goto mainDish;
  }
  sprintf(sides, "%s %s %s", typeOfSides[sideType[0] - 1],
          typeOfSides[sideType[1] - 1], typeOfSides[sideType[2] - 1]);
  for (int i = 3; i < 6; i++)
    if (sideType[i] != 0) {
      strcat(sides, " ");
      strcat(sides, typeOfSides[sideType[i] - 1]);
    }

remark:
  printf("\n有冇咩特別要求？^^（加底, 多甜汁, 走青 etc.）冇就打\"0\"\n");
  if (foodType >= 1 && foodType <= 3)
    printf("你而家揀咗%s %s %s\n打\"69\"返轉頭再揀過餸 "
           "打\"99\"返轉頭再揀過主食\n",
           typeOfFood[foodType - 1], typeOfStock[stockType - 1], sides);
  else
    printf("你而家揀咗%s %s\n打\"69\"返轉頭再揀過餸 打\"99\"返轉頭再揀過主食\n",
           typeOfFood[foodType - 1], sides);
  fgets(remarks, 100, stdin);
  remarks[strlen(remarks) - 1] = '\0';
  if (strcmp(remarks, "0") == 0)
    sprintf(remarks, " ");
  if (strcmp(remarks, "69") == 0) {
    memset(sideType, 0, sizeof(sideType));
    goto sideDish;
  }
  if (strcmp(remarks, "99") == 0) {
    memset(sideType, 0, sizeof(sideType));
    goto mainDish;
  }

  if (foodType >= 1 && foodType <= 3)
    printf(
        "\n覆單：\n你而家揀咗%s %s %s %s\n打\"39\"返轉頭改特別要求 "
        "打\"69\"返轉頭再揀過餸 "
        "打\"99\"返轉頭再揀過主食\n如果冇落錯單打\"1\"確認，一旦確認不得悔單，"
        "走數正仆街^^\n",
        typeOfFood[foodType - 1], typeOfStock[stockType - 1], sides, remarks);
  else
    printf(
        "\n覆單：\n你而家揀咗%s %s %s\n打\"39\"返轉頭改特別要求 "
        "打\"69\"返轉頭再揀過餸 "
        "打\"99\"返轉頭再揀過主食\n如果冇落錯單打\"1\"確認，一旦確認不得悔單，"
        "走數正仆街^^\n",
        typeOfFood[foodType - 1], sides, remarks);
  fgets(input, 100, stdin);
  confirm = atoi(input);
  while (confirm != 1 && confirm != 39 && confirm != 69 && confirm != 99) {
    printf("invalid input, type again.\n");
    fgets(input, 100, stdin);
    confirm = atoi(input);
  }
  if (confirm == 39)
    goto remark;
  if (confirm == 69) {
    memset(sideType, 0, sizeof(sideType));
    goto sideDish;
  }
  if (confirm == 99) {
    memset(sideType, 0, sizeof(sideType));
    goto mainDish;
  }
  if (confirm == 1) {
    number = searchNumber();
    FILE *f = fopen("output.txt", "a");
    if (number == 1) {
      time_t timer;
      char buffer[26];
      struct tm *tm_info;
      timer = time(NULL);
      tm_info = gmtime(&timer);
      tm_info->tm_hour = tm_info->tm_hour + 8;
      strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
      fputs(buffer, f);
    }

    fprintf(f, "\n%d.%s %s ", number, name, typeOfFood[foodType - 1]);
    if (foodType >= 1 && foodType <= 3)
      fprintf(f, "%s ", typeOfStock[stockType - 1]);
    fprintf(f, "%s %s", sides, remarks);
    fclose(f);
    printf("\n落單完成，有嘢食會嗌你^^\n");
  }
  return 0;
}