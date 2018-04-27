FRK2D 
==============
Another 2D framework.
Uses SFML 2.3, Box2D 2.3, TGUI 0.8.

Install (Ubuntu 16.04)
-------------------------
Install the required libs
* SFML
```
sudo apt-get install libsfml-dev libsfml-graphics2.3v5 libsfml-system2.3v5 libsfml-audio2.3v5  libsfml-network2.3v5 libsfml-window2.3v5
```
  
   
* Box2D
```
sudo apt-get install libbox2d2.3.0 libbox2d-dev
```
* TGUI 
```
sudo add-apt-repository ppa:texus/tgui-0.8
sudo apt-get update
sudo apt-get install libtgui-dev
```
* sfml-tmxloader
```
git clone https://github.com/fallahn/sfml-tmxloader.git
cd build
rm -rf *
cmake ..
sudo make install
```

Build FRK2D and the demo project
```
git clone https://github.com/tristankpka/2D-Framework.git
cd 2D-Framework
mkdir build
cd build
cmake ..
make
```
Run
-----
To run the test project :
```
cd build
./framework
```

