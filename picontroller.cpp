#include "picontroller.h"
#include <iostream>
#include <string>
#include <string_view>

PIController::PIController()
{

}

int PIController::on(int GPIO_PIN){
    int fd = open("/sys/class/gpio/gpio37/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio37/value");
        exit(1);
    }

    // Toggle LED 50 ms on, 50ms off, 100 times (10 seconds)

    for (int i = 0; i < 100; i++) {
        if (write(fd, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio37/value");
            exit(1);
        }
        usleep(50000);

        if (write(fd, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio37/value");
            exit(1);
        }
        usleep(50000);
    }

    close(fd);

    return 1;
}
