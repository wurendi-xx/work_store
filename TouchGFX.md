## TouchGFX的实现
硬件：

+ 图片缓存使用FMC->SDRAM来扩展RAM内存（现有的不知道可以不可以扩展）
+ 图片加载使用QSPI加载W25Q（因为TouchGFX需要使用memory-mapped mode，现有的应该不行）
+ 图片显示使用FSMC->LTDC（现在已经有了）
+ 触摸别人用的是ST的驱动（我们自己的我还没了解）

软件：

+ cubeMX添加touchGFX作为独立第三方库（会设置图片的缓存区起始地址，即RAM中的地址）

+ 然后再src中会产生part后缀的文件，可以使用TouchGFX Designer打开编辑

+ TouchGFX Designer中可以设计UI界面，会生产sln工程文件，即Visual Studio的工程，需要使用C++编写UI的交互逻辑

+ 设计好sln工程文件之后，会产生与文件和字库相关的数据，需要设置一些参数之后，让烧程序时自动烧到W25Q128中（这个不懂）

  