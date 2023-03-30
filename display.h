#ifndef DISPLAY_H
#define DISPLAY_H

class Display
{

public:
  Display();
  ~Display();
  int getWidth(){return width;}
  int getHeight(){return height;}

private:
  int width;
  int height;
};
#endif // DISPLAY_H
