# wxCalc

This is my project for OOP class, from Transilvania University Brasov. It is a simple cross-platform calculator application, made with wxWidgets.

## Demo for Windows

Install Visual Studio 2019 and run wxCalc.exe

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* Windows

... Visual Studio Code 2019
... wxWidgets

[Follow the link for configure VS with wxWidgets](https://www.youtube.com/watch?v=sRhoZcNpMb4)

* Ubuntu

```
sudo apt update
sudo apt install build-essential
sudo apt-get install libgtk-3-dev
sudo apt install libwxgtk3.0-gtk3-dev
sudo apt install cmake
```

### Compiling

* Windows

Open wxCalc.sln and build

* Ubuntu

```
mkdir build
cd build
cmake ../
make
./wxCalc
```

## Features

+ working with decimal system
+ four operation implemented, add, difference, product and divide
+ check if the input have a correct parentheses
+ check if the input have letters and the accepted operators
+ have a history of your calculus, and if click one that will come in your input

## Built With

* [wxWidgets](https://www.wxwidgets.org/)

## Authors

* **Puscasu Alexandru** - *4LF792* - [alex2kameboss](https://github.com/alex2kameboss)

## License

This project is licensed under the MIT License.
