#ifndef PICONTROLLER_H
#define PICONTROLLER_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


class PIController
{
public:
    PIController();
    static int on(int GPIO_PIN = 0);
private:

};

#endif // PICONTROLLER_H
