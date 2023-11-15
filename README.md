# LED_TEST_FW
This is simple test fw to controll an test LED via i2c controller <br>
<br>
To build, clone the repository, open project with STM32Cube IDE. <br>
<br>
Project has been prepared with IDE version 1.10.1, so it wasn't the latest. It's due to fact that I need to maintain some other projects.

![image](https://github.com/arkadiuszgibes/LED_TEST_FW/assets/150804991/3fdc9968-a4d5-4d30-8512-fddc17e9a47c)


<br>

Project wasn't tested in real enviroment so it may not work properly. I don't have access to PCA9633 dev board, so it's a first shot in solving this problem, based on information collected in datasheet.
<br>
<br>
camelCase notation used by ST wasn't followed for a reason, it's easier to track app code. It makes clear what does not comes from ST.
