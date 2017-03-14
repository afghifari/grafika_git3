#ifndef CREDIT_H
#define CREDIT_H

class Credit {
public:
    Credit(char* filename);
    ~Credit();

    unsigned char* getData();
    int getWidth();
    int getHeight();

private:
    unsigned char* data;
    int width;
    int height;
};

#endif