#ifndef CANVAS_H
#define CANVAS_H

class Credit {
public:
    Credit(char* filename);
    ~Credit();

    int* getData();
    int getWidth();
    int getHeight();

private:
    int* data;
    int width;
    int height;
};

#endif