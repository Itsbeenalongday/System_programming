# System_programming

## Contents
+ 실습
  - 라즈베리 파일 실습
+ 과제
  - SIC/XE Architecture Assembly language
  - make algorithm written by assembly
  
## Sictool manual
```shell
# install

# remove <= 1.8 java
$ sudo apt-get remove openjdk* oracle*

# install 1.8 <= version java
$ sudo apt-get update
$ sudo apt-get install openjdk-8-jdk
$ git clone  https://github.com/jurem/SicTools.git
$ cd SitTools/
$ make jar

# file name is option 
$ java -jar out/make/sictools.jar <file_name>
```
+ make jar error
  - javafx가 포함되지 않아서 일어나는 에러
  - [해결법 링크](https://askubuntu.com/questions/1137891/how-to-install-run-java-8-and-javafx-on-ubuntu-18-04)
