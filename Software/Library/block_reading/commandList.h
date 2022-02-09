enum deviceName {
    D_LED,
    D_SERVO
};

typedef struct
{
  float startTime;
  deviceName itemName;
  int indexNum;
  int mode;
  float value;
} InputCommand;


InputCommand inputCommandList[] = {
  {5, D_LED, 1, 1, 255},
  {7, D_LED, 1, 1, 0},
  {9, D_LED, 1, 1, 255},
  {11, D_LED, 1, 1, 0}
};
